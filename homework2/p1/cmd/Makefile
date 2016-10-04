CXX ?= g++
INCLUDE_DIRS ?= ../
CXX_FLAGS ?= --std=c++11

# another ugly makefile...
all: build/main_cmd build/main_cmd_nsquare build/points_gen

build/%: %.cpp ../algo/algo.cpp
	@mkdir -p build
	$(CXX) $(CXX_FLAGS) $(foreach includedir,$(INCLUDE_DIRS),-I$(includedir)) -o $@ $^

# build/points_gen: points_gen.cpp ../algo/algo.cpp
#	@mkdir -p build
#	$(CXX) $(CXX_FLAGS) $(foreach includedir,$(INCLUDE_DIRS),-I$(includedir)) -o $@ $^

clean:
	@rm -rf build
