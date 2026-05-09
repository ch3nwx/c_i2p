CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2

all: solution

solution: function.c 14934.c 14934.h
	$(CC) $(CFLAGS) function.c 14934.c -o solution

run: solution
	./solution

clean:
	rm -f solution
