
# Name: Emanuel Hernandez
# Assignment: Lab 11 Multiprocessing
# Section: 111

CC = gcc
CFLAGS = -Wall -Wextra

all: mandel mandelmovie

# Compile the original Mandelbrot program
mandel: mandel.c jpegrw.c jpegrw.h
	$(CC) $(CFLAGS) -o mandel mandel.c jpegrw.c -ljpeg -lm

# Compile the multiprocessing program
mandelmovie: mandelmovie.c
	$(CC) $(CFLAGS) -o mandelmovie mandelmovie.c -lm

# Remove compiled programs and object files
clean:
	rm -f mandel mandelmovie *.o

.PHONY: all clean
