#include "Library.h"
#include <iostream>
#include <stdexcept>


struct Library::Impl {
    std::vector<Book*> books;
    SortStrategy* strategy = nullptr;
};


Library::Library()
    : impl(std::make_unique<Impl>()) {}

Library::Library(const Library& other)
    : impl(std::make_unique<Impl>()) {
    // deep copy — kiekvieną knygą klonuojam
    for (Book* book : other.impl->books) {
        try {
            impl->books.push_back(book->clone());
        } catch (const NotImplementedException&) {
            // AudioBook dar neimplementuota — praleidžiame
        }
    }
    impl->strategy = other.impl->strategy;
}

Library& Library::operator=(const Library& other) {
    if (this == &other) return *this;
    // išvalome senus duomenis
    for (Book* book : impl->books) {
        delete book;
    }
    impl->books.clear();
    // klonuojam naujus
    for (Book* book : other.impl->books) {
        try {
            impl->books.push_back(book->clone());
        } catch (const NotImplementedException&) {
            // AudioBook dar neimplementuota — praleidžiame
        }
    }
    impl->strategy = other.impl->strategy;
    return *this;
}

Library::~Library() {
    for (Book* book : impl->books) {
        delete book;
    }
}

void Library::add(Book* book) {
    impl->books.push_back(book);
}

void Library::remove(int index) {
    if (index < 0 || index >= (int)impl->books.size()){
        throw std::out_of_range("Index out of range.");
    }
    delete impl->books[index];
    impl->books.erase(impl->books.begin() + index);
}

Book* Library::get(int index) const {
    if (index < 0 || index >= (int)impl->books.size()){
        throw std::out_of_range("Index out of range.");
    }
    return impl->books[index];
}

int Library::size() const {
    return (int)impl->books.size();
}

void Library::setStrategy(SortStrategy* strategy) {
    impl->strategy = strategy;
}

void Library::sort() {
    if (impl->strategy == nullptr){
        throw StrategyNotSet("Sort strategy is not set.");
    }
    impl->strategy->sort(impl->books);
}


std::vector<Book*> Library::filter(std::function<bool(Book*)> condition) const {
    std::vector<Book*> result;
    for (Book* book : impl->books) {
        if (condition(book)) {
            result.push_back(book);
        }
    }
    return result;
}


void Library::describeAll() const {
    for (Book* book : impl->books) {
        try {
            book->describe();
        } catch (const NotImplementedException& e) {
            std::cout << "Not implemented: " << e.what() << std::endl;
        }
        std::cout << std::endl;
    }
}


Library::ForwardIterator::ForwardIterator(std::vector<Book*>* books, int index)
    : books(books), index(index) {}

Book*& Library::ForwardIterator::operator*() {
    return (*books)[index];
}

Library::ForwardIterator& Library::ForwardIterator::operator++() {
    ++index;
    return *this;
}

Library::ForwardIterator Library::ForwardIterator::operator++(int) {
    ForwardIterator tmp = *this;
    ++index;
    return tmp;
}

bool Library::ForwardIterator::operator==(const ForwardIterator& other) const {
    return index == other.index;
}

bool Library::ForwardIterator::operator!=(const ForwardIterator& other) const {
    return index != other.index;
}

Library::ForwardIterator Library::begin() {
    return ForwardIterator(&impl->books, 0);
}

Library::ForwardIterator Library::end() {
    return ForwardIterator(&impl->books, (int)impl->books.size());
}
