struct central {
    vector<ll> sz, removed, ans,par;
    ll n, sol;
    vector<vector<ll> > adj;

    central(ll m, vector<vector<ll> > &adj1) {
        sz.resize(m + 2);
        par.resize(m + 2);
        ans.resize(m + 2); // may change the sz depend on the problem
        removed.resize(m + 2);
        n = m + 2;
        sol = 0;
        adj = adj1;
    }

    ll dfsz(ll u,ll p) {
        sz[u] = 1;
        for (ll v: adj[u]) {
            if (v == p || removed[v])continue;
            sz[u] += dfsz(v, u);
        }
        return sz[u];
    }

    ll getC(ll u,ll p,ll cursz) {
        for (ll v: adj[u]) {
            if (removed[v] || v == p)continue;
            if (sz[v] * 2 > cursz)return getC(v, u, cursz);
            // if this child is the big then the centroid exist in it
        }
        return u;
        // he the centroid
    }

    // like sack
    void add(ll u,ll p,ll d,ll del) {
        for (auto v: adj[u]) {
            if (v == p || removed[v])continue;
            add(v, u, d, del);
        }
    }

    void getans(ll u,ll p, ll dep) {
        for (auto v: adj[u]) {
            if (v == p || removed[v])continue;
            getans(v, u, dep);
        }
    }

    void build(ll u = 1,ll p=0) {
        ll cursz = dfsz(u, u);
        u = getC(u, u, cursz); // u is the cent
        removed[u] = 1;
        //1-get ans from this centroid
        //ans[0] = 1; // depend on  how you will calc the ans from the child to the cent
        for (auto v: adj[u]) {
            if (removed[v])continue;
            // getans(v, u, 1);
            // add(v, u, 1, 1);
        }
        // 2-remove the childs
        // ans[0] = 0;
        for (auto v: adj[u]) {
            if (removed[v])continue;
            //add(v, u, 1, -1);
        }

        //3-calc for the another ones
        for (ll v: adj[u])if (!removed[v])build(v,u);
    }
};
