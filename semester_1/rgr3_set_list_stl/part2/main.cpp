#include "rgr3.2.h"
#include <iostream>
#include <clocale>

int main() {
    std::setlocale(LC_ALL, "Russian");

    Library lib;
    lib.loadFromFile("input.txt");

    std::cout << "Ищем книгу с названием <Война и мир> :\n";
    lib.searchByTitle("Война и мир");

    
    std::cout << "Ищем все книги с авторством Достоевскго:\n";
    lib.searchByAuthor("Достоевский");

    std::list<Library::Book::Author> authors;
    authors.emplace_back("Толстой", "Лев", "Николаевич");
    Library::Book newBook(999, authors, "Анна Каренина", 1877);
    lib.addBook(newBook);

    std::cout << "После добавления ищем новую книгу:\n";
    lib.searchByTitle("Анна Каренина");

    lib.deleteBook("Алгебра");
    std::cout << "После удаления книги пытаемся её найти:\n";
    lib.searchByTitle("Алгебра");

    return 0;
}
