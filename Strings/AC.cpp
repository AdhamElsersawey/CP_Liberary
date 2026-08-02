struct Aho {
    int cn, patt;
    const int con = 26;
    vector<vector<int> > out;
    vector<array<int, 26> > nxt;
    vector<int> link, out_link;
    vector<int> ord, havePatt;


    int node() {
        array<int, 26> ar{};
        ar.fill(0);
        nxt.emplace_back(ar);
        link.emplace_back(0);
        out_link.emplace_back(0);
        out.emplace_back();
        havePatt.emplace_back(0);
        return cn++;
    }

    Aho(): cn(0), patt(0) {
        node();
    }

    int get(char c) {
        return c - 'a';
    }

    //  Return terminal node of this pattern
    int add(const string &s, int ind) {
        int u = 0; //root
        for (auto c: s) {
            int x = get(c);
            if (!nxt[u][x])
                nxt[u][x] = node();
            //  Move to next node
            u = nxt[u][x];
        }
        //  Pattern ends at node u
        out[u].push_back(ind);
        havePatt[u] = 1;
        //  return terminal node

        return u;
    }

    //  Build failure links using BFS
    void calc() {
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            ord.push_back(u);
            for (int c = 0; c < con; c++) {
                int v = nxt[u][c];

                if (!v) {
                    nxt[u][c] = (u == 0 ? 0 : nxt[link[u]][c]);
                } else {
                    link[v] = (u ? nxt[link[u]][c] : 0);
                    havePatt[v] |= havePatt[link[v]];
                    out_link[v] = out[link[v]].empty() ? out_link[link[v]] : link[v];
                    q.push(v);
                }
            }
        }
    }

    int go(int u, char c) {
        return nxt[u][get(c)];
    }

    // return the pos for every string in s
    void search(string &s, vector<int> &len, vector<vector<int> > &ret) {
        ret.assign(len.size(), vector<int>());
        for (int i = 0, u = 0; i < s.size(); ++i) {
            u = go(u, s[i]);
            for (int t = u; t; t = out_link[t]) {
                for (auto x: out[t]) {
                    ret[x].push_back(i - len[x] + 1);
                }
            }
        }
    }
};
