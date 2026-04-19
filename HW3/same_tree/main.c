#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *left, *right;
} Node;

Node* newNode(int val) {
    Node *n = malloc(sizeof(Node));
    n->val = val;
    n->left = n->right = NULL;
    return n;
}

void freeTree(Node *n) {
    if (!n) return;
    freeTree(n->left);
    freeTree(n->right);
    free(n);
}

// Format T: TREE ::= '(' INT '/' TREE '/' TREE ')' | NIL
Node* parseT(const char *s, int *pos) {
    if (s[*pos] != '(') return NULL;
    (*pos)++;
    int val = 0;
    while (s[*pos] >= '0' && s[*pos] <= '9')
        val = val * 10 + (s[(*pos)++] - '0');
    (*pos)++;  // consume '/'
    Node *left = parseT(s, pos);
    (*pos)++;  // consume '/'
    Node *right = parseT(s, pos);
    (*pos)++;  // consume ')'
    Node *n = newNode(val);
    n->left = left;
    n->right = right;
    return n;
}

// Format S: TREE ::= INT '(' TREE ')' '(' TREE ')' | NIL
Node* parseS(const char *s, int *pos) {
    if (s[*pos] < '0' || s[*pos] > '9') return NULL;
    int val = 0;
    while (s[*pos] >= '0' && s[*pos] <= '9')
        val = val * 10 + (s[(*pos)++] - '0');
    (*pos)++;  // consume '('
    Node *left = parseS(s, pos);
    (*pos)++;  // consume ')'
    (*pos)++;  // consume '('
    Node *right = parseS(s, pos);
    (*pos)++;  // consume ')'
    Node *n = newNode(val);
    n->left = left;
    n->right = right;
    return n;
}

int same(Node *a, Node *b) {
    if (!a && !b) return 1;
    if (!a || !b) return 0;
    return a->val == b->val && same(a->left, b->left) && same(a->right, b->right);
}

int main() {
    int n;
    scanf("%d", &n);
    char *sT = malloc(200005);
    char *sS = malloc(200005);
    scanf("%s", sT);
    scanf("%s", sS);
    int posT = 0, posS = 0;
    Node *T = parseT(sT, &posT);
    Node *S = parseS(sS, &posS);
    printf("%s\n", same(T, S) ? "YES" : "NO");
    freeTree(T);
    freeTree(S);
    free(sT);
    free(sS);
    return 0;
}
