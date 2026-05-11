#include "14224.h"
#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    long long *a = new long long[n];
    for (int i = 0; i < n; i++) cin >> a[i];
    cout << huffman(n, a);
    delete[] a;
    return 0;
}
