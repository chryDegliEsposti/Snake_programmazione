# Compilatore e flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I./src -MMD -MP -g
LDFLAGS = -lncurses

# Struttura delle directory
SRC_DIR = src
TEST_DIR = tests
OBJ_DIR = build
BIN = app
TEST_BIN = app_tests

# --- SORGENTI APP ---
# Trova tutti i .cpp sotto src/
SRCS = $(shell find $(SRC_DIR) -name '*.cpp')
# Crea i .o corrispondenti sotto build/
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
DEPS = $(OBJS:.o=.d)

# Escludi main.o quando linki i test (evita "multiple definition of main")
MAIN_OBJ = $(OBJ_DIR)/main.o
OBJS_NO_MAIN = $(filter-out $(MAIN_OBJ),$(OBJS))

# --- SORGENTI TEST ---
# Tutti i test singoli in tests/*.cpp
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp,$(OBJ_DIR)/tests/%.o,$(TEST_SRCS))
TEST_DEPS = $(TEST_OBJS:.o=.d)

# Regola principale
.PHONY: all
all: $(BIN)

# Link finale app
$(BIN): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Compila i .cpp in .o (sorgenti dell'app)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compila i test .cpp in .o (sorgenti dei test)
$(OBJ_DIR)/tests/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link binario dei test:
# usa tutti gli object della app tranne main.o + gli object dei test
$(TEST_BIN): $(OBJS_NO_MAIN) $(TEST_OBJS)
	$(CXX) $(OBJS_NO_MAIN) $(TEST_OBJS) -o $@ $(LDFLAGS)

# Target "tests" per costruire i test
.PHONY: tests
tests: $(TEST_BIN)

# Target "run-tests" per eseguire i test
.PHONY: run-tests
run-tests: $(TEST_BIN)
	./$(TEST_BIN)

# Pulizia
.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(BIN) $(TEST_BIN)

# Include dipendenze degli header
-include $(DEPS)
-include $(TEST_DEPS)
