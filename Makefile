CXXFLAGS ?= -std=c++17 -Wall -Wextra -O2
CPPFLAGS += -Iinclude

SRCS      := $(wildcard src/*.cpp)
OBJS      := $(SRCS:src/%.cpp=build/%.o)
GAME_OBJS := $(filter-out build/main.o,$(OBJS))
HEADERS   := $(wildcard include/*.h)

TEST_SRCS := $(wildcard tests/*.cpp)
TEST_OBJS := $(TEST_SRCS:tests/%.cpp=build/tests/%.o)
CATCH_DIR := third_party/catch2
CATCH_OBJ := build/catch_amalgamated.o

px: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

build/%.o: src/%.cpp $(HEADERS) | build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

build/tests/%.o: tests/%.cpp $(HEADERS) | build/tests
	$(CXX) $(CPPFLAGS) -I$(CATCH_DIR) $(CXXFLAGS) -c $< -o $@

# Catch2 itself is third-party code, so it's built once without our warning flags.
$(CATCH_OBJ): $(CATCH_DIR)/catch_amalgamated.cpp $(CATCH_DIR)/catch_amalgamated.hpp | build
	$(CXX) -std=c++17 -O2 -I$(CATCH_DIR) -c $< -o $@

build/run_tests: $(GAME_OBJS) $(TEST_OBJS) $(CATCH_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

build build/tests:
	mkdir -p $@

run: px
	./px

test: build/run_tests
	./build/run_tests

clean:
	rm -rf build px bombs.txt treasure.txt path_data.txt

.PHONY: run test clean
