APPNAME := sudokuSolver

CXX := g++-10
CXXFLAGS := -Wall -std=c++20 -g

SRC := main.cpp Board.cpp Cell.cpp
OBJS := $(subst .cpp,.o,$(SRC))

HEADERS := Board.h Cell.h

$(APPNAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(APPNAME) $(OBJS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Board.o: Board.cpp Board.h
	$(CXX) $(CXXFLAGS) -c Board.cpp

Cell.o: Cell.cpp Cell.h
	$(CXX) $(CXXFLAGS) -c Cell.cpp

clean:
	rm -f *.o $(APPNAME)