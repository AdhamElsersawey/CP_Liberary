struct Dsu {
    vector<int> sz, parent, pt;
    int mx, comp;
    stack<array<int, 4> > stk;

    Dsu(int n) {
        parent.resize(n);
        sz.resize(n);
        pt.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            sz[i] = 1;
        }
        mx = 1;
        comp = n;
    }

    int find(int p) {
        if (p == parent[p]) return p;
        return find(parent[p]);
        // parent[p] =
        //if u will use query or rollback delete parent[p]=
    }


    bool join(int p, int q) {
        int r = find(p);
        int s = find(q);
        array<int, 4> tmp{-1, -1, -1, -1};
        stk.push(tmp);
        if (r == s)
            return 0;
        if (sz[r] > sz[s]) swap(r, s);
        stk.pop();
        tmp = {r, parent[r], s, sz[s]};
        stk.push(tmp);
        parent[r] = s;
        sz[s] += sz[r];
        pt[r] -= pt[s];
        mx = max(mx, sz[s]);
        comp--;
        return 1;
    }

    void rollback() {
        auto tmp = stk.top();
        stk.pop();
        if (tmp[0] == -1)return;
        parent[tmp[0]] = tmp[1];
        sz[tmp[2]] = tmp[3];
    }

    void add(int p,int val) {
        pt[find(p)] += val;
    }

    int size(int p) {
        return sz[parent[p]];
    }

    int query(int x) {
        if (x == parent[x]) return pt[x];
        return pt[x] + query(parent[x]);
    }
};
