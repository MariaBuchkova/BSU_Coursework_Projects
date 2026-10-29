package Program7;

import java.io.*;
import java.time.LocalDate;
import java.time.LocalTime;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;
import java.time.Duration;

public class parking implements Serializable {
    private static final long serialVersionUID = 1L;
    
    private int number;
    private String FIO;
    private String dataStart;
    private String dataEnd;
    private String timeStart;
    private String timeEnd;
    private double pricePerHour;
    
    private static final String DATE_PATTERN = "dd.MM.yyyy";
    private static final String TIME_PATTERN = "HH:mm";
    private static final DateTimeFormatter DATE_FORMATTER = DateTimeFormatter.ofPattern(DATE_PATTERN);
    private static final DateTimeFormatter TIME_FORMATTER = DateTimeFormatter.ofPattern(TIME_PATTERN);
    
    public parking(int number, String FIO, String dataStart, String dataEnd, 
                  String timeStart, String timeEnd, double pricePerHour) {
        setNumber(number);
        setFIO(FIO);
        setDataStart(dataStart);
        setDataEnd(dataEnd);
        setTimeStart(timeStart);
        setTimeEnd(timeEnd);
        setPricePerHour(pricePerHour);
    }
    
    // Геттеры и сеттеры
    public int getNumber() { return number; }
    
    public void setNumber(int number) {
        if (number <= 0) throw new IllegalArgumentException("Номер должен быть положительным числом");
        this.number = number;
    }
    
    public String getFIO() { return FIO; }
    
    public void setFIO(String FIO) {
        if (FIO == null || FIO.trim().isEmpty()) {
            throw new IllegalArgumentException("ФИО не может быть пустым");
        }
        
        String[] nameParts = FIO.trim().split("\\s+");
        if (nameParts.length != 3) {
            throw new IllegalArgumentException("ФИО должно состоять из трех частей (Фамилия Имя Отчество)");
        }
        
        this.FIO = String.join(" ", nameParts);
    }
    
    public String getDataStart() { return dataStart; }
    public String getDataEnd() { return dataEnd; }
    public String getTimeStart() { return timeStart; }
    public String getTimeEnd() { return timeEnd; }
    public double getPricePerHour() { return pricePerHour; }
    
    public void setDataStart(String dataStart) {
        validateDate(dataStart);
        this.dataStart = dataStart;
    }
    
    public void setDataEnd(String dataEnd) {
        validateDate(dataEnd);
        this.dataEnd = dataEnd;
    }
    
    public void setTimeStart(String timeStart) {
        validateTime(timeStart);
        this.timeStart = timeStart;
    }
    
    public void setTimeEnd(String timeEnd) {
        validateTime(timeEnd);
        this.timeEnd = timeEnd;
    }
    
    public void setPricePerHour(double pricePerHour) {
        if (pricePerHour < 0) throw new IllegalArgumentException("Цена за час не может быть отрицательной");
        this.pricePerHour = pricePerHour;
    }
    
    // Метод для получения времени стоянки в часах
    public long getParkingDurationHours() {
        try {
            LocalDate startDate = LocalDate.parse(dataStart, DATE_FORMATTER);
            LocalDate endDate = LocalDate.parse(dataEnd, DATE_FORMATTER);
            LocalTime startTime = LocalTime.parse(timeStart, TIME_FORMATTER);
            LocalTime endTime = LocalTime.parse(timeEnd, TIME_FORMATTER);
            
            // Создаем LocalDateTime для расчета длительности
            java.time.LocalDateTime startDateTime = java.time.LocalDateTime.of(startDate, startTime);
            java.time.LocalDateTime endDateTime = java.time.LocalDateTime.of(endDate, endTime);
            
            return Duration.between(startDateTime, endDateTime).toHours();
        } catch (Exception e) {
            return 0;
        }
    }
    
    private void validateDate(String date) {
        if (date == null || date.trim().isEmpty()) {
            throw new IllegalArgumentException("Дата не может быть пустой");
        }
        try {
            // Используем правильный парсинг для формата dd.MM.yyyy
            LocalDate.parse(date, DATE_FORMATTER);
        } catch (DateTimeParseException e) {
            throw new IllegalArgumentException("Неверный формат даты. Используйте: " + DATE_PATTERN + ". Ошибка: " + date);
        }
    }
    
    private void validateTime(String time) {
        if (time == null || time.trim().isEmpty()) {
            throw new IllegalArgumentException("Время не может быть пустым");
        }
        try {
            // Используем правильный парсинг для формата HH:mm
            LocalTime.parse(time, TIME_FORMATTER);
        } catch (DateTimeParseException e) {
            throw new IllegalArgumentException("Неверный формат времени. Используйте: " + TIME_PATTERN + ". Ошибка: " + time);
        }
    }
    
    @Override
    public String toString() {
        return String.format("parking[number=%d, FIO='%s', from %s %s to %s %s, price=%.2f, duration=%d hours]",
                number, FIO, dataStart, timeStart, dataEnd, timeEnd, pricePerHour, getParkingDurationHours());
    }
}