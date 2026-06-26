

auto kmp(const string &s) {
    int n = s.length();
    vector<int> pi(n);
    for (int i = 1, j = 0; i < n; i++) {
        while (j && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}

auto kmp_auto(string s) {
    vector<ll> pi = kmp(s);
    vector aut(s.length(), vector<int>(26));
    aut[0][s[0] - 'a'] = 1;
    for (int i = 1; i < s.length(); ++i) {
        for (int j = 0; j < 26; j++) {
            if (s[i] - 'a' == j)aut[i][j] = i + 1;
            else aut[i][j] = aut[pi[i - 1]][j];
        }
    }
    return aut;
}
