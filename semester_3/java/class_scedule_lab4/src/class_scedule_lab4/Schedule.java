package class_scedule_lab4;

import java.util.Arrays;

public class Schedule {
    private static final int DEFAULT_CAPACITY = 4;

    private ScheduleItem[] items;
    private int size;

    public Schedule() {
        this(DEFAULT_CAPACITY);
    }

    public Schedule(int capacity) {
        if (capacity <= 0) {
            throw new IllegalArgumentException("Емкость должна быть положительной: " + capacity);
        }
        items = new ScheduleItem[capacity];
        size = 0;
    }

    public Schedule(Schedule other) {
        this(Math.max(other.size, DEFAULT_CAPACITY));
        for (int i = 0; i < other.size; i++) {
            items[i] = new ScheduleItem(other.items[i]);
        }
        size = other.size;
    }

    public int size() {
        return size;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public ScheduleItem get(int index) {
        checkIndex(index);
        return items[index];
    }

    public void clear() {
        Arrays.fill(items, 0, size, null);
        size = 0;
        assert size == 0;
    }

    public void add(ScheduleItem item) {
        checkItem(item);
        ensureCapacity(size + 1);
        items[size++] = item;
        assert size <= items.length;
    }

    /** Вставить элемент на позицию index (допустимо 0..size), остальные сдвигаются вправо. */
    public void insert(int index, ScheduleItem item) {
        if (index < 0 || index > size) {
            throw new IndexOutOfBoundsException("Индекс " + index + ", размер " + size);
        }
        checkItem(item);
        ensureCapacity(size + 1);
        System.arraycopy(items, index, items, index + 1, size - index);
        items[index] = item;
        size++;
    }

    public ScheduleItem replace(int index, ScheduleItem item) {
        checkIndex(index);
        checkItem(item);
        ScheduleItem old = items[index];
        items[index] = item;
        return old;
    }

    public ScheduleItem remove(int index) {
        checkIndex(index);
        ScheduleItem removed = items[index];
        System.arraycopy(items, index + 1, items, index, size - index - 1);
        items[--size] = null;
        return removed;
    }

    private void checkIndex(int index) {
        if (index < 0 || index >= size) {
            throw new IndexOutOfBoundsException("Индекс " + index + ", размер " + size);
        }
    }

    private void checkItem(ScheduleItem item) {
        if (item == null) {
            throw new IllegalArgumentException("Элемент расписания не может быть null");
        }
    }

    private void ensureCapacity(int min) {
        if (min > items.length) {
            items = Arrays.copyOf(items, Math.max(min, items.length * 2));
        }
    }

    @Override
    public String toString() {
        if (size == 0) return "(расписание пусто)";
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < size; i++) {
            sb.append(i).append(": ").append(items[i]).append('\n');
        }
        return sb.toString();
    }
}