struct Aho {
    int cn, patt;
    /*
        nxt[u][c] = next node when we are in node u and read character c
        out[u] = list of pattern indices that end exactly at node u
    */
    vector<vector<int> > nxt, out;
    /*
        link[u] = failure link of node u
        out_link[u] = next node in suffix chain that contains output
    */
    vector<int> link, out_link;
    /*
        ord = BFS order of nodes
        we use it later to propagate occurrences through failure links
    */
    vector<int> ord;

    const int con = 26; // alphabet size

    /*
        Create a new node in the trie
    */
    int node() {
        /*
            Each node has 26 transitions initially pointing to 0
        */
        nxt.emplace_back(con, 0);

        /*
            Failure link initially points to root
        */
        link.emplace_back(0);

        /*
            Output suffix link initially 0
        */
        out_link.emplace_back(0);

        /*
            No pattern ends here initially
        */
        out.emplace_back();

        /*
            return index of this node
        */
        return cn++;
    }

    Aho(): cn(0), patt(0) {
        node();
    }

    int get(char c) {
        return c - 'a';
    }

    //  Insert pattern into trie
    //  Return terminal node of this pattern
    int add(const string &s, int ind) {
        int u = 0; //root
        for (auto c: s) {
            int x = get(c);
            //   If transition does not exist, create new node
            if (!nxt[u][x])
                nxt[u][x] = node();
            //  Move to next node
            u = nxt[u][x];
        }
        //  Pattern ends at node u
        out[u].push_back(ind);
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
            /*
                Save BFS order
                Needed later for propagating counts
            */
            ord.push_back(u);
            //  Process all characters automata
            for (int c = 0; c < con; c++) {
                int v = nxt[u][c];
                /*
                    If transition doesn't exist
                    use failure transition
                */
                if (!v) {
                    /*
                        Root stays root
                        otherwise follow failure link
                    */
                    nxt[u][c] = (u == 0 ? 0 : nxt[link[u]][c]);
                } else {
                    /*
                        Build failure link
                        similar to KMP fallback
                    */
                    link[v] = (u ? nxt[link[u]][c] : 0);
                    /*
                        Build output link
                        next suffix node that has pattern ending
                    */
                    out_link[v] = out[link[v]].empty() ? out_link[link[v]] : link[v];
                    q.push(v);
                }
            }
        }
    }

    /*
        Move in automaton with character c
    */
    int go(int u, char c) {
        /*
            Since we filled missing transitions in build,
            this is just direct lookup
        */
        return nxt[u][get(c)];
    }
};
