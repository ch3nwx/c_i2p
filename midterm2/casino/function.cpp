#include "13182.h"
#include <iostream>
using namespace std;

// ============================ Guest ============================
Guest::Guest() : money(0), skill(0) {}
Guest::Guest(string s, int m, int ski) : name(s), money(m), skill(ski) {}
Guest::~Guest() {}

string Guest::get_name() { return name; }
int Guest::get_money() { return money; }
int Guest::get_skill() { return skill; }
void Guest::Win(int m) { money += m; }

// ============================ Casino ============================
Casino::Casino() : fee(0), guest_num(0), income(0), list_num(0) {
    for (int i = 0; i < 1009; i++) guest[i] = NULL;
}

Casino::~Casino() {
    for (int i = 0; i < guest_num; i++) delete guest[i];
}

void Casino::Enterance(int f) { fee = f; }

void Casino::GuestEnter(string s, int m, int ski) {
    // ignore if blacklisted
    for (int i = 0; i < list_num; i++)
        if (blacklist[i] == s) return;
    // ignore if already in casino
    for (int i = 0; i < guest_num; i++)
        if (guest[i]->get_name() == s) return;
    // pay entrance fee. If Y (money) <= X (fee), pay all and go bankrupt.
    if (m <= fee) {
        income += m;
        blacklist[list_num++] = s;
    } else {
        income += fee;
        guest[guest_num++] = new Guest(s, m - fee, ski);
    }
}

void Casino::Win(string s, int m) {
    // ignore if blacklisted
    for (int i = 0; i < list_num; i++)
        if (blacklist[i] == s) return;
    // find the guest currently in the casino
    int idx = -1;
    for (int i = 0; i < guest_num; i++)
        if (guest[i]->get_name() == s) { idx = i; break; }
    if (idx == -1) return;

    Guest *g = guest[idx];

    if (m >= 0) {
        // guest wins money from casino
        g->Win(m);
        income -= m;
        if (m > 2 * g->get_skill()) {
            // cheater: blacklist and remove (casino still pays)
            blacklist[list_num++] = s;
            delete g;
            for (int i = idx; i < guest_num - 1; i++) guest[i] = guest[i + 1];
            guest_num--;
        }
    } else {
        // guest must pay |m| to casino
        int X = -m;
        int Y = g->get_money();
        if (Y <= X) {
            // pay all, bankrupt
            income += Y;
            blacklist[list_num++] = s;
            delete g;
            for (int i = idx; i < guest_num - 1; i++) guest[i] = guest[i + 1];
            guest_num--;
        } else {
            g->Win(m); // m is negative
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
