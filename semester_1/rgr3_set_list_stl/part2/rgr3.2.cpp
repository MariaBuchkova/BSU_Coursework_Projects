#include "rgr3.2.h"
#include <iostream>

Library::Book::Author::Author(const std::string& surname, const std::string& name, const std::string& patronymic) : 
	surname_(surname), name_(name), patronymic_(patronymic) {}
bool Library::Book::Author::operator<(const Author& other) const {
	return surname_ < other.surname_;
}

bool Library::Book::operator<(const Book& other) const {
	return title_ < other.title_;
}
const std::string& Library::Book::getTitle() const { 
	return title_;
}
const std::list<Library::Book::Author>& Library::Book::getAuthors() const { 
	return authors_;
}


Library::Book::Book(int udk, const std::list<Author>& authors, const std::string& title, size_t year) :
	udk_(udk), authors_(authors), title_(title), year_(year) {}
void Library::Book::addAuthor(const Author& author) { 
	authors_.push_back(author); 
	authors_.sort();
} 
void Library::Book::removeAuthor(const std::string& surname) {
	authors_.remove_if([&](const Author& x) {return x.surname_ == surname; });
}
void Library::Book::print() const {
	std::cout << "УДК: " << udk_ << "\nНазвание: " << title_ << "\nГод: " << year_ << "\nАвторы:\n"; 
	for (std::list<Author>::const_iterator it = authors_.cbegin(); it != authors_.cend(); ++it) {
		std::cout << it->surname_ << " " << it->name_ << " " << it->patronymic_ << "\n";
	}
	std::cout << "----------------------\n";
}


void Library::addBook(const Book& book) { 
	library.push_back(book); 
	library.sort(); 
} 
void Library::deleteBook(const std::string& title) {
	library.remove_if([&](const Book& x){ return x.getTitle() == title; });
} 
void Library::searchByTitle(const std::string& title) const {
	for (std::list<Book>::const_iterator it = library.cbegin(); it != library.cend(); ++it) {
		if (it->getTitle() == title) {
			it->print();
		}
	}
}
void Library::searchByAuthor(const std::string& surname) const {
	for (std::list<Book>::const_iterator it = library.cbegin(); it != library.cend(); ++it) {
		const std::list<Library::Book::Author>& authors = it->getAuthors();
		for (std::list<Library::Book::Author>::const_iterator ait = authors.cbegin(); ait != authors.cend(); ++ait) {
			if (ait->surname_ == surname) {
				it->print();
				break; 
			}
		}
	}
}
