TARGET ?= main
SRCS = $(wildcard *.cpp) $(wildcard patterns/*.cpp)

all:
	g++ $(SRCS) -o game-of-life