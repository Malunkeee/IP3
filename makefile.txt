CXX = g++
CXXFLAGS = -std=c++14 -Wall

# Source files
OBJS = Book.o FictionBook.o NonFictionBook.o SortStrategy.o Library.o

# a) Build module.o
module.o: $(OBJS)
	$(CXX) $(CXXFLAGS) -c Book.cpp FictionBook.cpp NonFictionBook.cpp SortStrategy.cpp Library.cpp

# b) Build demo
demo: $(OBJS) demo.o
	$(CXX) $(CXXFLAGS) -o demo $(OBJS) demo.o

demo.o: demo.cpp
	$(CXX) $(CXXFLAGS) -c demo.cpp

# c) Run demo
run_demo: demo
	./demo

# d) Build test
test: $(OBJS) test.o
	$(CXX) $(CXXFLAGS) -o test $(OBJS) test.o

test.o: test.cpp
	$(CXX) $(CXXFLAGS) -c test.cpp

# e) Run test
run_test: test
	./test

# Individual object files
Book.o: Book.cpp Book.h
	$(CXX) $(CXXFLAGS) -c Book.cpp

FictionBook.o: FictionBook.cpp Book.h
	$(CXX) $(CXXFLAGS) -c FictionBook.cpp

NonFictionBook.o: NonFictionBook.cpp Book.h
	$(CXX) $(CXXFLAGS) -c NonFictionBook.cpp

SortStrategy.o: SortStrategy.cpp SortStrategy.h
	$(CXX) $(CXXFLAGS) -c SortStrategy.cpp

Library.o: Library.cpp Library.h
	$(CXX) $(CXXFLAGS) -c Library.cpp

# f) Clean
clean:
	rm -f *.o demo test

# g) Rebuild from scratch
rebuild: clean demo test
