CXX ?= g++
INCLUDE_DIRS ?= ../
CXX_FLAGS ?= --std=c++11

all: build/main_cmd build/points_gen

build/main_cmd: main_cmd.cpp ../algo/algo.cpp
	@mkdir -p build
	@# another ugly makefile...
	$(CXX) $(CXX_FLAGS) $(foreach includedir,$(INCLUDE_DIRS),-I$(includedir)) -o $@ $^

build/points_gen: points_gen.cpp ../algo/algo.cpp
	@mkdir -p build
	$(CXX) $(CXX_FLAGS) $(foreach includedir,$(INCLUDE_DIRS),-I$(includedir)) -o $@ $^

clean:
	@rm -rf build
