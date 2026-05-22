#include "Book.h"

NotImplementedException::NotImplementedException(const std::string& msg)
    : std::logic_error(msg) {}

Book::Book(const std::string& title, const std::string& author, int year, int pages)
    : title(title), author(author), year(year), pages(pages) {}

const std::string& Book::getTitle() const {
    return title;
}
const std::string& Book::getAuthor() const {
    return author;
}
int Book::getYear() const {
    return year;
}
int Book::getPages() const {
    return pages;
}
bool Book::operator<(const Book& other) const {
    return title < other.title;
}
