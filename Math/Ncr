struct Comp {
    vector<Z> fact;

    Comp(int n) {
        fact.assign(n + 5, 1);
        for (int i = 1; i <= n; ++i)
            fact[i] = fact[i - 1] * i;
    }

    Z nCr(int n, int r) { return n < r ? 0 : fact[n] / fact[n - r] / fact[r]; }

    Z nPr(int n, int r) { return n < r ? 0 : fact[n] / fact[n - r]; }

    Z catalan(int n) {
        return fact[2 * n] / fact[n] / fact[n + 1];
    }
};
