CFLAGS=-Isrc -std=c++11 -O2 -ggdb3 -Wall

all: test

test: tests/test_options.cpp
	g++ -o test_modules tests/test_options.cpp $(CFLAGS)
