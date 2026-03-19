#include <cstdio>
#include <cstdlib>

unsigned random_seed = 7122;
unsigned Random() {
    return random_seed = random_seed * 0xdefaced + 1;
}

class Array3D {
    unsigned n, m, k;
    unsigned ***data;

public:
    Array3D(unsigned n, unsigned m, unsigned k) : n(n), m(m), k(k) {
        // single allocation: pointer layers + data, contiguous block
        char *block = new char[sizeof(unsigned **) * n +
                               sizeof(unsigned *) * (n * m) +
                               sizeof(unsigned) * (n * m * k)];

        data = reinterpret_cast<unsigned ***>(block);
        unsigned **ptrs = reinterpret_cast<unsigned **>(data + n);
        unsigned *vals = reinterpret_cast<unsigned *>(ptrs + n * m);

        for (unsigned i = 0; i < n; i++) {
            data[i] = ptrs + i * m;
            for (unsigned j = 0; j < m; j++) {
                data[i][j] = vals + i * m * k + j * k;
            }
        }
    }

    ~Array3D() {
        delete[] reinterpret_cast<char *>(data);
    }

    unsigned **operator[](unsigned i) { return data[i]; }
};

int main() {
    int t, n, m, k;
    scanf("%d%d%d%d%u", &t, &n, &m, &k, &random_seed);

    while (t--) {
        Array3D arr(n, m, k);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                for (int l = 0; l < k; l++)
                    arr[i][j][l] = Random();

        for (int i = 0; i < 5; i++) {
            unsigned a = Random() % n;
            unsigned b = Random() % m;
            unsigned c = Random() % k;
            if (i) putchar(' ');
            printf("%u", arr[a][b][c]);
        }
        puts("");
    }
    return 0;
}
