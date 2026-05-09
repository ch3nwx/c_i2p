#ifndef MIDTERM2_QUESTION_H
#define MIDTERM2_QUESTION_H

#include <iostream>
#include <string>


// ============================ 13182 (casino) ============================
class Guest {
public:
    Guest();
    Guest(std::string s, int m, int ski);
    ~Guest();
    std::string get_name();
    int get_money();
    int get_skill();
    void Win(int m);
private:
    std::string name;
    int money;
    int skill;
};

class Casino {
public:
    Casino();
    ~Casino();
    void Enterance(int f);
    void GuestEnter(std::string s, int m, int ski);
    void Win(std::string s, int m);
    void EndDay();
    void Result();
private:
    int fee;

    int guest_num;
    Guest *guest[1009];

    int income;
    int list_num;
    std::string blacklist[1009];
};


// ============================ 13472 (kuoyang) ============================
namespace kuoyang {
    struct Node {
        Node *prev;
        Node *next;
        int val;
        int tag;
    };

    class KuoYangPresent {
    public:
        KuoYangPresent(int k);
        void Push(int x);
        void Pop();
        void Reverse();
        void ProgrammingTanoshi();
        void KuoYangTeTe();
        void PrintList();
    private:
        Node *head, *mid, *tail;
        int sz, k;
        int now;
        bool reverse;
    };
}


// ============================ 14932 (corridor) ============================
namespace corridor {
    struct Node {
        struct Node *next;
    };
    Node *detectCycle(Node *head);
}


// ============================ 14934 (station) ============================
namespace station {
    struct Node {
        int id;
        struct Node *prev;
        struct Node *next;
    };
    extern Node *heads[100005];
    extern Node *tails[100005];
    void enter(int p, int c);
    void merge(int p_src, int p_dest);
    void split(int p_src, int c, int p_dest);
    void reverse(int p);
    int check(int p, int c, int k);
}


// ============================ per-problem entry points ============================
int casino_main();
int kuoyang_main();
int corridor_main();
int station_main();

#endif
