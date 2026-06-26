int mob[N];
vector<int> dv[N];

void mobius() {
    sieve();
    for (int i = 1; i < N; i++)mob[i] = 1;
    for (auto p: primes) {
        for (int i = p; i < N; i += p) {
            if ((i / p) % p == 0)mob[i] = 0;
            else mob[i] *= -1;
        }
    }
    for (int i = 1; i < N; ++i) {
        if (mob[i] != 0) {
            for (int j = i; j < N; j += i) {
                dv[j].push_back(i);
            }
        }
    }
}
