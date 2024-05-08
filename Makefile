CXX=g++
CXXFLAGS=-std=c++11 -Werror -Wsign-conversion
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all --error-exitcode=99

SOURCES=Graph.cpp Algorithms.cpp Demo.cpp Test.cpp main.cpp TestCounter.cpp

OBJECTS=$(SOURCES:.cpp=.o)

all: program run
program: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

run: program
	./program

valgrind: program
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./program 2>&1 | { egrep "lost| at " || true; }

clean:
	rm -f $(OBJECTS) program

tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,performance-*,portability-*,-cppcoreguidelines-avoid-magic-numbers,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --


.PHONY: all run program clean tidy valgrind