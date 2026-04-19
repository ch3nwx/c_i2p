Description
You are given two rooted binary trees,  and , in a special format, each with vertices, numbered from  to . The format is described by the following EBNF (Extended Backus–Naur form):

The tree : TREE ::= '(' INT '/' TREE '/' TREE ')' | NIL
The tree : TREE ::= INT '(' TREE ')' '(' TREE ')' | NIL

It means that a tree is a integer followed by two subtrees or a NIL. The integer represents which vertex the root of the tree is. If the tree is a NIL, it means that the tree is empty.

Two binary trees are considered identical if and only if:

Both trees are empty (NIL), or
Both trees have roots, and:
Their root values are equal AND
Their left subtrees are identical AND
Their right subtrees are identical
Here is a example. In the following figure, tree (a) will be represented as (2/(1//)/(0//)) and 2(1()())(0()()),
tree (b) as (2/(0//)/(1//)) and 2(0()())(1()()), and they are NOT identical.



Input
Input contains three lines. The first line contains an integer , the number of vertices in each tree.

For the following two lines, each line contains a string, representing tree  and respectively in the EBNF format.

Contraints
Length of  and  won't exceed 
 only contain character '(', ')', '/' and digit.
 only contain character '(', ')' and digit.
 
Output
If the two trees are identical, output "YES", otherwise output "NO" (without quote)

Noted that you should output one single line.
