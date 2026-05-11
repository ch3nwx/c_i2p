#include "question.h"
#include <iostream>
#include <queue>
#include <vector>
#include <stdlib.h>
using namespace std;

// ============================ 13182 (casino) ============================
Guest::Guest() : money(0), skill(0) {}
Guest::Guest(string s, int m, int ski) : name(s), money(m), skill(ski) {}
Guest::~Guest() {}

string Guest::get_name() { return name; }
int Guest::get_money() { return money; }
int Guest::get_skill() { return skill; }
void Guest::Win(int m) { money += m; }

Casino::Casino() : fee(0), guest_num(0), income(0), list_num(0) {
    for (int i = 0; i < 1009; i++) guest[i] = NULL;
}

Casino::~Casino() {
    for (int i = 0; i < guest_num; i++) delete guest[i];
}

void Casino::Enterance(int f) { fee = f; }

void Casino::GuestEnter(string s, int m, int ski) {
    for (int i = 0; i < list_num; i++)
        if (blacklist[i] == s) return;
    for (int i = 0; i < guest_num; i++)
        if (guest[i]->get_name() == s) return;
    if (m <= fee) {
        income += m;
        blacklist[list_num++] = s;
    } else {
        income += fee;
        guest[guest_num++] = new Guest(s, m - fee, ski);
    }
}

void Casino::Win(string s, int m) {
    for (int i = 0; i < list_num; i++)
        if (blacklist[i] == s) return;
    int idx = -1;
    for (int i = 0; i < guest_num; i++)
        if (guest[i]->get_name() == s) { idx = i; break; }
    if (idx == -1) return;

    Guest *g = guest[idx];

    if (m >= 0) {
        g->Win(m);
        income -= m;
        if (m > 2 * g->get_skill()) {
            blacklist[list_num++] = s;
            delete g;
            for (int i = idx; i < guest_num - 1; i++) guest[i] = guest[i + 1];
            guest_num--;
        }
    } else {
        int X = -m;
        int Y = g->get_money();
        if (Y <= X) {
            income += Y;
            blacklist[list_num++] = s;
            delete g;
            for (int i = idx; i < guest_num - 1; i++) guest[i] = guest[i + 1];
            guest_num--;
        } else {
            g->Win(m);
            income += X;
        }
    }
}

void Casino::EndDay() {
    for (int i = 0; i < guest_num; i++) delete guest[i];
    guest_num = 0;
}

void Casino::Result() {
    cout << income << "\n";
    for (int i = 0; i < list_num; i++) cout << blacklist[i] << "\n";
}


// ============================ 13472 (kuoyang) ============================
namespace kuoyang {

KuoYangPresent::KuoYangPresent(int k_) {
    k = k_;
    head = mid = tail = NULL;
    sz = 0;
    now = 0;
    reverse = false;
}

void KuoYangPresent::Push(int x) {
    Node *n = new Node;
    n->val = x;
    n->tag = now;
    n->prev = n->next = NULL;

    sz++;
    if (sz == 1) {
        head = tail = mid = n;
        return;
    }

    if (reverse) {
        n->next = head;
        head->prev = n;
        head = n;
    } else {
        n->prev = tail;
        tail->next = n;
        tail = n;
    }

    if (sz % 2 == 1) {
        mid = reverse ? mid->prev : mid->next;
    }
}

void KuoYangPresent::Pop() {
    Node *to_del = mid;
    Node *new_mid = reverse ? mid->next : mid->prev;

    Node *p = to_del->prev, *nx = to_del->next;
    if (p) p->next = nx;
    if (nx) nx->prev = p;
    if (to_del == head) head = nx;
    if (to_del == tail) tail = p;

    delete to_del;
    sz--;
    mid = (sz == 0) ? NULL : new_mid;
}

void KuoYangPresent::Reverse() {
    reverse = !reverse;
    if (sz > 0 && sz % 2 == 0) {
        mid = reverse ? mid->next : mid->prev;
    }
}

void KuoYangPresent::ProgrammingTanoshi() { now++; }
void KuoYangPresent::KuoYangTeTe() {}

void KuoYangPresent::PrintList() {
    if (reverse) {
        for (Node *c = tail; c; c = c->prev) {
            if (c->tag < now) { c->val %= k; c->tag = now; }
            cout << c->val << " ";
        }
    } else {
        for (Node *c = head; c; c = c->next) {
            if (c->tag < now) { c->val %= k; c->tag = now; }
            cout << c->val << " ";
        }
    }
    cout << "\n";
}

} // namespace kuoyang


// ============================ 14932 (corridor) ============================
namespace corridor {

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
        Node *c = head;
        while (c->next) c = c->next;
        return c;
    }

    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}

} // namespace corridor


// ============================ 14934 (station) ============================
namespace station {

Node *heads[100005] = {NULL};
Node *tails[100005] = {NULL};

#define HASH_SIZE 2000003

struct HashEntry {
    int key;
    Node *val;
    int used;
};

static HashEntry hash_table[HASH_SIZE];

static int hash_lookup(int key) {
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

void merge(int p_src, int p_dest) {
    if (!heads[p_src]) return;
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
}

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
        heads[p_src] = NULL;
        tails[p_src] = NULL;
    }
}

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

int check(int p, int c, int k) {
    (void)p;
    Node *n = hash_get(c);
    while (k > 0 && n->prev) {
        n = n->prev;
        k--;
    }
    return n->id;
}

} // namespace station


// ============================ 14224 (electrical) ============================
namespace electrical {

long long huffman(int n, long long *a) {
    if (n <= 0) return 0;
    if (n == 1) return a[0];

    priority_queue<long long, vector<long long>, greater<long long>> pq;
    for (int i = 0; i < n; i++) pq.push(a[i]);

    long long total = 0;
    while (pq.size() > 1) {
        long long x = pq.top(); pq.pop();
        long long y = pq.top(); pq.pop();
        long long s = x + y;
        total += s;
        pq.push(s);
    }
    return total;
}

} // namespace electrical


// ============================ 13858 (salesman) ============================
namespace salesman {

static long long dfs(int u, int parent, vector<vector<Edge>> &adj,
                     long long &diameter) {
    long long best1 = 0, best2 = 0;
    for (Edge &e : adj[u]) {
        if (e.to == parent) continue;
        long long d = dfs(e.to, u, adj, diameter) + e.w;
        if (d > best1)      { best2 = best1; best1 = d; }
        else if (d > best2) { best2 = d; }
    }
    if (best1 + best2 > diameter) diameter = best1 + best2;
    return best1;
}

long long openLoopTSP(int n, vector<vector<Edge>> &adj, long long total) {
    if (n <= 1) return 0;
    long long diameter = 0;
    dfs(0, -1, adj, diameter);
    return 2 * total - diameter;
}

} // namespace salesman
