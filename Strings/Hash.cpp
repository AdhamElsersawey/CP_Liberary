random_device rd;
mt19937 mt(rd());
 
auto rnd(int l, int r) {
    return uniform_int_distribution(l, r)(mt);
}
 
struct cash {
    int base, inv, mod, n;
    vector<int> pow{1}, invpow{1}, pref{0}, suf{0};
 
    cash() {
    }
 
    // m->mod,b->base
    cash(const string &s,int m = 1e9 + 7,int b = 30) {
        mod = m;
        base = rnd(b, mod - 1);
        n = s.length();
        inv = 1;
        ll cur = base;
        int e = mod - 2;
        while (e) {
            if (e & 1)inv = (inv * cur) % mod;
            cur = (cur * cur) % mod;
            e >>= 1;
        }
        // calc hash for each prefix
        for (int i = 1; i <= n; i++) {
            pow.push_back(pow.back() * base % mod);
            invpow.push_back(invpow.back() * inv % mod);
            pref.push_back((pref.back() + s[i - 1] * pow[i]) % mod);
            suf.push_back((suf.back() + s[n - i] * pow[i]) % mod);
        }
    }
 
    // 1-based
    ll get(int l,int r) {
        if (l < 0 || l > r)return 0;
        return (pref[r] - pref[l - 1] + mod) * invpow[l - 1] % mod;
    }
 
    // 1-based to get the suffix to the check the palindrome
    ll get2(int l,int r) {
        if (l < 0 || l > r)return 0;
        return (suf[n - l + 1] - suf[n - r] + mod) * invpow[n - r] % mod;
    }
};
struct DoubleHash {
    cash h1, h2;

    DoubleHash(const string &s) {
        h1 = cash(s, 1e9 + 7, 131);
        h2 = cash(s, 1e9 + 9, 137);
    }

    pair<ll, ll> get(int l, int r) {
        return {h1.get(l, r), h2.get(l, r)};
    } pair<ll, ll> get2(int l, int r) {
        return {h1.get2(l, r), h2.get2(l, r)};
    }
};

