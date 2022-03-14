
CXX:=g++-10
CXXFLAGS:=-Wall -std=c++20 -g

RM:=rm
RMFLAGS:=

SRCDIR:=src
OBJDIR:=obj
SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))

BINDIR:=bin
BIN := $(BINDIR)/main.out

.PHONY: clean prep run

all:$(BIN)

run: all
	./$(BIN)


$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

prep: $(OBJS)

DEPENDS := $(patsubst $(SRCDIR)%.cpp, $(OBJDIR)%.d, $(SRCS))

-include $(DEPENDS) # executes all those: main.d, Cell.d, Board.d makefiles, if they exist

# creates all those dependency files execute in the include $(DEPENDS)
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp Makefile
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# That does the same as:

# obj/main.o: src/main.cpp
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# obj/Board.o: src/Board.cpp
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# obj/Cell.o: src/Cell.cpp
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# If you change this, make a test run with RM := trash-put
clean:
	$(RM) $(RMFLAGS) $(BINDIR)/* $(OBJDIR)/*