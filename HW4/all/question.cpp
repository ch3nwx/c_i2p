#include "question.h"
#include <iostream>
#include <string>
#include <string.h>
using namespace std;


// ============================ 10998 (stack) ============================
int stack_main() {
    List_stack L_stack;
    char command[10];
    int n;
    while (cin >> command) {
        if (strcmp(command, "pop") == 0) {
            L_stack.pop();
        } else if (strcmp(command, "push") == 0) {
            cin >> n;
            L_stack.push(n);
        } else if (strcmp(command, "print") == 0) {
            L_stack.print();
            cout << endl;
        }
    }
    return 0;
}


// ============================ 14605 (matrix) ============================
int matrix_main() {
    long long n, t;
    cin >> n >> t;
    long long **tmp = new long long *[n];
    for (long long i = 0; i < n; i++) tmp[i] = new long long[n];
    for (long long i = 0; i < n; i++)
        for (long long j = 0; j < n; j++) cin >> tmp[i][j];
    Matrix res(n, tmp);
    while (t--) {
        int o;
        cin >> o;
        if (o == 1) {
            for (long long i = 0; i < n; i++)
                for (long long j = 0; j < n; j++) cin >> tmp[i][j];
            Matrix mat(n, tmp);
            res.add(mat);
        } else if (o == 2) {
            for (long long i = 0; i < n; i++)
                for (long long j = 0; j < n; j++) cin >> tmp[i][j];
            Matrix mat(n, tmp);
            res.subtract(mat);
        } else if (o == 3) {
            for (long long i = 0; i < n; i++)
                for (long long j = 0; j < n; j++) cin >> tmp[i][j];
            Matrix mat(n, tmp);
            res.multiply(mat);
        } else if (o == 4) {
            res.transpose();
        } else if (o == 5) {
            long long x;
            cin >> x;
            res.power(x);
        }
    }
    res.print();
    for (long long i = 0; i < n; i++) delete[] tmp[i];
    delete[] tmp;
    return 0;
}


// ============================ 14927 (vending) ============================
int vending_main() {
    VendingMachine vm;
    string cmd;
    while (cin >> cmd) {
        if (cmd == "store") {
            int price;
            cin >> price;
            vm.store(price);
        } else if (cmd == "sell") {
            vm.sell();
        }
    }
    vm.printResult();
    return 0;
}


// ============================ 14931 (kura) ============================
static kura::ListNode *kura_newNode(int val) {
    kura::ListNode *ret = new kura::ListNode();
    ret->value = val;
    ret->next = nullptr;
    return ret;
}

int kura_main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    kura::ListNode *head = nullptr;
    kura::ListNode *tail = nullptr;

    int value, chk = 0;
    for (int i = 0; i < N; ++i) {
        cin >> value;
        kura::ListNode *node = kura_newNode(value);
        chk ^= (reinterpret_cast<intptr_t>(node) + node->value);
        if (head == nullptr) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

    kura::ListNode *result = kura::solve(head);

    int chk2 = 0;
    kura::ListNode *curr = result;
    while (curr != nullptr) {
        chk2 ^= (reinterpret_cast<intptr_t>(curr) + curr->value);
        cout << curr->value;
        if (curr->next != nullptr) cout << " ";
        curr = curr->next;
    }
    cout << "\n";

    if (chk != chk2) cout << "Wrong Answer\n";

    curr = result;
    while (curr != nullptr) {
        kura::ListNode *tmp = curr;
        curr = curr->next;
        delete tmp;
    }
    return 0;
}


// ============================ dispatcher ============================
int main(int argc, char **argv) {
    if (argc < 2) {
        cerr << "usage: " << argv[0] << " <stack|matrix|vending|kura>\n";
        return 1;
    }
    string p = argv[1];
    if (p == "stack")   return stack_main();
    if (p == "matrix")  return matrix_main();
    if (p == "vending") return vending_main();
    if (p == "kura")    return kura_main();
    cerr << "unknown problem: " << p << "\n";
    return 1;
}
