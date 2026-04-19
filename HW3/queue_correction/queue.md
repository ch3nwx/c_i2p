Description
The elephants are queuing in a line. However, some of them are standing in the wrong position, so you are asked to help restore the correct order.

Since the elephants are too lazy to call each other by name, they use a lucky number to recognize one another. Therefore, you will receive a linked list where each node contains a lucky number. Your task is to reverse the order of nodes within the range  (both inclusive, -based).

The I/O functions are already implemented in the given file. You only need to complete the void solve(Node* head, int l, int r) fucntion that returns the same dummy head. Your task is to reverse the linked list within the specified range .

You can ignore the warning while compiling: cast to smaller integer type 'int' from 'Node *' (aka 'struct Node *') [-Wpointer-to-int-cast]

There is a restriction: You can only modify the “next” pointer of each node to change the order. If you attempt to modify the node values or return a list containing nodes whose addresses do not belong to the original list, you may receive a wrong answer.



Input
The first line contains three integers ,  and , representing the size of the list, the start index, and the end index (both inclusive, -based).

The second line contains  integers , representing the lucky numbers of the elephants.

Contraints
Subtask
(Testcases 1-2) 
(Testcases 3-7) No additional Constraints.
Output
Output the modified list of lucky numbers, each followed by a space.
