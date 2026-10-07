package class_scedule_lab4;

import java.time.LocalTime;

public class ScheduleItem {
    private LocalTime start;
    private LocalTime end;
    private String place;
    private String comment;

    public ScheduleItem(LocalTime start, LocalTime end, String place, String comment) {
        if (start == null || end == null) {
            throw new IllegalArgumentException("Время начала и окончания не должно быть null");
        }
        if (!start.isBefore(end)) {
            throw new IllegalArgumentException("Время начала должно быть раньше времени окончания");
        }
        this.start = start;
        this.end = end;
        this.place = place == null ? "" : place;
        this.comment = comment == null ? "" : comment;
    }

    public ScheduleItem(ScheduleItem other) {
        this(other.start, other.end, other.place, other.comment);
    }

    public LocalTime getStart() { return start; }
    public LocalTime getEnd() { return end; }
    public String getPlace() { return place; }
    public String getComment() { return comment; }

    public void setStart(LocalTime start) {
        if (start == null || !start.isBefore(end)) {
            throw new IllegalArgumentException("Некорректное время начала");
        }
        this.start = start;
    }

    public void setEnd(LocalTime end) {
        if (end == null || !start.isBefore(end)) {
            throw new IllegalArgumentException("Некорректное время окончания");
        }
        this.end = end;
    }

    public void setPlace(String place) { this.place = place == null ? "" : place; }
    public void setComment(String comment) { this.comment = comment == null ? "" : comment; }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof ScheduleItem)) return false;
        ScheduleItem s = (ScheduleItem) o;
        return start.equals(s.start) && end.equals(s.end)
                && place.equals(s.place) && comment.equals(s.comment);
    }

    @Override
    public int hashCode() {
        return java.util.Objects.hash(start, end, place, comment);
    }

    @Override
    public String toString() {
        return String.format("%s-%s | %s | %s", start, end, place, comment);
    }
}