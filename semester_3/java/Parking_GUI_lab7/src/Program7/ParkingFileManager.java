package Program7;

import java.io.*;
import java.util.*;

public class ParkingFileManager {
    private RandomAccessFile file;
    private ParkingIndex indexManager;
    private String dataFilename;
    private String indexFilename;
    
    private static final int DELETED_MARKER = -1;
    
    public ParkingFileManager(String dataFilename) throws IOException {
        this.dataFilename = dataFilename;
        this.indexFilename = dataFilename + ".index";
        this.indexManager = new ParkingIndex();
        
        file = new RandomAccessFile(dataFilename, "rw");
        loadIndex();
    }
    
    public void fillWithTestData() throws IOException {
        file.setLength(0);
        indexManager = new ParkingIndex();
        
        parking[] testData = {
            new parking(101, "Иванов Иван Иванович", "01.01.2024", "01.01.2024", "10:00", "15:30", 50.0),
            new parking(205, "Петров Петр Петрович", "01.01.2024", "02.01.2024", "20:00", "08:00", 40.0),
            new parking(78, "Сидоров Алексей Николаевич", "02.01.2024", "02.01.2024", "09:00", "18:00", 60.0),
            new parking(456, "Козлова Мария Сергеевна", "03.01.2024", "03.01.2024", "14:00", "16:00", 55.0),
            new parking(33, "Васильев Дмитрий Петрович", "04.01.2024", "05.01.2024", "22:00", "10:00", 45.0)
        };
        
        int successCount = 0;
        for (parking p : testData) {
            try {
                addParking(p);
                successCount++;
            } catch (Exception e) {
                System.out.println("Ошибка при добавлении тестовой записи " + p.getNumber() + ": " + e.getMessage());
            }
        }
        System.out.println("Успешно добавлено " + successCount + " тестовых записей из " + testData.length);
    }
    
    public void printAllSequential() throws IOException {
        List<parking> allParkings = getAllParkings();
        if (allParkings.isEmpty()) {
            System.out.println("Файл пуст");
            return;
        }
        
        System.out.println("\n=== ВСЕ ЗАПИСИ (ПОСЛЕДОВАТЕЛЬНО) ===");
        for (int i = 0; i < allParkings.size(); i++) {
            System.out.println((i + 1) + ". " + allParkings.get(i));
        }
    }
    
    public void rebuildIndex() throws IOException {
        indexManager = new ParkingIndex();
        file.seek(0);
        
        while (file.getFilePointer() < file.length()) {
            long position = file.getFilePointer();
            int length = file.readInt();
            
            if (length == DELETED_MARKER) {
                continue;
            }
            
            if (length <= 0 || length > 10000) {
                try {
                    if (length > 0) {
                        file.skipBytes(length);
                    }
                } catch (Exception e) {
                    break;
                }
                continue;
            }
            
            byte[] data = new byte[length];
            int bytesRead = file.read(data);
            
            if (bytesRead == length) {
                try {
                    parking p = deserialize(data);
                    indexManager.addToIndex(p.getNumber(), position);
                } catch (IOException e) {
                    System.out.println("Ошибка при индексировании записи на позиции " + position);
                }
            }
        }
        saveIndex();
        System.out.println("Индекс перестроен");
    }
    
    public void printByIndex(boolean ascending) throws IOException {
        List<Map.Entry<Integer, Long>> entries;
        
        if (ascending) {
            entries = indexManager.getEntriesAscending();
            System.out.println("\n=== ЗАПИСИ ПО ВОЗРАСТАНИЮ НОМЕРА ===");
        } else {
            entries = indexManager.getEntriesDescending();
            System.out.println("\n=== ЗАПИСИ ПО УБЫВАНИЮ НОМЕРА ===");
        }
        
        if (entries.isEmpty()) {
            System.out.println("Нет записей для отображения");
            return;
        }
        
        for (int i = 0; i < entries.size(); i++) {
            Map.Entry<Integer, Long> entry = entries.get(i);
            parking p = readAtPosition(entry.getValue());
            if (p != null) {
                System.out.println((i + 1) + ". " + p);
            }
        }
    }
    
    public void searchByNumber(int number) throws IOException {
        Long position = indexManager.getPositionByNumber(number);
        if (position == null) {
            System.out.println("Запись с номером " + number + " не найдена");
            return;
        }
        
        parking p = readAtPosition(position);
        if (p != null) {
            System.out.println("\n=== НАЙДЕНА ЗАПИСЬ ===");
            System.out.println(p);
        } else {
            System.out.println("Запись с номером " + number + " была удалена");
        }
    }
    
    public void searchNumbersGreaterThan(int number) throws IOException {
        List<Map.Entry<Integer, Long>> entries = indexManager.getEntriesGreaterThan(number);
        printSearchResults(entries, "НОМЕР БОЛЬШЕ " + number);
    }
    
    public void searchNumbersLessThan(int number) throws IOException {
        List<Map.Entry<Integer, Long>> entries = indexManager.getEntriesLessThan(number);
        printSearchResults(entries, "НОМЕР МЕНЬШЕ " + number);
    }
    
    public boolean deleteByNumber(int number) throws IOException {
        Long position = indexManager.getPositionByNumber(number);
        if (position == null) {
            System.out.println("Запись с номером " + number + " не найдена");
            return false;
        }
        
        file.seek(position);
        file.writeInt(DELETED_MARKER);
        
        indexManager.removeFromIndex(number);
        saveIndex();
        
        System.out.println("Запись с номером " + number + " удалена");
        return true;
    }
    
    
    public void addParking(parking parking) throws IOException {
        long position = file.length();
        file.seek(position);
        
        byte[] data = serialize(parking);
        file.writeInt(data.length);
        file.write(data);
        
        indexManager.addToIndex(parking.getNumber(), position);
        saveIndex();
    }
    
    public List<parking> getAllParkings() throws IOException {
        List<parking> result = new ArrayList<>();
        file.seek(0);
        
        while (file.getFilePointer() < file.length()) {
            long position = file.getFilePointer();
            
            try {
                int length = file.readInt();
                
                if (length == DELETED_MARKER) {
                    continue;
                }
                
                if (length <= 0 || length > 10000) {
                    if (length > 0) {
                        long skipBytes = Math.min(length, file.length() - file.getFilePointer());
                        if (skipBytes > 0) {
                            file.skipBytes((int)skipBytes);
                        }
                    }
                    continue;
                }
                
                if (file.getFilePointer() + length > file.length()) {
                    break;
                }
                
                byte[] data = new byte[length];
                int bytesRead = file.read(data);
                
                if (bytesRead != length) {
                    continue;
                }
                
                parking p = deserialize(data);
                result.add(p);
                
            } catch (EOFException e) {
                break;
            } catch (Exception e) {
                System.out.println("Ошибка чтения на позиции " + position + ": " + e.getMessage());
                try {
                    long nextPosition = findNextRecordPosition(position + 4);
                    file.seek(nextPosition);
                } catch (Exception ex) {
                    break;
                }
            }
        }
        return result;
    }
    
    private long findNextRecordPosition(long startPosition) throws IOException {
        file.seek(startPosition);
        while (file.getFilePointer() < file.length()) {
            long position = file.getFilePointer();
            try {
                int length = file.readInt();
                if (length == DELETED_MARKER || (length > 0 && length <= 10000)) {
                    return position;
                }
            } catch (Exception e) {
                file.seek(position + 1);
            }
        }
        return file.length();
    }
    
    private parking readAtPosition(long position) throws IOException {
        if (position < 0 || position >= file.length()) {
            return null;
        }
        
        try {
            file.seek(position);
            int length = file.readInt();
            if (length == DELETED_MARKER) {
                return null;
            }
            
            if (length <= 0 || length > 10000) {
                return null;
            }
            
            if (position + 4 + length > file.length()) {
                return null;
            }
            
            byte[] data = new byte[length];
            int bytesRead = file.read(data);
            
            if (bytesRead != length) {
                return null;
            }
            
            return deserialize(data);
        } catch (Exception e) {
            return null;
        }
    }
    
    private void printSearchResults(List<Map.Entry<Integer, Long>> entries, String title) throws IOException {
        if (entries.isEmpty()) {
            System.out.println("Записей " + title.toLowerCase() + " не найдено");
            return;
        }
        
        System.out.println("\n=== " + title + " ===");
        int count = 0;
        for (Map.Entry<Integer, Long> entry : entries) {
            parking p = readAtPosition(entry.getValue());
            if (p != null) {
                count++;
                System.out.println(count + ". " + p);
            }
        }
        
        if (count == 0) {
            System.out.println("Активных записей " + title.toLowerCase() + " не найдено");
        }
    }
    
    private byte[] serialize(parking parking) throws IOException {
        try (ByteArrayOutputStream baos = new ByteArrayOutputStream();
             ObjectOutputStream oos = new ObjectOutputStream(baos)) {
            oos.writeObject(parking);
            return baos.toByteArray();
        }
    }
    
    private parking deserialize(byte[] data) throws IOException {
        try (ByteArrayInputStream bais = new ByteArrayInputStream(data);
             ObjectInputStream ois = new ObjectInputStream(bais)) {
            return (parking) ois.readObject();
        } catch (ClassNotFoundException e) {
            throw new IOException("Error deserializing parking object", e);
        } catch (Exception e) {
            throw new IOException("Error deserializing data", e);
        }
    }
    
    private void loadIndex() {
        try {
            indexManager.loadIndex(indexFilename);
            System.out.println("Индекс загружен успешно");
        } catch (Exception e) {
            System.out.println("Индекс не загружен, будет создан новый: " + e.getMessage());
            try {
                rebuildIndex();
            } catch (IOException ex) {
                System.out.println("Ошибка при перестроении индекса: " + ex.getMessage());
            }
        }
    }
    
    private void saveIndex() throws IOException {
        indexManager.saveIndex(indexFilename);
    }
    
    public void close() throws IOException {
        if (file != null) {
            file.close();
        }
    }
    
    public void printIndexStatus() {
        Set<Integer> indexes = indexManager.getAllIndexes();
        System.out.println("В индексе: " + indexes.size() + " записей");
        if (!indexes.isEmpty()) {
            System.out.println("Индексированные номера: " + indexes);
        }
    }

    public void clearAll() throws IOException {
        file.setLength(0);
        indexManager = new ParkingIndex();
        saveIndex();
        System.out.println("Все данные очищены");
    }
    
    public void compactFile() throws IOException {
        System.out.println("Начинаем уплотнение файла...");
        
        List<parking> validParkings = getAllParkings();
        System.out.println("Найдено валидных записей: " + validParkings.size());
        
        String tempFilename = dataFilename + ".tmp";
        try (RandomAccessFile tempFile = new RandomAccessFile(tempFilename, "rw")) {
            ParkingIndex tempIndex = new ParkingIndex();
            
            for (parking p : validParkings) {
                long position = tempFile.length();
                tempFile.seek(position);
                
                byte[] data = serialize(p);
                tempFile.writeInt(data.length);
                tempFile.write(data);
                
                tempIndex.addToIndex(p.getNumber(), position);
            }
            
            tempIndex.saveIndex(tempFilename + ".index");
        }
        
        file.close();
        
        File originalFile = new File(dataFilename);
        File originalIndex = new File(indexFilename);
        File tempFile = new File(tempFilename);
        File tempIndexFile = new File(tempFilename + ".index");
        
        if (originalFile.exists()) originalFile.delete();
        if (originalIndex.exists()) originalIndex.delete();
        
        tempFile.renameTo(originalFile);
        tempIndexFile.renameTo(originalIndex);
        
        file = new RandomAccessFile(dataFilename, "rw");
        indexManager = new ParkingIndex();
        loadIndex();
        
        System.out.println("Файл уплотнен. Сохранено записей: " + validParkings.size());
    }

    public Long getIndexPosition(int number) {
        return indexManager.getPositionByNumber(number);
    }

    public parking readAtPosition(Long position) throws IOException {
        if (position == null) return null;
        return readAtPosition(position.longValue());
    }
}