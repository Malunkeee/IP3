#ifndef SORTSTRATEGY_H
#define SORTSTRATEGY_H

#include <vector>
#include "Book.h"

/**
 * Thrown when sort() is called but no strategy has been set.
 */
class StrategyNotSet : public std::logic_error {
public:
    explicit StrategyNotSet(const std::string& msg)
        : std::logic_error(msg) {}
};

/**
 * Abstract base class for all sorting strategies.
 */
class SortStrategy {
public:
    virtual ~SortStrategy() = default;

    /** Sorts the given list of books according to this strategy. */
    virtual void sort(std::vector<Book*>& books) const = 0;
};

/** Sorts books alphabetically by title (ascending). */
class SortByTitle : public SortStrategy {
public:
    void sort(std::vector<Book*>& books) const override;
};

/** Sorts books alphabetically by author name (ascending). */
class SortByAuthor : public SortStrategy {
public:
    void sort(std::vector<Book*>& books) const override;
};

/** Sorts books by publication year (ascending). */
class SortByYear : public SortStrategy {
public:
    void sort(std::vector<Book*>& books) const override;
};

#endif // SORTSTRATEGY_H
