CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I./src -MMD -MP -g
LDFLAGS = -lncurses

SRC_DIR = src
TEST_DIR = tests
OBJ_DIR = build
BIN = app
TEST_BIN = app_tests

SRCS = $(shell find $(SRC_DIR) -name '*.cpp')
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
DEPS = $(OBJS:.o=.d)

MAIN_OBJ = $(OBJ_DIR)/main.o
OBJS_NO_MAIN = $(filter-out $(MAIN_OBJ),$(OBJS))

TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp,$(OBJ_DIR)/tests/%.o,$(TEST_SRCS))
TEST_DEPS = $(TEST_OBJS:.o=.d)

.PHONY: all
all: $(BIN)

$(BIN): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/tests/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TEST_BIN): $(OBJS_NO_MAIN) $(TEST_OBJS)
	$(CXX) $(OBJS_NO_MAIN) $(TEST_OBJS) -o $@ $(LDFLAGS)

.PHONY: tests
tests: $(TEST_BIN)

.PHONY: run-tests
run-tests: $(TEST_BIN)
	./$(TEST_BIN)

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(BIN) $(TEST_BIN)

-include $(DEPS)
-include $(TEST_DEPS)
