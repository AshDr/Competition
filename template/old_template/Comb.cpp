LL fac[N],invfac[N];
void init(int n) {
    fac[0] = 1;
    for(int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % MOD;
    invfac[n] = qpow(fac[n],MOD - 2);
    invfac[0] = invfac[1] = 1;
    for(int i = n - 1; i >= 2; i--) invfac[i] = (i + 1) * invfac[i + 1] % MOD;
}
LL binom(int n, int m) {
    if(m > n) return 0;
    return fac[n] * invfac[m] % MOD * invfac[n - m] % MOD;
}