int rev[600005];
void cpy(mint *a, mint *b, int len) {
    for (int i = 0; i < len; ++i) b[i] = a[i];
    return ;
}
void clr(mint *a, int len) {
    for (int i = 0; i < len; ++i) a[i] = 0;
    return ;
}
void print(mint *a, int len) {  
    for(int i = 0; i < len; i++) cout << a[i] << " \n"[i == len - 1];
}
void ntt(mint *a, int w, int b) {// w is bit
    int len = 1 << w;
    for (int i = 0; i < len; ++i) {
        rev[i] = rev[i >> 1] >> 1 | ((i & 1) << (w - 1));
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    }
    for (int l = 2; l <= len; l <<= 1) {
        int m = l >> 1;
        mint omega = mpow(mint(3), (MOD - 1) / l);
        if (b) omega = mpow(omega, MOD - 2);
        for (int i = 0; i < len; i += l) {
            mint tomega = 1;
            for (int j = i; j < i + m; ++j, (tomega *= omega)) {
                mint t = tomega * a[j + m];
                a[j + m] = (a[j] - t);
                a[j] = (a[j] + t);
            }
        }
    }
    if(b) {
        mint invn = mpow(mint(len),MOD - 2);
        for(int i = 0; i < len; i++) a[i] = (a[i] * invn);
    }
    return ;
}
void Mul(mint *a, mint *b,mint *c, int n) {//n must be 2^k
    int N = n + n;
    int limit = 0;
    while((1 << limit) <= N) limit++;
    ntt(a,limit,0);ntt(b,limit,0);
    for(int i = 0; i < (1 << limit); i++) c[i] = a[i] * b[i];
    ntt(a,limit,1);ntt(b,limit,1);ntt(c,limit,1);
}
void Mula(mint *a, mint *b,int n) {//n must be 2^k
    int N = n + n;
    int limit = 0;
    while((1 << limit) <= N) limit++;
    ntt(a,limit,0);ntt(b,limit,0);
    for(int i = 0; i < (1 << limit); i++) a[i] = a[i] * b[i];
    ntt(a,limit,1);ntt(b,limit,1);
}
void Inversion(mint *a, mint *b, int n) {//n must be 2^k 
    static mint tmp1[N];
    clr(b, 2 * n);
    if (a[0] == 1) b[0] = 1;
    else b[0] = mpow(a[0], MOD - 2);
    //5 -> w = 4 2^4
    //     
    for (int w = 1; (1 << (w - 1)) < n; ++w) { 
        int len = 1 << w;
        //a = f
        //c = f -> ntt 扩展到 (1 << (w + 1))
        //b = f^-1 (1 << (w - 1)) 扩展到 (1 << (w + 1))
        cpy(a, tmp1, len), ntt(tmp1, w + 1, 0), ntt(b, w + 1, 0); //因为在len这一次最后最大次数是*2的
        for (int i = 0; i < (len << 1); ++i) (b[i] *= MOD + 2ll - b[i] * tmp1[i]);
        ntt(b, w + 1, 1);
        for (int i = len; i < (len << 1); ++i) b[i] = 0;
    }
    for(int i = 0; i < (n << 1); i++) tmp1[i] = 0;
    for(int i = n; i < (n << 1); i++) b[i] = 0;
}// b is inversion
void Der(mint *a, mint *b, int n) { //n must be 2^k 
    for(int i = 0; i < n - 1; i++) {
        b[i] = a[i + 1] * (i + 1);
    }
    b[n - 1] = 0;
}
void Integ(mint *a,mint *b, int n) {
    b[0] = 0;
    for(int i = 1; i < n; i++) {
        b[i] = a[i - 1] * inv(mint(i));
    }
}
void Ln(mint *a, mint *b, int n) {//n must be 2^k a[0] must be 1
    static mint da[N],iva[N],mulres[N];
    Der(a, da, n);
    Inversion(a, iva, n);
    Mul(da,iva,mulres,n);
    Integ(mulres, b, n);
    for(int i = 0; i < (n << 1); i++) da[i]=iva[i]=mulres[i]=0;
}
void Exp(mint *a, mint *b, int n) {//n must be 2^k. a[0] must be 0
    if(n == 1) {
        b[0] = 1;
        return ;
    }
    static mint lnb[N];
    Exp(a, b, (n >> 1));Ln(b, lnb, n);
    lnb[0] = a[0]-lnb[0]+1;
    for(int i = 1; i < n; i++) lnb[i] = a[i]-lnb[i];
    Mula(b, lnb, n);
    for(int i = n,l = (n << 1); i < l; i++) b[i] = lnb[i] = 0;
    
}
void Sqrt(mint *a, mint *b, int n) {//n must be 2^k. a[0] must be 1 or 0
    b[0] = 1;
    //b[0]=0;
    mint inv2 = inv(mint(2));
    static mint tmpa[N],tmpb[N];
    for(int i = 1; i < (n << 1);  i <<= 1) {
        cpy(a, tmpa, i);
        Inversion(b, tmpb, i);
        Mula(tmpa, tmpb, i);
        for(int j = 0; j < i; j++) b[j] = (b[j] + tmpa[j]) * inv2;
        for(int j = i; j < (i << 1); j++) b[j] = 0;
    }
    for(int i = 0; i < (n << 1); i++) tmpa[i] = tmpb[i] = 0;
    for(int i = n; i < (n << 1); i++) b[i] = 0; 
}//b_x = (a_x+(b0_x)^2) / (2*b0_x) = (a_x/b0_x + b0_x)/2
void Pow(mint *a, mint *b, int n, LL k) {
    static mint c[N];
    Ln(a, c, n);
    for(int i = 0; i < n; i++) c[i] *= k;
    Exp(c, b, n);
}
//常数有一点点大
mint f[N],g[N];
//记得改mod
//读入数组后记得先初始化limit，作为参数传入 
int limit;
for(limit=1;limit <= n; limit <<= 1);