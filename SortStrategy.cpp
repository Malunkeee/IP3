#include "SortStrategy.h"
#include <algorithm>

void SortByTitle::sort(std::vector<Book*>& books) const {
    std::sort(books.begin(), books.end(), [](Book* a, Book* b) {
        return a->getTitle() < b->getTitle();
    });
}

void SortByAuthor::sort(std::vector<Book*>& books) const {
    std::sort(books.begin(), books.end(), [](Book* a, Book* b) {
        return a->getAuthor() < b->getAuthor();
    });
}

void SortByYear::sort(std::vector<Book*>& books) const {
    std::sort(books.begin(), books.end(), [](Book* a, Book* b) {
        return a->getYear() < b->getYear();
    });
}
