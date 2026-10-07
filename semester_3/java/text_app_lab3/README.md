# text_app

A Java console application for storing and processing text as a sequence of sentences.

## Task

Develop a class `text` that stores a sequence of sentences. Use `assert` and exceptions to handle error situations where possible. Develop a separate test application that exercises all constructors and methods and prints the data and results. Provide a Makefile with the targets `clean`, `build` and `run`.

Required functionality:

- several constructors;
- add a sentence;
- delete a sentence;
- insert a sentence;
- count letters, words and sentences;
- check whether two texts are equal.



## Class `text`

| Method / constructor | Description |
|---|---|
| `text()` | creates an empty text |
| `text(String)` | creates a text from a string (split into sentences automatically) |
| `text(List<String>)` | creates a text from a list of sentences |
| `text(text)` | copy constructor |
| `addSentence(String)` | appends a sentence to the end |
| `insertSentence(int, String)` | inserts a sentence at the given position |
| `removeSentence(int)` | removes and returns the sentence at the given index |
| `getSentence(int)` / `getSentences()` | returns one sentence / an unmodifiable list of sentences |
| `getSentenceCount()` | number of sentences |
| `getWordCount()` | number of words |
| `getLetterCount()` | number of letters (digits, spaces and punctuation are not counted) |
| `equals(Object)` / `hashCode()` | two texts are equal if their sentence sequences are equal |
| `toString()` | all sentences joined by a space |


In the counting test, the text has 3 sentences, 7 words (`Hello`, `world`, `Это`, `тест-проверка`, `Раз`, `два`, `три`) and 34 letters.

## How it works

1. A text is stored internally as a `List<String>` of sentences.
2. When a text is created from a string, it is split into sentences with the regular expression `(?<=[.!?])\s+`, i.e. after `.`, `!` or `?` followed by whitespace.
3. Every sentence is normalized before it is stored: leading and trailing spaces are trimmed, and a period is appended if the sentence has no ending `.`, `!` or `?`.
4. Words are counted with the pattern `[\p{L}\p{N}]+(?:[-'][\p{L}\p{N}]+)*`, so a hyphenated word such as `тест-проверка` counts as one word. Letters are counted with `Character.isLetter`.
5. `insertSentence` accepts positions from `0` to `size` (`size` means insert at the end). `removeSentence` and `getSentence` accept positions from `0` to `size - 1`.
6. `textApp` calls every constructor and method with prepared data, prints the results, and then deliberately triggers error situations inside `try/catch` blocks, printing the exception messages.


 ## How to run
To run this Java project on Windows, you must use a Unix-like terminal environment such as WSL or Git Bash. First, ensure you download and install a Java compiler (JDK) directly within your chosen environment. Once your setup is complete, execute 
``` WSL 
make build 
make run
```