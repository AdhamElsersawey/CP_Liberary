const ll g = 3;
//g=generator
ll pw(ll a, ll k) {
    ll pw = 1;
    while (k) {
        if (k & 1) pw = pw * a % mod;
        a = a * a % mod;
        k >>= 1;
    }
    return pw;
}

int generator() // the generator
{
    vector<int> fact;
    int phi = mod - 1, n = phi;
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0) {
            fact.push_back(i);
            while (n % i == 0)
                n /= i;
        }
    if (n > 1)
        fact.push_back(n);

    for (int res = 2; res <= mod; ++res) {
        bool ok = true;
        for (size_t i = 0; i < fact.size() && ok; ++i)
            ok &= pw(res, phi / fact[i]) != 1;
        if (ok) return res;
    }
    return -1;
}

void ntt(vector<ll> &a, bool inv) {
    int n = a.size();
    // bit reversal sort
    // 101-->011  بنزود من ورا
    for (int i = 0, j = 0; i < n; ++i) {
        if (i < j)swap(a[i], a[j]);
        ll bit = n >> 1;

        //++j
        for (; j & bit; bit >>= 1)j ^= bit;
        j ^= bit;
    }

    for (int len = 2; len <= n; len <<= 1) {
        ll step = pw(g, mod / len);
        ll w1 = (inv ? pw(step, mod - 2) : step);


        for (int i = 0; i < n; i += len) {
            ll w = 1;

            for (ll j = 0; j < len / 2; ++j) {
                auto temp = a[i + j];
                /*even*/
                a[i + j] = (a[i + j] + w * a[i + j + len / 2]) % mod;
                /*odd*/
                a[i + j + len / 2] = (temp - w * a[i + j + len / 2] + mod) % mod;
                if (a[i + j] >= mod)a[i + j] -= mod;
                if (a[i + j + len / 2] < 0)a[i + j + len / 2] += mod;

                w = (w * w1) % mod;
            }
        }
    }
    ll mul = pw(n, mod - 2);
    if (inv)
        for (auto &i: a)i = (i * mul) % mod;
}

auto mul(vector<ll> &a, vector<ll> &b) {
    vector<ll> fa(all(a)), fb(all(b));
    ll sz = 1;
    while (a.size() + b.size() > sz)sz <<= 1;

    fa.resize(sz), fb.resize(sz);

    ntt(fa, 0), ntt(fb, 0);

    for (int i = 0; i < sz; i++) {
        fa[i] = fa[i] * fb[i] % mod;
    }

    ntt(fa, 1);

    return fa;
}
