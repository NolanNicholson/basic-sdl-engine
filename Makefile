CC = g++
OBJS = $(wildcard src/*.cc)
LINKER_FLAGS = -lSDL2 -lSDL2_image

all: $(OBJS)
	$(CC) $(OBJS) $(LINKER_FLAGS)
