
CXX := g++-10
CXXFLAGS := -Wall -std=c++20 -g

SRC:=src
OBJ:=obj
SRCS := $(wildcard $(SRC)/*.cpp)
OBJS := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o,$(SRCS))

BINDIR:=bin
BIN := $(BINDIR)/main

all:$(BIN)

$(BIN):$(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -r $(BINDIR)/* $(OBJ)/*