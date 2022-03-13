
CXX:=g++-10
CXXFLAGS:=-Wall -std=c++20 -g

RM:=rm
RMFLAGS:=

SRC:=src
OBJ:=obj
SRCS := $(wildcard $(SRC)/*.cpp)
OBJS := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))

BINDIR:=bin
BIN := $(BINDIR)/main.out

.PHONY: clean prep
all:$(BIN)

$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

prep: $(OBJS)

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# That does the same as:

# obj/main.o: src/main.cpp
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# obj/Board.o: src/Board.cpp
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# obj/Cell.o: src/Cell.cpp
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# If you change this, make a test run with RM := trash-put
clean:
	$(RM) $(RMFLAGS) $(BINDIR)/* $(OBJ)/*