#include "question.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <assert.h>
using namespace std;


// ============================ 13182 (casino) ============================
int casino_main() {
    Casino casino = {};
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string op;
        int q, fee;
        cin >> op >> q >> fee;
        casino.Enterance(fee);
        for (int j = 0; j < q; ++j) {
            cin >> op;
            if (op == "Guest") {
                string name;
                int money, skill;
                cin >> name >> money >> skill;
                casino.GuestEnter(name, money, skill);
            } else if (op == "Win") {
                string name;
                int money;
                cin >> name >> money;
                casino.Win(name, money);
            }
        }
        casino.EndDay();
    }
    casino.Result();
    return 0;
}


// ============================ 13472 (kuoyang) ============================
int kuoyang_main() {
    int n, k, q;
    cin >> n >> k >> q;
    assert(k <= 4000);
    kuoyang::KuoYangPresent present(k);
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        assert(x <= 10000);
        present.Push(x);
    }
    while (q--) {
        string op;
        cin >> op;
        if (op == "push") {
            int x;
            cin >> x;
            assert(x <= 10000);
            present.Push(x);
        } else if (op == "pop") {
            present.Pop();
        } else if (op == "reverse") {
            present.Reverse();
        } else {
            cin >> op; // consume "tanoshi"
            present.ProgrammingTanoshi();
        }
    }
    present.KuoYangTeTe();
    present.PrintList();
    return 0;
}


// ============================ 14932 (corridor) ============================
int corridor_main() {
    int n;
    scanf("%d", &n);

    int *nxt = (int *)malloc((n + 1) * sizeof(int));
    for (int i = 1; i <= n; i++) scanf("%d", &nxt[i]);

    corridor::Node *nodes = (corridor::Node *)malloc((n + 1) * sizeof(corridor::Node));
    for (int i = 1; i <= n; i++)
        nodes[i].next = (nxt[i] == 0) ? NULL : &nodes[nxt[i]];

    printf("%d\n", (int)(corridor::detectCycle(&nodes[1]) - nodes));

    free(nxt);
    free(nodes);
    return 0;
}


// ============================ 14934 (station) ============================
int station_main() {
    int M, Q;
    if (scanf("%d %d", &M, &Q) != 2) return 0;

    char cmd[15];
    while (Q--) {
        scanf("%s", cmd);
        if (cmd[0] == 'E') {
            int p, c;
            scanf("%d %d", &p, &c);
            station::enter(p, c);
        } else if (cmd[0] == 'M') {
            int p_src, p_dest;
            scanf("%d %d", &p_src, &p_dest);
            station::merge(p_src, p_dest);
        } else if (cmd[0] == 'S') {
            int p_src, c, p_dest;
            scanf("%d %d %d", &p_src, &c, &p_dest);
            station::split(p_src, c, p_dest);
        } else if (cmd[0] == 'R') {
            int p;
            scanf("%d", &p);
            station::reverse(p);
        } else if (cmd[0] == 'C') {
            int p, c, k;
            scanf("%d %d %d", &p, &c, &k);
            printf("%d\n", station::check(p, c, k));
        }
    }

    for (int i = 1; i <= M; i++) {
        if (station::heads[i] != NULL) {
            printf("%d:", i);
            station::Node *curr = station::heads[i];
            while (curr != NULL) {
                printf(" %d", curr->id);
                curr = curr->next;
            }
            printf("\n");
        }
    }
    return 0;
}


// ============================ dispatcher ============================
int main(int argc, char **argv) {
    if (argc < 2) {
        cerr << "usage: " << argv[0] << " <casino|kuoyang|corridor|station>\n";
        return 1;
    }
    string p = argv[1];
    if (p == "casino")   return casino_main();
    if (p == "kuoyang")  return kuoyang_main();
    if (p == "corridor") return corridor_main();
    if (p == "station")  return station_main();
    cerr << "unknown problem: " << p << "\n";
    return 1;
}
