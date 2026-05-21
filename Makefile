TARGET ?= main
SRCS = $(wildcard src/*.cpp) $(wildcard src/patterns/*.cpp)

all:
	g++ $(SRCS) -o game-of-life