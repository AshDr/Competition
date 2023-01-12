int rev[600005];
mint a[N],b[N],c[N],tmp1[N],tmp2[N],tmp3[N];
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
void mul(mint *a, mint *b,mint *c, int n) {//n must be 2^k
    int N = n + n;
    int limit = 0;
    while((1 << limit) <= N) limit++;
    ntt(a,limit,0);ntt(b,limit,0);
    for(int i = 0; i < (1 << limit); i++) c[i] = a[i] * b[i];
    ntt(a,limit,1);ntt(b,limit,1);ntt(c,limit,1);
}
void inversion(mint *a, mint *b, mint *c, int n) {//n must be 2^k 
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
        cpy(a, c, len), ntt(c, w + 1, 0), ntt(b, w + 1, 0); //因为在len这一次最后最大次数是*2的
        for (int i = 0; i < (len << 1); ++i) (b[i] *= MOD + 2ll - b[i] * c[i]);
        ntt(b, w + 1, 1);
        for (int i = len; i < (len << 1); ++i) b[i] = 0;
    }
}// b is inversion
void der(mint *a, mint *b, int n) { //n must be 2^k 
    for(int i = 0; i < n - 1; i++) {
        b[i] = a[i + 1] * (i + 1);
    }
    b[n - 1] = 0;
}
void integ(mint *a,mint *b, int n) {
    b[0] = 0;
    for(int i = 1; i < n; i++) {
        b[i] = a[i - 1] * inv(mint(i));
    }
}
void ln(mint *a, mint *b, int n) {//n = len  must be 2^k
    der(a, tmp1, n);
    int bit = 0;
    inversion(a, tmp2, tmp3, n);
    mul(tmp1,tmp2,c,n);
    integ(c, b, n);
}
//读入数组后记得先初始化limit，作为参数传入 
int limit;
for(limit=0;limit <= n;++limit);