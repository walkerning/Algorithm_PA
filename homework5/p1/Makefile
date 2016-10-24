CXX ?= g++
CXX_FLAGS ?= --std=c++11

all: main

main: longest_monotonic_sequence.cpp main.cpp
	$(CXX) $(CXX_FLAGS) -o $@ $^

clean:
	rm -rf *.o main
