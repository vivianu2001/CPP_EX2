CXX=g++
CXXFLAGS=-std=c++11 -Werror
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all --error-exitcode=99

SOURCES=Graph.cpp Algorithms.cpp Demo.cpp Test.cpp TestCounter.cpp
OBJECTS=$(SOURCES:.cpp=.o)


run: demo
		./demo
demo: Demo.o Graph.o Algorithms.o
	$(CXX) $(CXXFLAGS) -o $@ $^

test: TestCounter.o Graph.o Algorithms.o Test.o
	$(CXX) $(CXXFLAGS) -o $@ $^
	./$@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


valgrind: demo test
	valgrind $(VALGRIND_FLAGS) ./demo
	valgrind $(VALGRIND_FLAGS) ./test

clean:
	rm -f $(OBJECTS) demo test

tidy:
	clang-tidy $(SOURCES) -- -$(CXXFLAGS)

.PHONY: all run demo test clean tidy valgrind