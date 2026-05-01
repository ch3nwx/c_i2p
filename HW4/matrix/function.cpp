#include "14605.h"
#include <iostream>
using namespace std;

void Matrix::add(const Matrix &rhs) {
    for (long long i = 0; i < n; i++)
        for (long long j = 0; j < n; j++)
            data[i][j] += rhs.data[i][j];
}

void Matrix::subtract(const Matrix &rhs) {
    for (long long i = 0; i < n; i++)
        for (long long j = 0; j < n; j++)
            data[i][j] -= rhs.data[i][j];
}

void Matrix::multiply(const Matrix &rhs) {
    long long **r = new long long *[n];
    for (long long i = 0; i < n; i++) {
        r[i] = new long long[n]();
        for (long long k = 0; k < n; k++) {
            long long a = data[i][k];
            if (!a) continue;
            for (long long j = 0; j < n; j++)
                r[i][j] += a * rhs.data[k][j];
        }
    }
    for (long long i = 0; i < n; i++) delete[] data[i];
    delete[] data;
    data = r;
}

void Matrix::transpose() {
    for (long long i = 0; i < n; i++)
        for (long long j = i + 1; j < n; j++) {
            long long t = data[i][j];
            data[i][j] = data[j][i];
            data[j][i] = t;
        }
}

void Matrix::power(long long x) {
    Matrix base(n, data);
    for (long long i = 0; i < n; i++)
        for (long long j = 0; j < n; j++)
            data[i][j] = (i == j) ? 1 : 0;
    while (x > 0) {
        if (x & 1) this->multiply(base);
        x >>= 1;
        if (x) base.multiply(base);
    }
}
