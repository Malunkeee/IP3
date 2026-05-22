#include "Book.h"
#include <iostream>


NonFictionBook::NonFictionBook(const std::string& title, const std::string& author, int year, int pages, const std::string& subject, const std::string& keyTopics)
    : Book(title, author, year, pages), subject(subject), keyTopics(keyTopics) {}

void NonFictionBook::describe() const {
    std::cout << "Non-Fiction Book" << std::endl;
    std::cout << "Title: " << title<< std::endl;
    std::cout << "Author: " << author<< std::endl;
    std::cout << "Subject: " << subject<< std::endl;
    std::cout << "Key Topics: " << keyTopics<< std::endl;
    std::cout << "Year: " << year<< std::endl;
    std::cout << "Pages: " << pages<< std::endl;
}

Book* NonFictionBook::clone() const {
    return new NonFictionBook(title, author, year, pages, subject, keyTopics);
}

const std::string& NonFictionBook::getSubject() const {
    return subject;
}

const std::string& NonFictionBook::getKeyTopics() const {
    return keyTopics;
}
