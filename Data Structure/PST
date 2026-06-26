struct seg {
    seg *l{}, *r{};
    ll val{};

    seg() {
    }

    seg(ll x): val(x) {
    }

    // merge
    seg(seg *le, seg *re) {
        l = le, r = re;
        // change
        if (l)val = max(val, l->val);
        if (r)val = max(val, r->val);
    }
};

struct PST {
    int sz, timer = 0;
    // 0 base r include
    vector<seg *> trees;

    PST(ll n,ll m): sz(n), trees(m) {
    }

    seg *build(ll l,ll r, vector<ll> &v) {
        if (l == r)return new seg(v[l]);
        ll md = (l + r) >> 1;
        auto lef = build(l, md, v);
        auto reh = build(md + 1, r, v);
        return new seg(lef, reh);
    }

    void build(vector<ll> &v) {
        trees[0] = (build(0, sz - 1, v));
    }

    seg *build(ll l,ll r) {
        if (l == r)return new seg(0);
        ll md = (l + r) >> 1;
        auto lef = build(l, md);
        auto reh = build(md + 1, r);
        return new seg(lef, reh);
    }

    void build() {
        trees[0] = (build(0, sz - 1));
    }

    seg *set(seg *sg,ll l,ll r,ll i,ll x) {
        if (l == r)return new seg(x);
        ll md = (l + r) >> 1;
        if (i <= md)
            return new seg(set(sg->l, l, md, i, x), sg->r);
        return new seg(sg->l, set(sg->r, md + 1, r, i, x));
    }

    void set(ll ti,ll p,ll i,ll x) {
        trees[ti] = set(trees[p], 0, sz - 1, i, x);
    }

    seg *query(seg *sg,ll l,ll r,ll lf, ll rh) {
        if (l > rh || r < lf || !sg)return 0;
        if (l >= lf && r <= rh)return sg;
        ll md = (l + r) >> 1;
        return new seg(query(sg->l, l, md, lf, rh), query(sg->r, md + 1, r, lf, rh));
    }

    //  who the sg that you want the answer from it
    ll query(ll who,ll l,ll r) {
        return query(trees[who], 0, sz - 1, l, r)->val;
    }

    // if tree ==>  u+v-lc-plca
    ll kth(seg *up, seg *down,ll k,ll l,ll r) {
        if (l == r)return l;
        ll md = (l + r) >> 1;
        ll lef = up->l->val - down->l->val;
        if (lef >= k)
            return kth(up->l, down->l, k, l, md);

        k -= lef;
        return kth(up->r, down->r, k, md + 1, r);
    }

    ll kth(ll u,ll v,ll k) { return kth(trees[u], trees[v], k, 0, sz - 1); }
    ll getfirst(seg *sg,ll l,ll r,ll x,ll lf,ll rh) {
        if (r < lf || rh < l)return -1;
        if (l == r)return sg->val <= x ? l : -1;
        ll md = (l + r) >> 1;
        ll ans = -1;
        if (sg->r->val <= x)ans = getfirst(sg->l, l, md, x - sg->r->val, lf, rh);
        if (~ans)return ans;
        return getfirst(sg->r, md + 1, r, x, lf, rh);
    }

    ll getfirst(ll i,ll x,ll l,ll r) {
        return getfirst(trees[i], 0, sz - 1, x, l, r);
    }
};

