#include "14932.h"
#include <stdlib.h>

/* Floyd's tortoise-and-hare cycle detection.
 *
 * Phase 1: advance slow by 1, fast by 2 until they meet (cycle) or fast
 *          falls off the end (no cycle).
 * Phase 2 (cycle case): math says if you reset one pointer to head and
 *          step both at speed 1, they meet at the cycle entry node.
 *
 * Memory is O(1) -- only the two pointers, no auxiliary storage proportional
 * to N. The hint in the problem warns that any solution allocating per-node
 * bookkeeping (e.g. visited[]) will exceed the memory limit on big tests.
 */
Node *detectCycle(Node *head) {
    if (!head) return NULL;

    Node *slow = head, *fast = head;
    int found = 0;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) { found = 1; break; }
    }

    if (!found) {
        /* No cycle: walk to the very last node (the one just before the exit). */
        Node *c = head;
        while (c->next) c = c->next;
        return c;
    }

    /* Cycle exists: rendezvous algorithm to find its starting node. */
    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}
