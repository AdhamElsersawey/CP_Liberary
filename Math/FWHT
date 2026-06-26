// 1->xor , 2->or ,3->and
// all possible X pairs
// size(v) must be power of 2
void FWHT(vector<ll> &v, bool inv, int tpy) {
    int n = v.size();
    for (int len = 1; len * 2 <= n; len <<= 1) {
        for (int i = 0; i < n; i += 2 * len) {
            for (int j = 0; j < len; j++) {
                ll u = v[i + j], uu = v[i + j + len];
                if (tpy == 1)v[i + j] = u + uu, v[i + j + len] = u - uu;
                else {
                    if (inv) {
                        if (tpy == 2)v[i + len + j] -= v[i + j];
                        else v[i + j] -= v[i + len + j], (v[i + j] += mod) %= mod;
                    } else {
                        if (tpy == 2)v[i + len + j] += v[i + j];
                        else v[i + j] += v[i + len + j];
                    }
                }
            }
        }
    }
    if (inv && tpy == 1) for (auto &i: v)i /= n;
}
