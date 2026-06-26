#define matrix vector<vector<ll>>

struct Matrix {
    int n, m;
    matrix a;

    Matrix(ll _n, ll _m) : n(_n), m(_m), a(_n, vector<int>(_m)) {
    }

    Matrix operator*(const Matrix &b) {
        int r = n, c = b.m, k = m;
        Matrix res(r, c);
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                for (int o = 0; o < k; o++) {
                    res.a[i][j] += a[i][o] * b.a[o][j] % mod;
                    res.a[i][j] %= mod;
                }
            }
        }
        return res;
    }

    friend Matrix power(Matrix &a, ll p) {
        Matrix res(a.n, a.n);
        for (int i = 0; i < a.n; i++)res.a[i][i] = 1;
        while (p) {
            if (p & 1)res = res * a;
            a = a * a;
            p >>= 1;
        }
        return res;
    }
};
