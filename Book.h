#ifndef BOOK_H
#define BOOK_H
#include <string>
#include <stdexcept>

/**
 * Thrown when a method is described but not yet implemented.
 */
class NotImplementedException : public std::logic_error {
public:
    explicit NotImplementedException(const std::string& msg)
        : std::logic_error(msg) {}
};

/**
 * Abstract base class for all book types in the library.
 */
class Book {
protected:
    std::string title;
    std::string author;
    int year;
    int pages;

public:
    /** Constructs a book with the given title, author, year and page count. */
    Book(const std::string& title, const std::string& author, int year, int pages);

    virtual ~Book() = default;

    /** Returns the title of the book. */
    const std::string& getTitle() const;

    /** Returns the author of the book. */
    const std::string& getAuthor() const;

    /** Returns the publication year of the book. */
    int getYear() const;

    /** Returns the number of pages in the book. */
    int getPages() const;

    /**
     * Prints a self-description of the book.
     * Each derived class provides different information.
     */
    virtual void describe() const = 0;

    /**
     * Prototype pattern: creates a deep copy of this object
     * without knowing its exact derived type.
     */
    virtual Book* clone() const = 0;

    /** Compares books alphabetically by title. Used for sorting. */
    bool operator<(const Book& other) const;
};

/**
 * Represents a fiction book.
 */
class FictionBook : public Book {
private:
    std::string genre;
    std::string plotSummary;

public:
    /** Constructs a fiction book with genre and plot summary. */
    FictionBook(const std::string& title, const std::string& author, int year, int pages,
                const std::string& genre, const std::string& plotSummary);

    /** Prints title, author, genre and plot summary. */
    void describe() const override;

    /** Returns a deep copy of this FictionBook. */
    Book* clone() const override;

    /** Returns the genre of the book. Child-only method. */
    const std::string& getGenre() const;

    /** Returns the plot summary of the book. Child-only method. */
    const std::string& getPlotSummary() const;
};

/**
 * Represents a non-fiction book.
 */
class NonFictionBook : public Book {
private:
    std::string subject;
    std::string keyTopics;

public:
    /** Constructs a non-fiction book with subject and key topics. */
    NonFictionBook(const std::string& title, const std::string& author, int year, int pages,
                   const std::string& subject, const std::string& keyTopics);

    /** Prints title, author, subject and key topics. */
    void describe() const override;

    /** Returns a deep copy of this NonFictionBook. */
    Book* clone() const override;

    /** Returns the subject area of the book. Child-only method. */
    const std::string& getSubject() const;

    /** Returns the key topics covered in the book. Child-only method. */
    const std::string& getKeyTopics() const;
};

/**
 * AudioBook — designed but NOT implemented.
 *
 * describe() must throw NotImplementedException.
 * clone()    must return a deep copy.
 */
class AudioBook : public Book {
private:
    std::string narrator;
    double durationHours;

public:
    /** Constructs an audio book with narrator and duration. */
    AudioBook(const std::string& title, const std::string& author, int year, int pages,
              const std::string& narrator, double durationHours);

    /** Throws NotImplementedException — not yet implemented. */
    void describe() const override;

    /** Returns a deep copy of this AudioBook. */
    Book* clone() const override;

    /** Returns the name of the narrator. Child-only method. */
    const std::string& getNarrator() const;

    /** Returns the duration of the audiobook in hours. Child-only method. */
    double getDurationHours() const;
};

#endif // BOOK_H
