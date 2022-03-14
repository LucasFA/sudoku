# Opciones de compilador
CXX:=g++-10
CXXFLAGS:=-Wall -std=c++20 -g
# Opciones de borrado
RM:=rm
RMFLAGS:=
# Localización del código fuente y su lista
SRCDIR:=src
SRCS := $(wildcard $(SRCDIR)/*.cpp)
# Localización de objetos compilados pre-linkeo
OBJDIR:=obj
OBJS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
# Localización del programa final
BINDIR:=bin
BIN := $(BINDIR)/main.out
# ────────────────────────────────────────────────────────────────────────────────
.PHONY: clean run

all:$(BIN)

run: all
	./$(BIN)

# ────────────────────────────────────────────────────────────────────────────────
# Linkeo
$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Crea la lista de dependencias para cada archivo .o
DEPENDS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.d, $(SRCS))
# Añade todas esas dependencias como reglas. No avisa si no existen.
-include $(DEPENDS) 

# Crea los objetos compilados %.o y el archivo %.d de sus dependencias
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp Makefile
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

clean:
	$(RM) $(RMFLAGS) $(BINDIR)/* $(OBJDIR)/*