CXX_FLAGS = -O2 -static

all: main

main: main.cpp gen_randint.cpp sorts.cpp
	g++ $(CXX_FLAGS) -o $@ $^

test: test.sh main
	bash test.sh

.PHONY: test
