
struct TwoSatSolver {
    int n_vars;
    int n_vertices;
    vector<vector<int>> adj, adj_t;
    vector<bool> used;
    vector<int> order, comp;
    vector<bool> assignment;

    TwoSatSolver(int _n_vars) : n_vars(_n_vars), n_vertices(2 * n_vars), adj(n_vertices), adj_t(n_vertices), used(n_vertices), order(), comp(n_vertices, -1), assignment(n_vars) {
        order.reserve(n_vertices);
    }
    void dfs1(int v) {
        used[v] = true;
        for (int u : adj[v]) {
            if (!used[u])
                dfs1(u);
        }
        order.push_back(v);
    }

    void dfs2(int v, int cl) {
        comp[v] = cl;
        for (int u : adj_t[v]) {
            if (comp[u] == -1)
                dfs2(u, cl);
        }
    }

    bool solve_2SAT() {
        order.clear();
        used.assign(n_vertices, false);
        for (int i = 0; i < n_vertices; ++i) {
            if (!used[i])
                dfs1(i);
        }

        comp.assign(n_vertices, -1);
        for (int i = 0, j = 0; i < n_vertices; ++i) {
            int v = order[n_vertices - i - 1];
            if (comp[v] == -1)
                dfs2(v, j++);
        }

        assignment.assign(n_vars, false);
        for (int i = 0; i < n_vertices; i += 2) {
            if (comp[i] == comp[i + 1])
                return false;
            assignment[i / 2] = comp[i] > comp[i + 1];
        }
        return true;
    }

    void add_disjunction(int a, bool na, int b, bool nb) {
        // na and nb signify whether a and b are to be negated
        a = 2 * a ^ na;
        b = 2 * b ^ nb;
        int neg_a = a ^ 1;
        int neg_b = b ^ 1;
        adj[neg_a].push_back(b);
        adj[neg_b].push_back(a);
        adj_t[b].push_back(neg_a);
        adj_t[a].push_back(neg_b);
    }

    void add_implication(int a, bool na, int b, bool nb) {
        // (a -> b) == (!a || b)
        add_disjunction(a, !na, b, nb);
    }

    void add_conjunction(int a, bool na, int b, bool nb) {
        // (a) && (b)
        // Add the two unit clauses separately:
        // (a)  == (a || a)
        // (b)  == (b || b)
        add_disjunction(a, na, a, na);
        add_disjunction(b, nb, b, nb);
    }
    /*
     * a -> b <=> !a or b
     * (i ^ j) or (!i ^ !j) <=> (j or !i) ^ (i or !j)
     * (i ^ !j) or (!i ^ j) <=> (!j or !i) ^ (i or j)
     * (at most one problem)
     * {
     *  make y(n) , z(z) literals
     *  f = ( [1,n]^(yi -> !xi) ) ^ ( [2,n]^(yi -> yi-1) ) ^ ( [2,n]^(xi -> yi-1) )
     *     ^ ( [1,n]^(zi -> !xi) ) ^ ( [1,n-1]^(zi -> zi+1) ) ^ ( [1,n-1]^(xi -> zi+1))
     * }
     * */
};