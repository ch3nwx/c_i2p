#!/bin/bash
gcc -Wall -Wextra central.c -o central
echo "4 3
1 2 2
2 4
3 3
4 1" | central
