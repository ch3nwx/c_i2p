#ifndef HW4_QUESTION_H
#define HW4_QUESTION_H

#include <iostream>


// ============================ 10998 (stack) ============================
class ListNode {
    friend class List_stack;
    public:
        ListNode(const int &info)
            : data(info), nextPtr(NULL), prevPtr(NULL) {}
    private:
        int data;
        ListNode *nextPtr;
        ListNode *prevPtr;
};

class List_stack {
    public:
        List_stack();
        ~List_stack();
        void push(const int &);
        void pop();
        void print();
    private:
        ListNode *head;
        ListNode *tail;
};


// ============================ 14605 (matrix) ============================
class Matrix {
public:
    Matrix();
    Matrix(long long N) {
        this->n = N;
        this->data = new long long *[N];
        for (long long i = 0; i < N; i++) {
            this->data[i] = new long long[N];
            for (long long j = 0; j < N; j++) {
                this->data[i][j] = (i == j) ? 1 : 0;
            }
        }
    }
    Matrix(long long N, long long **Data) {
        this->n = N;
        this->data = new long long *[N];
        for (long long i = 0; i < N; i++) {
            this->data[i] = new long long[N];
            for (long long j = 0; j < N; j++) {
                this->data[i][j] = Data[i][j];
            }
        }
    }
    ~Matrix() {
        for (long long i = 0; i < this->n; i++) delete[] this->data[i];
        delete[] this->data;
    }
    void print() {
        for (long long i = 0; i < this->n; i++) {
            for (long long j = 0; j < this->n; j++) {
                std::cout << this->data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
    void add(const Matrix &rhs);
    void subtract(const Matrix &rhs);
    void multiply(const Matrix &rhs);
    void transpose();
    void power(long long x);
private:
    long long n;
    long long **data;
};


// ============================ 14927 (vending) ============================
class VendingMachine {
private:
    int* data;
    int capacity;
    int size;
    long long totalRevenue;
    int totalSold;
public:
    VendingMachine();
    ~VendingMachine();
    void store(int price);
    void sell();
    void printResult();
};


// ============================ 14931 (kura) ============================
namespace kura {
    struct ListNode {
        int value;
        struct ListNode *next;
    };
    ListNode *solve(ListNode *head);
}


// ============================ per-problem entry points ============================
int stack_main();
int matrix_main();
int vending_main();
int kura_main();

#endif
