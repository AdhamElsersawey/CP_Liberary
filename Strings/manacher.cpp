vector<int> d_odd, d_even; // for even the pos i includes i-1
vector<int> manacher_odd(string s) {
    int n = s.size();
    s = "$" + s + "^";
    vector<int> p(n + 2);
    int l = 0, r = 1;
    for(int i = 1; i <= n; i++) {
        p[i] = min(r - i, p[l + (r - i)]);
        while(s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if(i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}
void manacher(string s) {
    string t;
    for(auto c: s) {
        t += string("#") + c;
    }
    auto res = manacher_odd(t + "#");
    d_odd.resize(s.size(), {});
    d_even.resize(s.size(), {});
    for (int i = 0; i < s.size(); ++i) {
        d_odd[i] = res[2 * i + 1] / 2;
        d_even[i] = (res[2 * i] - 1) / 2;
    }
}
