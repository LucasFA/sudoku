
CXX:=g++-10
CXXFLAGS:=-Wall -std=c++20 -g

RM:=trash-put
RMFLAGS:=

SRC:=src
OBJ:=obj
SRCS := $(wildcard $(SRC)/*.cpp)
OBJS := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))

BINDIR:=bin
BIN := $(BINDIR)/main.out

all:$(BIN)

$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

obj/main.o: src/main.cpp src/Board.h src/config.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/Board.o: src/Board.cpp src/Board.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/Cell.o: src/Cell.cpp src/Cell.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(RMFLAGS) $(BINDIR)/* $(OBJ)/*