struct Seg {
    int mx, coun = 0;
    ll pref, suf, sum, laz;
    bool islazy;

    Seg() {
        mx = -OO;
        pref = suf = 0;
        laz = 0;
        sum = 0;
        coun = 0;
    }

    Seg(int v) {
        mx = pref = sum = suf = v;
        coun = 0;
        laz = 0;
    }

    void update(int x,int l,int r) {
        coun += x;
        laz += x;
        islazy = 1;
    }

    void change(int v) {
        mx = pref = sum = suf = v;
        coun = v;
        islazy = 0;
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

    void prop(int i,int lx,int rx) {
        //o(1)
        if (lx + 1 == rx || !tree[i].islazy) return;
        int l = 2 * i + 1, r = 2 * i + 2;
        int md = (lx + rx) / 2;
        tree[l].update(tree[i].laz, lx, md);
        tree[r].update(tree[i].laz, md, rx);
        tree[i].islazy = 0;
        tree[i].laz = 0;
    }

    void update(int x,int l,int r,int i,int lx,int rx) {
        prop(i, lx, rx);
        if (l >= rx || r <= lx) return;
        if (lx >= l && r >= rx) {
            tree[i].update(x, lx, rx);
            return;
        }
        int md = (lx + rx) / 2;
        update(x, l, r, 2 * i + 1, lx, md);
        update(x, l, r, 2 * i + 2, md, rx);
        tree[i] = merge(tree[2 * i + 1], tree[2 * i + 2]);
    }

    void update(int x,int l,int r) {
        update(x, l, r, 0, 0, sz);
    }

    void set(int in,int mx,int i,int lx,int rx) {
        prop(i, lx, rx);
        if (lx + 1 == rx) {
            tree[i].coun = 0;
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
        prop(i, lx, rx);
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
};
