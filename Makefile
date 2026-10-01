CXXFLAGS ?= -std=c++17 -Wall -Wextra -O2

px: px.cpp
	$(CXX) $(CXXFLAGS) px.cpp -o px

run: px
	./px

clean:
	rm -f px bombs.txt treasure.txt path_data.txt

.PHONY: run clean
