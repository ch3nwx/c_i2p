CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2

all: solution

solution: function.c 14932.c 14932.h
	$(CC) $(CFLAGS) function.c 14932.c -o solution

run: solution
	./solution

clean:
	rm -f solution
