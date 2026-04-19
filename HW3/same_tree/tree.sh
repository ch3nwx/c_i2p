#!/bin/bash
gcc -Wall -Wextra main.c c -o tree
echo "5
(4//(1/(3//(0//))/(2//)))
4(3()(0()()))(1()(2()()))
" | tree
# output
# NO
echo "5
(0/(3/(2//(1//))/)/(4//))
0(3(2()(1()()))())(4()())
" | tree
# output
# YES
