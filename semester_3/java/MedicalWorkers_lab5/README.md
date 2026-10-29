# ambulance_app

A localized Java console application that models an ambulance station: medical workers, duty teams, and saving/loading them with Java serialization.

## Task

**Stage 1.** Design the classes of the problem domain with constructors, fields and methods, and implement them in a console application. Save the objects to a file using serialization (objects may contain `static` and `transient` fields). Create a special connector class for reading and changing data in the file. Handle exceptions caused by lack of memory, a missing record in the file, an invalid field value, etc.

**Stage 2.** Add a `Date` field with the creation time to each domain class and print it. Localize the application at least for Russian (Russia), Belarusian (Belarus) and English (United Kingdom); the language and region are passed as command-line parameters. Create the abstract class `MedicalWorker` with the subclasses `Nurse`, `Feldsher` and `Doctor` (with the subclasses `Therapist`, `Cardiologist`, `Surgeon`). Create an array of medical workers of the ambulance station. Create the class `Team` made of one doctor and one nurse or feldsher. Create an array of several teams of different profiles and print the duty roster.

## How it works

* `MedicalWorker` is an abstract class that stores the worker's name and the creation time (`Date`). It implements `Serializable`.
* `Nurse`, `Feldsher` and `Doctor` extend `MedicalWorker`; `Therapist`, `Cardiologist` and `Surgeon` extend `Doctor`.
* The static field `count` counts created workers. The `transient` field `info` is not saved to the file, so it is empty after reading.
* An empty or `null` name causes `IllegalArgumentException` with the message key `error.invalid_name`.
* `Team` holds one `Doctor` and one helper (`Nurse` or `Feldsher`) and its own creation time. The constructor throws `IllegalArgumentException` (`error.no_doctor`, `error.no_helper`) if the composition is wrong.
* `Connector` works with a file through `ObjectOutputStream` / `ObjectInputStream`:
  * `write(Team[])` writes the number of teams and then every team;
  * `read()` reads all teams from the file;
  * `read(int index)` returns one team and throws `NoSuchElementException` (`error.file_not_found`) if there is no such record.
* Localization uses `ResourceBundle` with the base name `medical.Msg`. The locale is created from the command-line arguments (`language [country]`); without arguments the system default is used. Dates are formatted with `DateFormat` for the chosen locale.
* Error messages are stored as keys in the exception and translated in `main`. `OutOfMemoryError` is handled separately.
* The test application (`main`) creates the workers and the array of workers, forms the teams, saves them to `teams_stage2.dat`, reads them back, prints the duty roster with creation times, demonstrates a missing record, and prints the number of created workers.