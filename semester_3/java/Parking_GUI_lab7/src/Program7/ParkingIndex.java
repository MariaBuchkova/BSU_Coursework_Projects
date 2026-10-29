package Program7;

import java.io.*;
import java.util.*;

public class ParkingIndex {
    private TreeMap<Integer, Long> numberIndex;
    
    public ParkingIndex() {
        numberIndex = new TreeMap<>();
    }
    
    public void addToIndex(int number, long position) {
        numberIndex.put(number, position);
    }
    
    public Long getPositionByNumber(int number) {
        return numberIndex.get(number);
    }
    
    public void removeFromIndex(int number) {
        numberIndex.remove(number);
    }
    
    public List<Map.Entry<Integer, Long>> getEntriesAscending() {
        return new ArrayList<>(numberIndex.entrySet());
    }
    
    public List<Map.Entry<Integer, Long>> getEntriesDescending() {
        List<Map.Entry<Integer, Long>> list = new ArrayList<>(numberIndex.entrySet());
        list.sort((a, b) -> b.getKey().compareTo(a.getKey()));
        return list;
    }
    
    public List<Map.Entry<Integer, Long>> getEntriesGreaterThan(int number) {
        List<Map.Entry<Integer, Long>> result = new ArrayList<>();
        for (Map.Entry<Integer, Long> entry : numberIndex.tailMap(number + 1).entrySet()) {
            result.add(entry);
        }
        return result;
    }
    
    public List<Map.Entry<Integer, Long>> getEntriesLessThan(int number) {
        List<Map.Entry<Integer, Long>> result = new ArrayList<>();
        for (Map.Entry<Integer, Long> entry : numberIndex.headMap(number).entrySet()) {
            result.add(entry);
        }
        return result;
    }
    
    public Set<Integer> getAllIndexes() {
        return numberIndex.keySet();
    }
    
    public void saveIndex(String filename) throws IOException {
        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(filename))) {
            oos.writeObject(numberIndex);
        }
    }
    
    @SuppressWarnings("unchecked")
    public void loadIndex(String filename) throws IOException, ClassNotFoundException {
        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(filename))) {
            numberIndex = (TreeMap<Integer, Long>) ois.readObject();
        }
    }
}