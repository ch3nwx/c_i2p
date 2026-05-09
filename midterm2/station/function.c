#include "14934.h"
#include <stdlib.h>

/* Hash table: car ID -> Node*. SPLIT and CHECK both need to locate a car
 * by its ID in O(1), so a linear scan of the platform's list would blow the
 * time limit on the larger subtasks. Open addressing with linear probing,
 * size = a prime well above the worst-case car count.
 */
#define HASH_SIZE 2000003

typedef struct HashEntry {
    int key;
    Node *val;
    int used;
} HashEntry;

static HashEntry hash_table[HASH_SIZE];

static int hash_lookup(int key) {
    /* Knuth multiplicative hash, then linear probe for the slot. */
    unsigned int h = ((unsigned int)key * 2654435769u) % HASH_SIZE;
    while (hash_table[h].used && hash_table[h].key != key)
        h = (h + 1) % HASH_SIZE;
    return h;
}

static void hash_set(int key, Node *val) {
    int h = hash_lookup(key);
    hash_table[h].key = key;
    hash_table[h].val = val;
    hash_table[h].used = 1;
}

static Node *hash_get(int key) {
    int h = hash_lookup(key);
    return hash_table[h].used ? hash_table[h].val : NULL;
}

/* ENTER p c: append a fresh car c to the tail of platform p. */
void enter(int p, int c) {
    Node *n = (Node *)malloc(sizeof(Node));
    n->id = c;
    n->prev = tails[p];
    n->next = NULL;
    if (tails[p]) tails[p]->next = n;
    else heads[p] = n;
    tails[p] = n;
    hash_set(c, n);
}

/* MERGE p_src p_dest: splice the entire src list onto the tail of dest. */
void merge(int p_src, int p_dest) {
    if (!heads[p_src]) return; // empty src is a no-op
    if (!heads[p_dest]) {
        heads[p_dest] = heads[p_src];
        tails[p_dest] = tails[p_src];
    } else {
        tails[p_dest]->next = heads[p_src];
        heads[p_src]->prev = tails[p_dest];
        tails[p_dest] = tails[p_src];
    }
    heads[p_src] = NULL;
    tails[p_src] = NULL;
    /* Note: nodes keep their existing pointers in the hash table -- only the
     * platform that "owns" them changed, but lookups are by ID, not platform. */
}

/* SPLIT p_src c p_dest: cut p_src right BEFORE car c. p_dest is empty
 * before the call. Cars from c onward become the new p_dest list; the cars
 * before c stay on p_src.
 */
void split(int p_src, int c, int p_dest) {
    Node *n = hash_get(c);
    Node *p = n->prev;

    if (p) p->next = NULL;
    n->prev = NULL;

    heads[p_dest] = n;
    tails[p_dest] = tails[p_src];

    if (p) {
        tails[p_src] = p;
    } else {
        // c was the head: p_src becomes empty
        heads[p_src] = NULL;
        tails[p_src] = NULL;
    }
}

/* REVERSE p: flip every (prev,next) pair, then swap head/tail.
 * Cost is O(len(p)), but the problem caps total reversed length so the
 * amortised work across all REVERSE calls stays bounded.
 */
void reverse(int p) {
    Node *c = heads[p];
    while (c) {
        Node *t = c->next;
        c->next = c->prev;
        c->prev = t;
        c = t;
    }
    Node *t = heads[p];
    heads[p] = tails[p];
    tails[p] = t;
}

/* CHECK p c k: walk k steps toward the FRONT (prev pointers) starting from
 * car c. Stop early if we hit the head before completing k steps.
 */
int check(int p, int c, int k) {
    (void)p; // platform is implied by the car's location, not used directly
    Node *n = hash_get(c);
    while (k > 0 && n->prev) {
        n = n->prev;
        k--;
    }
    return n->id;
}
