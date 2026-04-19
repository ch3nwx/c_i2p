#!/bin/bash
gcc -Wall -Wextra function.c main.c -o solution
echo "5 2
3 -1 2 -4 1" | ./solution
