CXX ?= g++
INCLUDE_DIRS ?= ../
#CXX_FLAGS ?= -static --std=c++11 -static-libstdc++ -static-libgcc -L $(shell g++ -print-file-name=libstdc++.a)
CXX_FLAGS ?= --std=c++11 
CXX_STATIC_FLAGS += -static

# another ugly makefile...
all: build/main_cmd build/main_cmd_nsquare build/points_gen

static: static_build/main_cmd static_build/main_cmd_nsquare static_build/points_gen

build/%: %.cpp ../algo/algo.cpp
	@mkdir -p build
	$(CXX) $(CXX_FLAGS) $(foreach includedir,$(INCLUDE_DIRS),-I$(includedir)) -o $@ $^

static_build/%: %.cpp ../algo/algo.cpp
	@mkdir -p static_build
	$(CXX) $(CXX_STATIC_FLAGS) $(CXX_FLAGS) $(foreach includedir,$(INCLUDE_DIRS),-I$(includedir)) -o $@ $^

# build/points_gen: points_gen.cpp ../algo/algo.cpp
#	@mkdir -p build
#	$(CXX) $(CXX_FLAGS) $(foreach includedir,$(INCLUDE_DIRS),-I$(includedir)) -o $@ $^

clean:
	@rm -rf build
