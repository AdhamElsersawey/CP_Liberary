struct Basis {
    vector<ll> value;
    int B;
    //sz cnt leaders,n cnt elements
    ll sz = 0, n = 0;

    Basis(int b) {
        B = b;
        value.resize(b);
    }

    void insert(int x,int who = 0) {
        n++;
        for (int i = B - 1; ~i; --i) {
            if (!(x >> i & 1))continue;
            if (!value[i]) {
                sz++;
                value[i] = x;
                return;
            }
            x ^= value[i];
        }
    }

    //if x can get by the exists atoms
    bool exist(int x) {
        for (int i = B - 1; ~i; --i) {
            if (!(x >> i & 1) || !value[i])continue;
            x ^= value[i];
        }
        return !x;
    }

    ll pw(ll a, ll k) {
        ll pw = 1;
        while (k) {
            if (k & 1) pw = pw * a % mod;
            a = a * a % mod;
            k >>= 1;
        }
        return pw;
    }

    // how many subsequence with xor =x;
    ll count(int x) {
        if (exist(x))return pw(2, n - sz);
        return 0;
    }

    // how many distinct xor you can get by your atoms
    ll distinct() {
        return 1ll << sz;
    }

    //return the k-th subsequence xor,1-ind
    ll kth(int k) {
        if (k < 1 || k > (1ll << sz))return -1;
        int x = 0, hl = 1ll << sz;
        for (int i = B - 1; ~i; --i) {
            if (!value[i]) continue;
            hl >>= 1;
            if (k > hl) {
                k -= hl;
                if (!(x >> i & 1))x ^= value[i];
            } else if (x >> i & 1) x ^= value[i];
        }
        return x;
    }

    // return the order of the xor x
    ll getorder(int x) {
        int ret = 0;
        for (int i = B - 1; ~i; --i) {
            if (!value[i]) continue;
            ret = ret * 2 + (x >> i & 1);
        }
        return ret + 1;
    }

    // ans all with x
    void updateAnd(int x) {
        vector<ll> ne;
        for (int i = 0; i < B; i++) {
            if (!value[i]) continue;
            ne.push_back(x & value[i]);
            value[i] = 0;
            --sz, --n;
        }
        for (auto i: ne)insert(i);
    }

    // xor all with x
    void updateXor(int x) {
        vector<ll> ne;
        for (int i = 0; i < B; i++) {
            if (!value[i]) continue;
            ne.push_back(value[i] & 1 ? value[i] ^ x : value[i]);
            value[i] = 0;
            --sz, --n;
        }
        for (auto i: ne)insert(i);
    }

    // max xor subsequence
    int get() {
        int ret = 0;
        for (int i = B - 1; ~i; --i) {
            if (value[i] && !(ret >> i & 1))
                ret ^= value[i];
        }
        return ret;
    }
};
