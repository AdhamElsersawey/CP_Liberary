struct Seg {
    int mx, coun = 0;
    ll pref, suf, sum;

    Seg() {
        mx = -OO;
        pref = suf = 0;
        sum = 0;
        coun = 0;
    }

    Seg(int v) {
        mx = pref = sum = suf = v;
        coun = v;
    }

    void change(int v) {
        mx = pref = sum = suf = v;
        coun = v;
    }
};

struct SegT {
    int sz = 1;
    vector<Seg> tree;
    //0 index , r not include
    SegT(int n) {
        while (sz < n) sz <<= 1;
        tree.assign(sz * 2, Seg());
    }

    //change
    Seg merge(Seg &l, Seg &r) {
        Seg res = Seg();
        res.coun = max(l.coun, r.coun);
        return res;
    }

    void build(vector<int> &v,int i,int lx,int rx) {
        if (lx + 1 == rx) {
            if (lx < v.size())tree[i].change(v[lx]);
            return;
        }
        int md = (lx + rx) / 2;
        build(v, 2 * i + 1, lx, md);
        build(v, 2 * i + 2, md, rx);
        tree[i] = merge(tree[i * 2 + 1], tree[i * 2 + 2]);
    }

    void build(vector<int> &v) {
        build(v, 0, 0, sz);
    }

    void set(int in,int mx,int i,int lx,int rx) {
        if (lx + 1 == rx) {
            tree[i].coun = mx;
            return;
        }
        int md = (lx + rx) / 2;
        if (md > in) {
            set(in, mx, 2 * i + 1, lx, md);
        } else {
            set(in, mx, 2 * i + 2, md, rx);
        }
        tree[i] = merge(tree[2 * i + 1], tree[2 * i + 2]);
    }

    void set(int in, int mx) {
        set(in, mx, 0, 0, sz);
    }

    Seg query(int l, int r,int i,int lx,int rx) {
        if (lx >= l && r >= rx) return tree[i];
        if (l >= rx || r <= lx) return Seg(0);
        int md = (lx + rx) / 2;
        auto lf = query(l, r, 2 * i + 1, lx, md);
        auto rf = query(l, r, 2 * i + 2, md, rx);
        return merge(lf, rf);
    }

    Seg query(int l, int r) {
        return query(l, r, 0, 0, sz);
    }

    int k_th(int k,int i,int lx,int rx) {
        if (lx + 1 == rx) return lx;
        int md = (lx + rx) / 2;
        if (tree[2 * i + 1].coun > k) {
            return k_th(k, 2 * i + 1, lx, md);
        } else {
            return k_th(k - tree[2 * i + 1].coun, 2 * i + 2, md, rx);
        }
    }

    int k_th(int k) {
        return k_th(k, 0, 0, sz);
    }

    // get first index s.t. v[i]>=x;
    int get_fir(int x,int i,int lx,int rx) {
        if (lx + 1 == rx) return lx;
        int md = (lx + rx) / 2;
        if (tree[2 * i + 1].coun >= x) {
            return get_fir(x, 2 * i + 1, lx, md);
        } else {
            return get_fir(x, 2 * i + 2, md, rx);
        }
    }

    int get_fir(int x) {
        if (tree[0].coun < x)return -1;
        return get_fir(x, 0, 0, sz);
    }

    // get first index s.t. v[i]>=x&&i>=j;
    int get(int x,int l,int i,int lx,int rx) {
        if (tree[i].coun < x || l >= rx) return -1;
        if (lx + 1 == rx)return lx;
        int md = (lx + rx) / 2;
        int ans = get(x, l, 2 * i + 1, lx, md);
        if (~ans) return ans;
        return get(x, l, 2 * i + 2, md, rx);
    }

    int get(int x,int l) {
        return get(x, l, 0, 0, sz);
    }
};
