# schedule_app

A Java console application for storing and editing a schedule as an array of items.

## Task

Define the class `Schedule` as an array of elements, each containing a start time, an end time, a place and a comment. Implement methods for changing the elements: clear, add, replace, remove, insert. Use `assert` and exceptions to handle error situations where possible. Develop a separate test application that exercises all constructors and methods and prints the data and results. Provide a Makefile with the targets `clean`, `build` and `run`.

## How it works

* `Schedule` is the main class that implements the schedule as an array of `ScheduleItem` objects.
* `ScheduleItem` is a class that represents one schedule item. Each `ScheduleItem` contains a start time, an end time, a place and a comment.
* The schedule is stored internally as an array `ScheduleItem[]` together with the counter `size`.
* When the array is full, it is enlarged automatically: the new length is `max(required, 2 * current length)`.
* `insert`, `remove` and the array growth use `System.arraycopy` to shift elements.
* `clear()` sets all used cells to `null` and resets `size` to 0.
* The copy constructor makes copies of the items, so changing the copy does not affect the original.
* The test application (`main`) calls every constructor and method with prepared data, prints the results, and then deliberately triggers error situations inside `try/catch` blocks, printing the exception messages.

## Project structure

```text
src/class_scedule_lab4/
    ScheduleItem.java   - one schedule item
    Schedule.java       - the schedule (array of items)
    main.java           - test main
Makefile
```

## Build and run
To run this Java project on Windows, you must use a Unix-like terminal environment such as WSL or Git Bash. First, ensure you download and install a Java compiler (JDK) directly within your chosen environment. Once your setup is complete, execute 
``` WSL 
make build 
make run
```