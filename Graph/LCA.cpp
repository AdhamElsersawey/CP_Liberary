struct lca {
    int log = 24, n, timer;
    vector<vector<int> > up, val;
    vector<ll> in, out, dep;

    lca(int _n, vector<vector<pair<ll,ll> > > &adj,int root = 1) {
        n = _n + 1;
        timer = 0;
        up.assign(log, vector(n, root));
        val.assign(log, vector(n, 0ll));
        in.resize(n);
        dep.assign(n, 0ll);
        out.resize(n);
        dfs(root, root, adj);
        for (int j = 1; j < log; j++) {
            for (int i = 1; i < n; i++) {
                up[j][i] = up[j - 1][up[j - 1][i]];
                val[j][i] = max(val[j - 1][i], val[j - 1][up[j - 1][i]]);
            }
        }
    }

    ll k_th(int u, int k) {
        for (int i = 0; i < log; i++) {
            if (k >> i & 1) u = up[i][u];
        }
        return u;
    }

    void dfs(int u,int p, vector<vector<pair<ll,ll> > > &adj) {
        in[u] = ++timer;
        up[0][u] = p;
        for (auto [v,w]: adj[u]) {
            if (v == p) continue;
            val[0][v] = w;
            dep[v] = dep[u] + 1;
            dfs(v, u, adj);
        }
        out[u] = timer;
    }

    bool is_ancestor(int u, int v) {
        return in[u] <= in[v] && out[u] >= out[v];
    }

    ll calc_lca(int u, int v) {
        if (is_ancestor(u, v)) return u;
        if (is_ancestor(v, u)) return v;
        for (int i = log - 1; ~i; i--) {
            if (is_ancestor(up[i][u], v)) continue;
            u = up[i][u];
        }
        return up[0][u];
    }

    ll query(int u,ll v) {
        if (dep[u] < dep[v])swap(u, v);
        auto move = [&](int &w,ll i) {
            w = up[i][w];
        };
        ll ret = 0, dif = dep[u] - dep[v];
        for (int i = 0; i < log; ++i) {
            if (dif >> i & 1) {
                ret = max(ret, val[i][u]);
                move(u, i);
            }
        }
        if (u == v)return ret;

        for (int i = log - 1; ~i; --i) {
            if (up[i][u] != up[i][v]) {
                ret = max(ret, val[i][u]);
                ret = max(ret, val[i][v]);
                move(u, i);
                move(v, i);
            }
        }
        ret = max(ret, val[0][u]);
        ret = max(ret, val[0][v]);
        return ret;
    }
};
