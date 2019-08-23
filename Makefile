CC = g++
OBJS = $(wildcard src/*.cc)
LINKER_FLAGS = -lSDL2

all: $(OBJS)
	$(CC) $(OBJS) $(LINKER_FLAGS)
