package Program7;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.File;
import java.io.IOException;
import java.util.List;

public class ParkingGUI extends JFrame {
    private ParkingFileManager manager;
    private JTextArea textArea;
    private JTextField numberField, fioField, dataStartField, dataEndField;
    private JTextField timeStartField, timeEndField, priceField;
    private JLabel statusLabel;
    private JFileChooser fileChooser;
    
    public ParkingGUI() {
        initComponents();
        setTitle("Система управления парковкой");
        setSize(1000, 700);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
        try {
            manager = new ParkingFileManager("parking_data.dat");
            updateStatus("Система инициализирована. Файл: parking_data.dat");
        } catch (IOException e) {
            showError("Ошибка инициализации: " + e.getMessage());
        }
    }
    
    private void initComponents() {
        JMenuBar menuBar = new JMenuBar();
        
        JMenu fileMenu = new JMenu("Файл");
        JMenuItem openItem = new JMenuItem("Открыть файл...");
        JMenuItem saveItem = new JMenuItem("Сохранить как...");
        JMenuItem exitItem = new JMenuItem("Выход");
        
        openItem.addActionListener(e -> openFile());
        saveItem.addActionListener(e -> saveFile());
        exitItem.addActionListener(e -> System.exit(0));
        
        fileMenu.add(openItem);
        fileMenu.add(saveItem);
        fileMenu.addSeparator();
        fileMenu.add(exitItem);
        
        // Меню "Операции"
        JMenu operationsMenu = new JMenu("Операции");
        
        JMenuItem fillTestDataItem = new JMenuItem("Заполнить тестовыми данными");
        JMenuItem showAllItem = new JMenuItem("Показать все записи");
        JMenuItem rebuildIndexItem = new JMenuItem("Перестроить индекс");
        JMenuItem sortAscItem = new JMenuItem("Сортировать по возрастанию номера");
        JMenuItem sortDescItem = new JMenuItem("Сортировать по убыванию номера");
        JMenuItem searchItem = new JMenuItem("Поиск по номеру");
        JMenuItem deleteItem = new JMenuItem("Удалить по номеру");
        JMenuItem clearAllItem = new JMenuItem("Очистить все данные");
        JMenuItem compactItem = new JMenuItem("Уплотнить файл");
        
        fillTestDataItem.addActionListener(e -> fillTestData());
        showAllItem.addActionListener(e -> showAllRecords());
        rebuildIndexItem.addActionListener(e -> rebuildIndex());
        sortAscItem.addActionListener(e -> sortRecords(true));
        sortDescItem.addActionListener(e -> sortRecords(false));
        searchItem.addActionListener(e -> searchDialog());
        deleteItem.addActionListener(e -> deleteDialog());
        clearAllItem.addActionListener(e -> clearAllData());
        compactItem.addActionListener(e -> compactFile());
        
        operationsMenu.add(fillTestDataItem);
        operationsMenu.add(showAllItem);
        operationsMenu.add(rebuildIndexItem);
        operationsMenu.addSeparator();
        operationsMenu.add(sortAscItem);
        operationsMenu.add(sortDescItem);
        operationsMenu.addSeparator();
        operationsMenu.add(searchItem);
        operationsMenu.add(deleteItem);
        operationsMenu.addSeparator();
        operationsMenu.add(clearAllItem);
        operationsMenu.add(compactItem);
        
        // Меню "Справка"
        JMenu helpMenu = new JMenu("Справка");
        JMenuItem aboutItem = new JMenuItem("О программе");
        aboutItem.addActionListener(e -> showAbout());
        helpMenu.add(aboutItem);
        
        menuBar.add(fileMenu);
        menuBar.add(operationsMenu);
        menuBar.add(helpMenu);
        setJMenuBar(menuBar);
        
        // Создаем панель для формы ввода
        JPanel formPanel = createFormPanel();
        
        // Создаем текстовую область для вывода
        textArea = new JTextArea();
        textArea.setEditable(false);
        textArea.setFont(new Font("Monospaced", Font.PLAIN, 12));
        JScrollPane scrollPane = new JScrollPane(textArea);
        
        // Создаем панель кнопок
        JPanel buttonPanel = createButtonPanel();
        
        // Создаем статусную строку
        statusLabel = new JLabel("Готово");
        statusLabel.setBorder(BorderFactory.createEtchedBorder());
        
        // Размещаем компоненты
        Container contentPane = getContentPane();
        contentPane.setLayout(new BorderLayout(5, 5));
        
        JPanel topPanel = new JPanel(new BorderLayout());
        topPanel.add(formPanel, BorderLayout.NORTH);
        topPanel.add(buttonPanel, BorderLayout.SOUTH);
        
        contentPane.add(topPanel, BorderLayout.NORTH);
        contentPane.add(scrollPane, BorderLayout.CENTER);
        contentPane.add(statusLabel, BorderLayout.SOUTH);
        
        // Инициализируем файловый диалог
        fileChooser = new JFileChooser();
        fileChooser.setCurrentDirectory(new File("."));
    }
    
    private JPanel createFormPanel() {
        JPanel panel = new JPanel(new GridBagLayout());
        panel.setBorder(BorderFactory.createTitledBorder("Данные о парковке"));
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.insets = new Insets(5, 5, 5, 5);
        gbc.fill = GridBagConstraints.HORIZONTAL;
        
        // Поле номера
        gbc.gridx = 0; gbc.gridy = 0;
        panel.add(new JLabel("Номер авто:"), gbc);
        gbc.gridx = 1;
        numberField = new JTextField(10);
        panel.add(numberField, gbc);
        
        // Поле ФИО
        gbc.gridx = 0; gbc.gridy = 1;
        panel.add(new JLabel("ФИО владельца:"), gbc);
        gbc.gridx = 1;
        fioField = new JTextField(30);
        panel.add(fioField, gbc);
        
        // Поля даты начала
        gbc.gridx = 0; gbc.gridy = 2;
        panel.add(new JLabel("Дата начала (дд.мм.гггг):"), gbc);
        gbc.gridx = 1;
        dataStartField = new JTextField(10);
        panel.add(dataStartField, gbc);
        
        // Поля времени начала
        gbc.gridx = 2; gbc.gridy = 2;
        panel.add(new JLabel("Время начала (чч:мм):"), gbc);
        gbc.gridx = 3;
        timeStartField = new JTextField(10);
        panel.add(timeStartField, gbc);
        
        // Поля даты окончания
        gbc.gridx = 0; gbc.gridy = 3;
        panel.add(new JLabel("Дата окончания (дд.мм.гггг):"), gbc);
        gbc.gridx = 1;
        dataEndField = new JTextField(10);
        panel.add(dataEndField, gbc);
        
        // Поля времени окончания
        gbc.gridx = 2; gbc.gridy = 3;
        panel.add(new JLabel("Время окончания (чч:мм):"), gbc);
        gbc.gridx = 3;
        timeEndField = new JTextField(10);
        panel.add(timeEndField, gbc);
        
        // Поле цены
        gbc.gridx = 0; gbc.gridy = 4;
        panel.add(new JLabel("Цена за час:"), gbc);
        gbc.gridx = 1;
        priceField = new JTextField(10);
        panel.add(priceField, gbc);
        
        return panel;
    }
    
    private JPanel createButtonPanel() {
        JPanel panel = new JPanel(new FlowLayout(FlowLayout.LEFT));
        
        JButton addButton = new JButton("Добавить запись");
        JButton clearFormButton = new JButton("Очистить форму");
        JButton indexStatusButton = new JButton("Статус индекса");
        
        addButton.addActionListener(e -> addParkingRecord());
        clearFormButton.addActionListener(e -> clearForm());
        indexStatusButton.addActionListener(e -> showIndexStatus());
        
        panel.add(addButton);
        panel.add(clearFormButton);
        panel.add(indexStatusButton);
        
        return panel;
    }
    
    private void addParkingRecord() {
        try {
            int number = Integer.parseInt(numberField.getText().trim());
            String fio = fioField.getText().trim();
            String dataStart = dataStartField.getText().trim();
            String dataEnd = dataEndField.getText().trim();
            String timeStart = timeStartField.getText().trim();
            String timeEnd = timeEndField.getText().trim();
            double price = Double.parseDouble(priceField.getText().trim());
            
            parking p = new parking(number, fio, dataStart, dataEnd, timeStart, timeEnd, price);
            manager.addParking(p);
            
            updateStatus("Запись успешно добавлена: номер " + number);
            clearForm();
        } catch (NumberFormatException e) {
            showError("Некорректный формат числа");
        } catch (IllegalArgumentException e) {
            showError("Ошибка в данных: " + e.getMessage());
        } catch (IOException e) {
            showError("Ошибка ввода-вывода: " + e.getMessage());
        }
    }
    
    private void clearForm() {
        numberField.setText("");
        fioField.setText("");
        dataStartField.setText("");
        dataEndField.setText("");
        timeStartField.setText("");
        timeEndField.setText("");
        priceField.setText("");
        updateStatus("Форма очищена");
    }
    
    private void fillTestData() {
        try {
            manager.fillWithTestData();
            updateStatus("Тестовые данные успешно добавлены");
        } catch (IOException e) {
            showError("Ошибка: " + e.getMessage());
        }
    }
    
    private void showAllRecords() {
        try {
            List<parking> records = manager.getAllParkings();
            textArea.setText("");
            textArea.append("=== ВСЕ ЗАПИСИ (ПОСЛЕДОВАТЕЛЬНО) ===\n\n");
            
            if (records.isEmpty()) {
                textArea.append("Файл пуст\n");
            } else {
                for (int i = 0; i < records.size(); i++) {
                    textArea.append((i + 1) + ". " + records.get(i).toString() + "\n");
                }
                textArea.append("\nВсего записей: " + records.size());
            }
            updateStatus("Показано " + records.size() + " записей");
        } catch (IOException e) {
            showError("Ошибка чтения: " + e.getMessage());
        }
    }
    
    private void rebuildIndex() {
        try {
            manager.rebuildIndex();
            updateStatus("Индекс перестроен");
        } catch (IOException e) {
            showError("Ошибка: " + e.getMessage());
        }
    }
    
    private void sortRecords(boolean ascending) {
        try {
            List<parking> records = manager.getAllParkings();
            
            // Сортируем вручную так как ваш метод printByIndex не возвращает список
            records.sort((p1, p2) -> {
                if (ascending) {
                    return Integer.compare(p1.getNumber(), p2.getNumber());
                } else {
                    return Integer.compare(p2.getNumber(), p1.getNumber());
                }
            });
            
            textArea.setText("");
            textArea.append(ascending ? "=== ЗАПИСИ ПО ВОЗРАСТАНИЮ НОМЕРА ===\n\n" 
                                     : "=== ЗАПИСИ ПО УБЫВАНИЮ НОМЕРА ===\n\n");
            
            if (records.isEmpty()) {
                textArea.append("Нет записей\n");
            } else {
                for (int i = 0; i < records.size(); i++) {
                    textArea.append((i + 1) + ". " + records.get(i).toString() + "\n");
                }
                textArea.append("\nВсего записей: " + records.size());
            }
            updateStatus("Отсортировано " + records.size() + " записей");
        } catch (IOException e) {
            showError("Ошибка: " + e.getMessage());
        }
    }
    
    private void searchDialog() {
        JPanel panel = new JPanel(new GridLayout(3, 2, 5, 5));
        JTextField searchField = new JTextField();
        JComboBox<String> searchType = new JComboBox<>(new String[]{
            "Точный поиск", "Номер больше", "Номер меньше"
        });
        
        panel.add(new JLabel("Номер для поиска:"));
        panel.add(searchField);
        panel.add(new JLabel("Тип поиска:"));
        panel.add(searchType);
        
        int result = JOptionPane.showConfirmDialog(this, panel, 
            "Поиск записи", JOptionPane.OK_CANCEL_OPTION);
        
        if (result == JOptionPane.OK_OPTION) {
            try {
                int number = Integer.parseInt(searchField.getText().trim());
                int type = searchType.getSelectedIndex();
                
                try {
                    switch (type) {
                        case 0: // Точный поиск
                            Long position = manager.getIndexPosition(number);
                            if (position != null) {
                                parking p = manager.readAtPosition(position);
                                if (p != null) {
                                    textArea.setText("=== НАЙДЕНА ЗАПИСЬ ===\n\n" + p.toString());
                                    updateStatus("Найдена запись с номером " + number);
                                } else {
                                    textArea.setText("Запись с номером " + number + " не найдена");
                                    updateStatus("Запись не найдена");
                                }
                            } else {
                                textArea.setText("Запись с номером " + number + " не найдена");
                                updateStatus("Запись не найдена");
                            }
                            break;
                        case 1: // Номер больше
                            searchNumbersGreaterThan(number);
                            break;
                        case 2: // Номер меньше
                            searchNumbersLessThan(number);
                            break;
                    }
                } catch (Exception e) {
                    showError("Ошибка поиска: " + e.getMessage());
                }
            } catch (NumberFormatException e) {
                showError("Введите корректный номер");
            }
        }
    }
    
    private void searchNumbersGreaterThan(int number) throws IOException {
        List<parking> allRecords = manager.getAllParkings();
        textArea.setText("=== ЗАПИСИ С НОМЕРОМ БОЛЬШЕ " + number + " ===\n\n");
        
        int count = 0;
        for (parking p : allRecords) {
            if (p.getNumber() > number) {
                count++;
                textArea.append(count + ". " + p.toString() + "\n");
            }
        }
        
        if (count == 0) {
            textArea.append("Записей не найдено\n");
        }
        textArea.append("\nНайдено записей: " + count);
        updateStatus("Найдено " + count + " записей с номером больше " + number);
    }
    
    private void searchNumbersLessThan(int number) throws IOException {
        List<parking> allRecords = manager.getAllParkings();
        textArea.setText("=== ЗАПИСИ С НОМЕРОМ МЕНЬШЕ " + number + " ===\n\n");
        
        int count = 0;
        for (parking p : allRecords) {
            if (p.getNumber() < number) {
                count++;
                textArea.append(count + ". " + p.toString() + "\n");
            }
        }
        
        if (count == 0) {
            textArea.append("Записей не найдено\n");
        }
        textArea.append("\nНайдено записей: " + count);
        updateStatus("Найдено " + count + " записей с номером меньше " + number);
    }
    
    private void deleteDialog() {
        String input = JOptionPane.showInputDialog(this, 
            "Введите номер записи для удаления:", "Удаление записи", 
            JOptionPane.QUESTION_MESSAGE);
        
        if (input != null && !input.trim().isEmpty()) {
            try {
                int number = Integer.parseInt(input.trim());
                int confirm = JOptionPane.showConfirmDialog(this, 
                    "Удалить запись с номером " + number + "?", 
                    "Подтверждение удаления", JOptionPane.YES_NO_OPTION);
                
                if (confirm == JOptionPane.YES_OPTION) {
                    boolean deleted = manager.deleteByNumber(number);
                    if (deleted) {
                        updateStatus("Запись с номером " + number + " удалена");
                    } else {
                        updateStatus("Запись с номером " + number + " не найдена");
                    }
                }
            } catch (NumberFormatException e) {
                showError("Введите корректный номер");
            } catch (IOException e) {
                showError("Ошибка удаления: " + e.getMessage());
            }
        }
    }
    
    private void showIndexStatus() {
        manager.printIndexStatus();
        updateStatus("Статус индекса выведен в консоль");
    }
    
    private void clearAllData() {
        int confirm = JOptionPane.showConfirmDialog(this, 
            "Вы уверены, что хотите удалить все данные?", 
            "Подтверждение", JOptionPane.YES_NO_OPTION);
        
        if (confirm == JOptionPane.YES_OPTION) {
            try {
                manager.clearAll();
                textArea.setText("");
                updateStatus("Все данные очищены");
            } catch (IOException e) {
                showError("Ошибка: " + e.getMessage());
            }
        }
    }
    
    private void compactFile() {
        int confirm = JOptionPane.showConfirmDialog(this, 
            "Уплотнение файла удалит все помеченные записи.\nПродолжить?", 
            "Подтверждение", JOptionPane.YES_NO_OPTION);
        
        if (confirm == JOptionPane.YES_OPTION) {
            try {
                manager.compactFile();
                updateStatus("Файл уплотнен");
            } catch (IOException e) {
                showError("Ошибка: " + e.getMessage());
            }
        }
    }
    
    private void openFile() {
        fileChooser.setDialogTitle("Открыть файл данных");
        fileChooser.setSelectedFile(new File("parking_data.dat"));
        
        if (fileChooser.showOpenDialog(this) == JFileChooser.APPROVE_OPTION) {
            try {
                manager.close();
                manager = new ParkingFileManager(fileChooser.getSelectedFile().getPath());
                updateStatus("Файл открыт: " + fileChooser.getSelectedFile().getName());
            } catch (IOException e) {
                showError("Ошибка открытия файла: " + e.getMessage());
            }
        }
    }
    
    private void saveFile() {
        fileChooser.setDialogTitle("Сохранить файл данных");
        fileChooser.setSelectedFile(new File("parking_data_backup.dat"));
        
        if (fileChooser.showSaveDialog(this) == JFileChooser.APPROVE_OPTION) {
            // Здесь можно добавить логику копирования файла
            updateStatus("Сохранение в: " + fileChooser.getSelectedFile().getName());
            JOptionPane.showMessageDialog(this, 
                "Функция сохранения в разработке", "Информация", 
                JOptionPane.INFORMATION_MESSAGE);
        }
    }
    
    private void showAbout() {
        JOptionPane.showMessageDialog(this, 
            "Система управления парковкой\nВерсия 1.0\n\n" +
            "Функции:\n" +
            "• Добавление записей о парковке\n" +
            "• Поиск и сортировка записей\n" +
            "• Индексация по номеру авто\n" +
            "• Удаление и редактирование данных\n\n" +
            "Все данные хранятся в файле parking_data.dat", 
            "О программе", JOptionPane.INFORMATION_MESSAGE);
    }
    
    private void updateStatus(String message) {
        statusLabel.setText(message);
    }
    
    private void showError(String message) {
        JOptionPane.showMessageDialog(this, message, "Ошибка", JOptionPane.ERROR_MESSAGE);
        updateStatus("Ошибка: " + message);
    }
    
    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            ParkingGUI gui = new ParkingGUI();
            gui.setVisible(true);
        });
    }
}