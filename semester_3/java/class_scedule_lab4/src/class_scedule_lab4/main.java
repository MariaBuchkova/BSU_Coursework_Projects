package class_scedule_lab4;

import java.time.LocalTime;

//Запускать с ключом -ea.

public class main {
    private static ScheduleItem item(String s, String e, String place, String comment) {
        return new ScheduleItem(LocalTime.parse(s), LocalTime.parse(e), place, comment);
    }

    private static void show(String title, Schedule sch) {
        System.out.println("--- " + title + " (size=" + sch.size() + ") ---");
        System.out.print(sch);
        System.out.println();
    }

    public static void main(String[] args) {
        Schedule sch = new Schedule();
        Schedule small = new Schedule(1);
        show("Пустое расписание", sch);

        sch.add(item("09:00", "10:30", "Ауд. 101", "Лекция по Java"));
        sch.add(item("10:45", "12:15", "Ауд. 202", "Практика"));
        sch.add(item("13:00", "14:30", "Лаборатория", "Лабораторная работа"));
        show("После add x3", sch);

        small.add(item("08:00", "09:00", "Зал", "Зарядка"));
        small.add(item("09:00", "10:00", "Столовая", "Завтрак"));
        show("Расширение массива (емкость 1 -> 2)", small);

        sch.insert(1, item("10:30", "10:45", "Коридор", "Перерыв"));
        show("После insert(1, ...)", sch);
        assert sch.size() == 4;
        assert sch.get(1).getPlace().equals("Коридор");

        ScheduleItem old = sch.replace(0, item("09:00", "10:30", "Ауд. 303", "Лекция (перенесена)"));
        System.out.println("Заменён элемент: " + old + "\n");
        show("После replace(0, ...)", sch);
        assert sch.get(0).getPlace().equals("Ауд. 303");

        ScheduleItem removed = sch.remove(1);
        System.out.println("Удалён элемент: " + removed + "\n");
        show("После remove(1)", sch);
        assert sch.size() == 3;

        Schedule copy = new Schedule(sch);
        copy.remove(0);
        show("Копия после remove(0)", copy);
        show("Оригинал не изменился", sch);
        assert sch.size() == 3 && copy.size() == 2;

        sch.clear();
        show("После clear", sch);
        assert sch.isEmpty();

        testError("remove в пустом расписании", () -> sch.remove(0));
        testError("get с неверным индексом", () -> copy.get(10));
        testError("insert с неверным индексом", () -> copy.insert(-1, item("08:00", "09:00", "A", "B")));
        testError("add(null)", () -> copy.add(null));
        testError("replace(null)", () -> copy.replace(0, null));
        testError("начало позже окончания", () -> item("12:00", "11:00", "A", "B"));
        testError("Schedule(0)", () -> new Schedule(0));

        System.out.println("Все тесты пройдены.");
    }

    private static void testError(String name, Runnable action) {
        try {
            action.run();
            System.out.println("[FAIL] " + name + ": исключение не возникло");
            throw new AssertionError(name);
        } catch (IllegalArgumentException | IndexOutOfBoundsException ex) {
            System.out.println("[OK] " + name + " -> " + ex.getClass().getSimpleName() + ": " + ex.getMessage());
        }
    }
}