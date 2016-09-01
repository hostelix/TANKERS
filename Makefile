CC=g++
CFLAGS=-L/usr/lib -lSDL -lpthread
all:
	$(CC) main.cpp -o bin/main -I/usr/local/include $(CFLAGS) -lSDL_mixer
