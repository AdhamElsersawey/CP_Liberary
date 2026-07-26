struct BinaryTrie {
    static const int BIT = 50;

    struct Node {
        Node *child[2];
        int cnt;

        Node() {
            child[0] = child[1] = nullptr;
            cnt = 0;
        }
    };

    Node *root = new Node();

    void insert(int x) {
        Node *cur = root;
        cur->cnt++;
        for (int i = BIT; i >= 0; i--) {
            int b = (x >> i) & 1;
            if (!cur->child[b]) {
                cur->child[b] = new Node();
            }
            cur = cur->child[b];
            cur->cnt++;
        }
    }

    void erase(int x) {
        Node *cur = root;
        cur->cnt--;
        for (int i = BIT; i >= 0; i--) {
            int b = (x >> i) & 1;
            Node *nxt = cur->child[b];
            if (!nxt) return;
            nxt->cnt--;
            cur = nxt;
        }
    }

    // number of values s.t. val ^ x < k
    int query(int x, int k) {
        Node *cur = root;
        int ans = 0;
        for (int i = BIT; i >= 0; i--) {
            if (!cur) break;
            int b1 = x >> i & 1, b2 = k >> i & 1;
            if (b2 == 1) {
                if (cur->child[b1]) ans += cur->child[b1]->cnt;
                cur = cur->child[!b1];
            } else cur = cur->child[b1];
        }
        return ans;
    }

    int maxor(int x) {
        Node *cur = root;
        if (!cur) return 0;
        int res = 0;
        for (int i = BIT; i >= 0; i--) {
            int bit = (x >> i) & 1;
            int want = bit ^ 1;
            if (cur->child[want] && cur->child[want]->cnt > 0) {
                res |= (1ll << i);
                cur = cur->child[want];
            } else if (cur->child[bit] && cur->child[bit]->cnt > 0) {
                cur = cur->child[bit];
            } else break;
        }

        return res;
    }

    int count(int x) const {
        Node *cur = root;
        for (int i = BIT; i >= 0; --i) {
            int b = (x >> i) & 1;
            Node *nx = cur->child[b];
            if (!nx) return 0;
            cur = nx;
        }
        return cur->cnt;
    }

    pair<int, ll> maxAnd(Node *node, int b, int x) const {
        if (!node || node->cnt == 0) return {0, 0};
        if (b < 0) return {0, node->cnt};

        int xb = (x >> b) & 1;

        if (xb == 1) {
            Node *one = node->child[1];
            if (one && one->cnt > 0) {
                auto res = maxAnd(one, b - 1, x);
                res.first |= (1 << b);
                return res;
            }
            return maxAnd(node->child[0], b - 1, x);
        }
        Node *l = node->child[0];
        Node *r = node->child[1];

        bool hasL = (l && l->cnt > 0);
        bool hasR = (r && r->cnt > 0);

        if (!hasL && !hasR) return {0, 0};
        if (hasL && !hasR) return maxAnd(l, b - 1, x);
        if (hasR && !hasL) return maxAnd(r, b - 1, x);

        auto A = maxAnd(l, b - 1, x);
        auto B = maxAnd(r, b - 1, x);

        if (A.first > B.first) return A;
        if (B.first > A.first) return B;
        // and , count
        return {A.first, A.second + B.second};
    }

    pair<int, ll> maxAnd(int x) const {
        if (!root || root->cnt == 0) return {0, 0};
        return maxAnd(root, BIT, x);
    }
};
