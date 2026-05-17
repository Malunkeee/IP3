#include "Book.h"
#include <iostream>

FictionBook::FictionBook(const std::string& title, const std::string& author, int year, int pages, const std::string& genre, const std::string& plotSummary)
    : Book(title, author, year, pages), genre(genre), plotSummary(plotSummary) {}

void FictionBook::describe() const {
    std::cout << "Fiction Book" << std::endl;
    std::cout << "Title: " << title<< std::endl;
    std::cout << "Author: " << author<< std::endl;
    std::cout << "Genre: " << genre<< std::endl;
    std::cout << "Plot: " << plotSummary << std::endl;
    std::cout << "Year: " << year << std::endl;
    std::cout << "Pages: " << pages << std::endl;
}

Book* FictionBook::clone() const {
    return new FictionBook(*this);
}

const std::string& FictionBook::getGenre() const {
    return genre;
}

const std::string& FictionBook::getPlotSummary() const {
    return plotSummary;
}
