struct WELP {
    multiset<int, greater<int> > smol;
    multiset<int> big; // median should be max of smol
    ll sm = 0, bi = 0;

    void balance() {
        while (smol.size() < big.size()) {
            sm += *big.begin();
            bi -= *big.begin();
            smol.insert(*big.begin());
            big.erase(big.begin());
        }
        while (smol.size() > big.size() + 1) {
            sm -= *smol.begin();
            bi += *smol.begin();
            big.insert(*smol.begin());
            smol.erase(smol.begin());
        }
    }

    void push(int x) {
        if (smol.empty() || x <= *smol.begin()) {
            smol.insert(x);
            sm += x;
        } else {
            bi += x;
            big.insert(x);
        }
        balance();
    }

    void eras(int x) {
        auto it = smol.find(x);
        if (it != smol.end()) {
            smol.erase(it);
            sm -= x;
        } else {
            bi -= x;
            big.erase(big.find(x));
        }
        balance();
    }

    ll cost() {
        // the cost to make the all elements equal the median
        int f = *smol.begin();
        return f * smol.size() - sm + bi - f * big.size();
    }
};
