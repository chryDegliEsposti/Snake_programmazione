# Compilatore e flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I./src -MMD -MP
LDFLAGS = -lncurses

# Struttura delle directory
SRC_DIR = src
OBJ_DIR = build
BIN = app

# Trova tutti i .cpp sotto src/
SRCS = $(shell find $(SRC_DIR) -name '*.cpp')
# Crea i .o corrispondenti sotto build/
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
DEPS = $(OBJS:.o=.d)

# Regola principale
all: $(BIN)

# Link finale
$(BIN): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Compila i .cpp in .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Pulizia
clean:
	rm -rf $(OBJ_DIR) $(BIN)

# Include dipendenze degli header
-include $(DEPS)
