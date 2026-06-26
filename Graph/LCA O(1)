struct lca {
    int n;
    vector<int> first, dep, euler, Log;
    vector<vector<int>> st;

    lca() {}

    lca(int _n, const vector<vector<int>> &adj, int root = 1) {
        n = _n + 1;
        first.resize(n);
        dep.assign(n, 0);
        euler.reserve(2 * n); // Euler tour size is roughly 2*N
        
        dfs(root, root, adj);
        
        int m = euler.size();
        Log.assign(m + 1, 0);
        for (int i = 2; i <= m; i++) {
            Log[i] = Log[i / 2] + 1;
        }
        
        st.assign(Log[m] + 1, vector<int>(m));
        for (int i = 0; i < m; i++) {
            st[0][i] = euler[i];
        }
        for (int i = 1; i <= Log[m]; i++) {
            for (int j = 0; j + (1 << i) <= m; j++) {
                int u = st[i - 1][j];
                int v = st[i - 1][j + (1 << (i - 1))];
                st[i][j] = (dep[u] < dep[v]) ? u : v;
            }
        }
    }

    void dfs(int u, int p, const vector<vector<int>> &adj) {
        first[u] = euler.size();
        euler.push_back(u);
        for (int v : adj[u]) {
            if (v == p) continue;
            dep[v] = dep[u] + 1;
            dfs(v, u, adj);
            euler.push_back(u); // Add back to tour after returning from child
        }
    }

    int calc_lca(int u, int v) {
        int L = first[u], R = first[v];
        if (L > R) swap(L, R);
        int i = Log[R - L + 1];
        int x = st[i][L];
        int y = st[i][R - (1 << i) + 1];
        return (dep[x] < dep[y]) ? x : y;
    }

    int dis(int u, int v) {
        int lc = calc_lca(u, v);
        // Distance is sum of depths minus 2 * depth of LCA
        return dep[u] + dep[v] - 2 * dep[lc]; 
    }
};
