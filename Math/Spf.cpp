int spf[N];
void build(){
    for (int i = 1; i < N; ++i) {
        spf[i]=i;
    }
    for (int i = 2; i < N; ++i) {
        if(spf[i]!=i)continue;
        for (int j = 2*i; j < N; j+=i) {
            if(spf[j]==j)
                spf[j]=i;
        }
    }
}

