struct SparseTable {
    vector<vector<int> > sp;
    vector<int> LOG;
    vector<int> arr;
    int n, LG;
 
    SparseTable(vector<int> &_arr) {
        n = (int) _arr.size();
 
        LOG = vector<int>(n + 1);
        LOG[0] = LOG[1] = 0;
 
        for (int i = 2; i <= n; ++i) {
            LOG[i] += LOG[i - 1] + !(i & (i - 1));
        }
        arr = _arr;
        LG = LOG[n];
        sp = vector<vector<int> >(LG + 1, vector<int>(n));
 
        build();
    }
 
    int merge(int lfV, int rtV) {
        return lfV & rtV;
    }
 
    void build() { // O( n log(n) )
        sp[0] = arr;
 
        for (int lvl = 1; lvl <= LG; ++lvl) {
            for (int j = 0; j + (1 << lvl) <= n; ++j) {
                sp[lvl][j] = merge(sp[lvl - 1][j], sp[lvl - 1][j + (1 << (lvl - 1))]);
            }
        }
    }
 
    int query(int l, int r) { // O( 1 )
        int lg = LOG[r - l + 1];
 
        return merge(sp[lg][l], sp[lg][r - (1 << lg) + 1]);
    }
 
    int query2(int l, int r) { // O( LogN )
        int lg = LOG[n];
        int ans = ~0;
        for (int j = lg; ~j; --j) {
            if ((1 << j) <= (r - l + 1)) {
                ans = merge(ans, sp[j][l]);
                l += (1 << j);
            }
        }
 
        return ans;
    }
};
 
