ll pw(int x,int k){
int ret=1;
while(k){
    if(k&1)ret=ret*x%mod;
    x=x*x%mod;
    k>>=1;
}
return ret;
}
int fact[N], invr[N];

void build() {
    fact[0] = 1;
    for(int i = 1; i < N; ++i) fact[i]=1ll*fact[i - 1]*i%mod;
    invr[N - 1] = pw(fact[N - 1], mod - 2);
    for(int i = N - 2; ~i; --i) invr[i] = 1ll*invr[i+1]*(i+1)%mod;
}
 
int nCr(int n, int r) {
    if(n < r) return 0;
    return 1ll*fact[n]*invr[n-r]%mod*invr[r]%mod;
}
// Z catalan(int n) {
     //   return fact[2 * n] / fact[n] / fact[n + 1];
    //}
