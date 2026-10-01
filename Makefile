CXXFLAGS ?= -std=c++17 -Wall -Wextra -O2
CPPFLAGS += -Iinclude

SRCS    := $(wildcard src/*.cpp)
OBJS    := $(SRCS:src/%.cpp=build/%.o)
HEADERS := $(wildcard include/*.h)

px: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

build/%.o: src/%.cpp $(HEADERS) | build
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

build:
	mkdir -p build

run: px
	./px

clean:
	rm -rf build px bombs.txt treasure.txt path_data.txt

.PHONY: run clean
