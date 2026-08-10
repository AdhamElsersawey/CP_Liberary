//dp[i] = min(dp[j] + m[j]*x[i])
struct Line {
    ll m, c;
    ll eval(ll x) { return m * x + c; }
};

struct Node {
    Line line;
    Node *left, *right;

    Node(Line l) : line(l), left(nullptr), right(nullptr) {
    }
};

struct LiChao {
    Node *root = nullptr;
    ll MIN_X = -2e9, MAX_X = 2e9;

    void insert_line(Node * &node, ll l, ll r, Line new_line) {
        if (!node) {
            node = new Node(new_line);
            return;
        }
        ll mid = (l + r) >> 1;
        // change to > if max
        bool left_better = new_line.eval(l) <= node->line.eval(l);
        bool mid_better = new_line.eval(mid) <= node->line.eval(mid);
        if (mid_better) {
            swap(node->line, new_line);
        }

        if (l == r) return;

        if (left_better != mid_better) {
            insert_line(node->left, l, mid, new_line);
        } else {
            insert_line(node->right, mid + 1, r, new_line);
        }
    }

    void add_line(ll m, ll c) {
        insert_line(root, MIN_X, MAX_X, {m, c});
    }

    void insert_segment(Node * &node, ll l, ll r, ll ql, ll qr, Line new_line) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            insert_line(node, l, r, new_line);
            return;
        }
        if (!node) node = new Node({0, OO});

        ll mid = (l + r) >> 1;
        insert_segment(node->left, l, mid, ql, qr, new_line);
        insert_segment(node->right, mid + 1, r, ql, qr, new_line);
    }

    void add_segment(ll ql, ll qr, ll m, ll c) {
        if (ql <= qr) {
            insert_segment(root, MIN_X, MAX_X, ql, qr, {m, c});
        }
    }

    ll query(Node *node, ll l, ll r, ll x) {
        if (!node) return OO;
        ll mid = l + (r - l) / 2;
        ll cur = node->line.eval(x);

        if (l == r) return cur;

        if (x <= mid) {
            return min(cur, query(node->left, l, mid, x));
        }
        return min(cur, query(node->right, mid + 1, r, x));
    }

    ll get_min(ll x) {
        return query(root, MIN_X, MAX_X, x);
    }
};
