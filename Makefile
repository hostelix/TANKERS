CC=g++
CFLAGS=-L/usr/lib -lSDL -lpthread -lSDL_mixer
all:
	$(CC) main.cpp -o bin/main -I/usr/local/include $(CFLAGS) 
