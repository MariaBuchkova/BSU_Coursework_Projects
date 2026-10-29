package Program7;

import java.io.IOException;
import java.util.Scanner;

public class ParkingMenu {
    private ParkingFileManager manager;
    private Scanner scanner;
    
    public ParkingMenu(String filename) throws IOException {
        this.manager = new ParkingFileManager(filename);
        this.scanner = new Scanner(System.in);
    }
    
    public void showMenu() {
        while (true) {
            System.out.println("\n=== СИСТЕМА УПРАВЛЕНИЯ ПАРКОВКОЙ ===");
            System.out.println("а) Заполнение файла тестовыми данными");
            System.out.println("б) Последовательный вывод всех объектов");
            System.out.println("в) Перестроить индекс");
            System.out.println("г) Вывод по возрастанию/убыванию номера");
            System.out.println("д) Поиск по номеру");
            System.out.println("е) Удаление по номеру");
            System.out.println("ж) Статус индекса");
            System.out.println("з) Выход");
            System.out.print("Выберите операцию: ");
            
            String choice = scanner.nextLine().toLowerCase();
            
            try {
                switch (choice) {
                    case "а":
                        manager.fillWithTestData();
                        break;
                    case "б":
                        manager.printAllSequential();
                        break;
                    case "в":
                        manager.rebuildIndex();
                        break;
                    case "г":
                        handleSorting();
                        break;
                    case "д":
                        handleSearch();
                        break;
                    case "е":
                        handleDelete();
                        break;
                    case "ж":
                        manager.printIndexStatus();
                        break;
                    case "з":
                        manager.close();
                        System.out.println("Выход из программы");
                        return;
                    default:
                        System.out.println("Неверный выбор");
                }
            } catch (IOException e) {
                System.out.println("Ошибка ввода-вывода: " + e.getMessage());
            } catch (Exception e) {
                System.out.println("Ошибка: " + e.getMessage());
            }
        }
    }
    
    private void handleSorting() throws IOException {
        System.out.println("1 - по возрастанию");
        System.out.println("2 - по убыванию");
        System.out.print("Выберите порядок: ");
        String sortChoice = scanner.nextLine();
        
        if (sortChoice.equals("1")) {
            manager.printByIndex(true);
        } else if (sortChoice.equals("2")) {
            manager.printByIndex(false);
        } else {
            System.out.println("Неверный выбор");
        }
    }
    
    private void handleSearch() throws IOException {
        System.out.println("1 - точный поиск");
        System.out.println("2 - номер больше указанного");
        System.out.println("3 - номер меньше указанного");
        System.out.print("Выберите тип поиска: ");
        String searchType = scanner.nextLine();
        
        System.out.print("Введите номер: ");
        try {
            int number = Integer.parseInt(scanner.nextLine());
            
            switch (searchType) {
                case "1":
                    manager.searchByNumber(number);
                    break;
                case "2":
                    manager.searchNumbersGreaterThan(number);
                    break;
                case "3":
                    manager.searchNumbersLessThan(number);
                    break;
                default:
                    System.out.println("Неверный тип поиска");
            }
        } catch (NumberFormatException e) {
            System.out.println("Неверный формат номера");
        }
    }
    
    private void handleDelete() throws IOException {
        System.out.print("Введите номер для удаления: ");
        try {
            int number = Integer.parseInt(scanner.nextLine());
            manager.deleteByNumber(number);
        } catch (NumberFormatException e) {
            System.out.println("Неверный формат номера");
        }
    }
    
    public static void main(String[] args) {
        try {
            ParkingMenu menu = new ParkingMenu("parking_data.dat");
            menu.showMenu();
        } catch (IOException e) {
            System.out.println("Ошибка инициализации: " + e.getMessage());
        }
    }
}