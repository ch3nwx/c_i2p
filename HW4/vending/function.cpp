#include "14927.h"
#include <iostream>

VendingMachine::VendingMachine() {
    capacity = 16;
    data = new int[capacity];
    size = 0;
    totalRevenue = 0;
    totalSold = 0;
}

VendingMachine::~VendingMachine() {
    delete[] data;
}

void VendingMachine::store(int price) {
    if (size == capacity) {
        int nc = capacity * 2;
        int *nd = new int[nc];
        for (int i = 0; i < size; i++) nd[i] = data[i];
        delete[] data;
        data = nd;
        capacity = nc;
    }
    int i = size++;
    data[i] = price;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (data[p] > data[i]) {
            int t = data[p]; data[p] = data[i]; data[i] = t;
            i = p;
        } else break;
    }
}

void VendingMachine::sell() {
    if (size == 0) return;
    totalSold++;
    totalRevenue += data[0];
    size--;
    if (size == 0) return;
    data[0] = data[size];
    int i = 0;
    while (true) {
        int l = 2 * i + 1, r = 2 * i + 2, s = i;
        if (l < size && data[l] < data[s]) s = l;
        if (r < size && data[r] < data[s]) s = r;
        if (s == i) break;
        int t = data[s]; data[s] = data[i]; data[i] = t;
        i = s;
    }
}

void VendingMachine::printResult() {
    std::cout << totalSold << " " << totalRevenue << "\n";
}
