#ifndef LIBRARY_H
#define LIBRARY_H

#include <memory>
#include <functional>
#include <vector>
#include "Book.h"
#include "SortStrategy.h"

/**
 * Container class for storing and managing books.
 * Stores pointers to Book objects (FictionBook, NonFictionBook, AudioBook).
 */
class Library {
private:
    // pimpl — implementation hidden in Library.cpp
    struct Impl;
    std::unique_ptr<Impl> impl;

public:
    /** Constructs an empty library. */
    Library();

    /** Deep copy constructor — clones all books using Prototype pattern. */
    Library(const Library& other);

    /** Deep copy assignment operator. */
    Library& operator=(const Library& other);

    /** Destructor — deletes all books. */
    ~Library();

    //  CRUD
    /** Adds a book to the library. Library takes ownership of the pointer. */
    void add(Book* book);

    /** Removes and deletes the book at the given index. */
    void remove(int index);

    /** Returns the book at the given index. */
    Book* get(int index) const;

    /** Returns the number of books in the library. */
    int size() const;

    //  STRATEGY
    /** Sets the sorting strategy to be used by sort(). */
    void setStrategy(SortStrategy* strategy);

    /**
     * Sorts books using the currently set strategy.
     * Throws StrategyNotSet if no strategy has been set.
     */
    void sort();

    //  CALLBACK
    /**
     * Returns a list of books matching the given condition.
     */
    std::vector<Book*> filter(std::function<bool(Book*)> condition) const;


    //  POLYMORPHISM
    /** Calls describe() on every book in the library. Demonstrates polymorphism. */
    void describeAll() const;


    //  ITERATOR
    /**
     * ForwardIterator — allows iterating through books in order.
     * Iterator part was assited by AI (Claude)
     */
    class ForwardIterator {
    private:
        std::vector<Book*>* books;
        int index;

    public:
        // STL required types
        using iterator_category = std::forward_iterator_tag;
        using value_type        = Book*;
        using difference_type   = std::ptrdiff_t;
        using pointer           = Book**;
        using reference         = Book*&;

        ForwardIterator(std::vector<Book*>* books, int index);

        /** Dereferences the iterator — returns current book. */
        Book*& operator*();

        /** Prefix increment — moves to next book. */
        ForwardIterator& operator++();

        /** Postfix increment — moves to next book, returns old position. */
        ForwardIterator  operator++(int);

        /** Returns true if both iterators point to the same position. */
        bool operator==(const ForwardIterator& other) const;

        /** Returns true if iterators point to different positions. */
        bool operator!=(const ForwardIterator& other) const;
    };

    /** Returns iterator pointing to the first book. */
    ForwardIterator begin();

    /** Returns iterator pointing past the last book. */
    ForwardIterator end();

};

#endif // LIBRARY_H
