CC= g++
CCFLAGS= -Wall

SRCS= $(wildcard src/*.cpp)

PROGS= $(patsubst src/%.cpp,build/%,$(SRCS))

all:
	mkdir -p build
	make progs
	
progs: $(PROGS)

build/%: src/%.cpp
	$(CC) $(CFLAGS) -o $@ $<
clean: 
	rm -f build/*
	rm -d build
