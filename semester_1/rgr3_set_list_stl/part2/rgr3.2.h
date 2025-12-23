#pragma once
#include <string>
#include <list>

class Library {
public:
	class Book {
	public:
		struct Author {
			std::string surname_;
			std::string name_;
			std::string patronymic_;

			Author(const std::string& surname, const std::string& name, const std::string& patronymic);
			bool operator<(const Author& other) const;
		};

		Book(int udk, const std::list<Author>& authors, const std::string& title, size_t year);
		bool operator<(const Book& other) const;

		const std::string& getTitle() const;
		const std::list<Author>& getAuthors() const;

		void addAuthor(const Author& author);
		void removeAuthor(const std::string& surname);
		void print() const;

	private:
		int udk_;
		std::list<Author> authors_;
		const std::string title_;
		size_t year_;
	};

	void addBook(const Book& book);
	void deleteBook(const std::string& title);
	void searchByTitle(const std::string& title) const;
	void searchByAuthor(const std::string& surname) const;
	void loadFromFile(const std::string& filename);


private:
	std::list<Book> library;
};