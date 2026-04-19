#!/bin/bash
gcc -Wall -Wextra function.c main.c c -o queue
echo "5 2 4
4 6 7 8 3" | queue
# putput
# 4 8 7 6 3
