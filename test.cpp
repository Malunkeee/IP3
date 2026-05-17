#include <iostream>
#include "Book.h"
#include "Library.h"
#include "SortStrategy.h"

void printResult(const std::string& testName, bool passed) {
    std::cout << (passed ? "[PASS] " : "[FAIL] ") << testName << std::endl;
}

void testFictionBook() {
    FictionBook fb("Dune", "Frank Herbert", 1965, 412, "Sci-Fi", "A desert planet story.");

    printResult("FictionBook getTitle", fb.getTitle() == "Dune");
    printResult("FictionBook getAuthor", fb.getAuthor() == "Frank Herbert");
    printResult("FictionBook getYear", fb.getYear() == 1965);
    printResult("FictionBook getPages", fb.getPages() == 412);
    printResult("FictionBook getGenre", fb.getGenre() == "Sci-Fi");
    printResult("FictionBook getPlotSummary", fb.getPlotSummary() == "A desert planet story.");
}

void testNonFictionBook() {
    NonFictionBook nfb("Sapiens", "Yuval Noah Harari", 2011, 443, "History", "Human evolution.");

    printResult("NonFictionBook getTitle", nfb.getTitle() == "Sapiens");
    printResult("NonFictionBook getAuthor", nfb.getAuthor() == "Yuval Noah Harari");
    printResult("NonFictionBook getSubject", nfb.getSubject() == "History");
    printResult("NonFictionBook getKeyTopics", nfb.getKeyTopics() == "Human evolution.");
}

void testClone() {
    FictionBook fb("1984", "George Orwell", 1949, 328, "Dystopia", "Big Brother is watching.");
    Book* copy = fb.clone();

    printResult("FictionBook clone title", copy->getTitle()  == "1984");
    printResult("FictionBook clone author", copy->getAuthor() == "George Orwell");
    printResult("FictionBook clone independent", copy != &fb);

    delete copy;
}


void testCRUD() {
    Library lib;
    lib.add(new FictionBook("Dune", "Frank Herbert", 1965, 412, "Sci-Fi", "Desert planet."));
    lib.add(new NonFictionBook("Sapiens", "Harari", 2011, 443, "History", "Evolution."));

    printResult("Library add / size", lib.size() == 2);
    printResult("Library get title",  lib.get(0)->getTitle() == "Dune");

    lib.remove(0);
    printResult("Library remove", lib.size() == 1);
    printResult("Library after remove", lib.get(0)->getTitle() == "Sapiens");
}

void testDeepCopy() {
    Library lib;
    lib.add(new FictionBook("Dune", "Frank Herbert", 1965, 412, "Sci-Fi", "Desert planet."));

    Library libCopy = lib;
    printResult("Deep copy size", libCopy.size() == lib.size());
    printResult("Deep copy title", libCopy.get(0)->getTitle() == lib.get(0)->getTitle());
    printResult("Deep copy independent", libCopy.get(0) != lib.get(0));
}

void testStrategy() {
    Library lib;
    lib.add(new FictionBook("Zebra", "Author C", 2000, 100, "Genre", "Plot."));
    lib.add(new FictionBook("Apple", "Author A", 1990, 200, "Genre", "Plot."));
    lib.add(new FictionBook("Mango", "Author B", 2010, 300, "Genre", "Plot."));

    SortByTitle byTitle;
    lib.setStrategy(&byTitle);
    lib.sort();
    printResult("SortByTitle first", lib.get(0)->getTitle() == "Apple");
    printResult("SortByTitle last",  lib.get(2)->getTitle() == "Zebra");

    SortByYear byYear;
    lib.setStrategy(&byYear);
    lib.sort();
    printResult("SortByYear first", lib.get(0)->getYear() == 1990);
    printResult("SortByYear last",  lib.get(2)->getYear() == 2010);

    SortByAuthor byAuthor;
    lib.setStrategy(&byAuthor);
    lib.sort();
    printResult("SortByAuthor first", lib.get(0)->getAuthor() == "Author A");
}

void testStrategyNotSet() {
    Library lib;
    lib.add(new FictionBook("Test", "Author", 2020, 100, "Genre", "Plot."));

    bool threw = false;
    try {
        lib.sort();
    } catch (const StrategyNotSet&) {
        threw = true;
    }
    printResult("StrategyNotSet exception", threw);
}

void testCallback() {
    Library lib;
    lib.add(new FictionBook("Old Book",  "Author", 1990, 100, "Genre", "Plot."));
    lib.add(new FictionBook("New Book",  "Author", 2005, 500, "Genre", "Plot."));
    lib.add(new NonFictionBook("Another", "Author", 2015, 250, "History", "Topics."));

    auto afterY2K = lib.filter([](Book* b) { return b->getYear() > 2000; });
    printResult("Callback filter by year",  (int)afterY2K.size() == 2);

    auto longBooks = lib.filter([](Book* b) { return b->getPages() > 300; });
    printResult("Callback filter by pages", (int)longBooks.size() == 1);
    printResult("Callback filter title",    longBooks[0]->getTitle() == "New Book");
}

void testIterator() {
    Library lib;
    lib.add(new FictionBook("Book A", "Author", 2000, 100, "Genre", "Plot."));
    lib.add(new FictionBook("Book B", "Author", 2001, 200, "Genre", "Plot."));
    lib.add(new FictionBook("Book C", "Author", 2002, 300, "Genre", "Plot."));

    int count = 0;
    for (auto it = lib.begin(); it != lib.end(); ++it) {
        count++;
    }
    printResult("Iterator count", count == 3);
}

//  AUDIOBOOK TESTS (for colleague)
//
//
//  void testAudioBook() {
//      AudioBook ab("Harry Potter", "J.K. Rowling", 1997, 332, "Jim Dale", 8.5);
//
//      // getter's
//      assert(ab.getNarrator() == "Jim Dale");
//      assert(ab.getDurationHours() == 8.5);
//      assert(ab.getTitle() == "Harry Potter");
//
//      // describe() should print:
//      // Audio Book
//      //   Title: Harry Potter
//      //   Author: J.K. Rowling
//      //   Narrator: Jim Dale
//      //   Duration: 8.5 hours
//      //   Year: 1997
//      //   Pages: 332
//      ab.describe();
//
//      // clone() should return independant copy
//      Book* copy = ab.clone();
//      assert(copy->getTitle() == "Harry Potter");
//      assert(copy != &ab);
//      delete copy;
//
//      // AudioBook should work in Library container
//      Library lib;
//      lib.add(new AudioBook("Harry Potter", "J.K. Rowling", 1997, 332, "Jim Dale", 8.5));
//      assert(lib.size() == 1);
//      lib.describeAll();
//  }

int main() {
    std::cout << "Hierarchy tests" << std::endl;
    testFictionBook();
    testNonFictionBook();
    testClone();

    std::cout << "\nContainer tests" << std::endl;
    testCRUD();
    testDeepCopy();
    testStrategy();
    testStrategyNotSet();
    testCallback();
    testIterator();

    return 0;
}
