#include <iostream>
#include <algorithm>
#include "Book.h"
#include "Library.h"
#include "SortStrategy.h"

int main() {

    Library lib;

    lib.add(new FictionBook("Dune", "Frank Herbert", 1965, 412, "Sci-Fi", "A desert planet holds the universe's most valuable resource."));
    lib.add(new NonFictionBook("A Brief History of Time", "Stephen Hawking", 1988, 212, "Physics", "Black holes, Big Bang, space and time."));
    lib.add(new FictionBook("1984", "George Orwell", 1949, 328, "Dystopia", "A totalitarian society where Big Brother watches everyone."));
    lib.add(new NonFictionBook("Sapiens", "Yuval Noah Harari", 2011, 443, "History", "Evolution of humans, agriculture, science, and empires."));

    std::cout << "All books" << std::endl;
    // polymorphism
    lib.describeAll();


    std::cout << "Dynamic cast" << std::endl;
    for (int i = 0; i < lib.size(); i++) {
        Book* b = lib.get(i);

        FictionBook* fb = dynamic_cast<FictionBook*>(b);
        if (fb != nullptr) {
            std::cout << "Fiction plot: " << fb->getPlotSummary() << std::endl;
        }

        NonFictionBook* nfb = dynamic_cast<NonFictionBook*>(b);
        if (nfb != nullptr) {
            std::cout << "Non-fiction topics: " << nfb->getKeyTopics() << std::endl;
        }
    }

    std::cout << "\nSort by title" << std::endl;
    SortByTitle byTitle;
    // strategy
    lib.setStrategy(&byTitle);
    lib.sort();
    for (int i = 0; i < lib.size(); i++) {
        std::cout << lib.get(i)->getTitle() << std::endl;
    }

    std::cout << "\nSort by year" << std::endl;
    SortByYear byYear;
    lib.setStrategy(&byYear);
    lib.sort();
    for (int i = 0; i < lib.size(); i++) {
        std::cout << lib.get(i)->getYear() << " - " << lib.get(i)->getTitle() << std::endl;
    }

    std::cout << "\nBooks after 2000" << std::endl;
    // callback
    auto afterY2K = lib.filter([](Book* b) {
        return b->getYear() > 2000;
    });
    for (Book* b : afterY2K) {
        std::cout << b->getTitle() << " (" << b->getYear() << ")" << std::endl;
    }

    std::cout << "\nBooks with more than 300 pages" << std::endl;
    auto longBooks = lib.filter([](Book* b) {
        return b->getPages() > 300;
    });
    for (Book* b : longBooks) {
        std::cout << b->getTitle() << " (" << b->getPages() << " pages)" << std::endl;
    }

    std::cout << "\nIterator" << std::endl;
    // iterator
    std::for_each(lib.begin(), lib.end(), [](Book* b) {
        std::cout << b->getTitle() << " by " << b->getAuthor() << std::endl;
    });

    std::cout << "\nDeep copy" << std::endl;
    // deep copy
    Library libCopy = lib;
    std::cout << "Original size: " << lib.size() << std::endl;
    std::cout << "Copy size: " << libCopy.size() << std::endl;
    std::cout << "Copy first book: " << libCopy.get(0)->getTitle() << std::endl;


    std::cout << "\nStrategy not set" << std::endl;
    try {
        Library lib2;
        lib2.add(new FictionBook("Test", "Author", 2020, 100, "Genre", "Plot"));
        lib2.sort();
    } catch (const StrategyNotSet& e) {
        std::cout << "Caught: " << e.what() << std::endl;
    }

    return 0;
}
