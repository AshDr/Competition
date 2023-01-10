int rev[600005];
struct Poly {
    mint x[600005];
    int len;
    //remember set len
    mint& operator[](int idx) { return x[idx]; }
    void cpy(Poly &a, int len) {
        for (int i = 0; i < len; ++i) x[i] = a.x[i];
        return ;
    }
    void clr(int len) {
        for (int i = 0; i < len; ++i) x[i] = 0;
        return ;
    }
    void print(int len) {  
        for(int i = 0; i < len; i++) cout << x[i] << " \n"[i == len - 1];
    }
    void ntt(int w, int b) {
        int len = 1 << w;
        for (int i = 0; i < len; ++i) {
            rev[i] = rev[i >> 1] >> 1 | ((i & 1) << (w - 1));
            if (i < rev[i]) swap(x[i], x[rev[i]]);
        }
        for (int l = 2; l <= len; l <<= 1) {
            int m = l >> 1;
            mint omega = mpow(mint(3), (MOD - 1) / l);
            if (b) omega = mpow(omega, MOD - 2);
            for (int i = 0; i < len; i += l) {
                mint tomega = 1;
                for (int j = i; j < i + m; ++j, (tomega *= omega)) {
                    mint t = tomega * x[j + m];
                    x[j + m] = (x[j] - t);
                    x[j] = (x[j] + t);
                }
            }
        }
        if(b) {
            mint invn = mpow(mint(len),MOD - 2);
            for(int i = 0; i < len; i++) x[i] = (x[i] * invn);
        }
        return ;
    }
    Poly operator * (Poly b) {
        Poly a = *this,c;
        int N = a.len + b.len;
        int limit = 0;
        while((1 << limit) <= N) limit++;
        a.ntt(limit,0);b.ntt(limit,0);
        for(int i = 0; i < (1 << limit); i++) c[i] = a[i] * b[i];
        c.ntt(limit,1);
        //not reverse a and b here
        return c;
    }
};
Poly inversion(Poly &a, Poly &b, Poly &c, int n) {
    b.clr(2 * n);
    if (a.x[0] == 1) b.x[0] = 1;
    else b.x[0] = mpow(a.x[0], MOD - 2);
    //5 -> w = 4 2^4
    //     
    for (int w = 1; (1 << (w - 1)) < n; ++w) { 
        int len = 1 << w;
        //a = f
        //c = f -> ntt 扩展到 (1 << (w + 1))
        //b = f^-1 (1 << (w - 1)) 扩展到 (1 << (w + 1))
        c.cpy(a, len), c.ntt(w + 1, 0), b.ntt(w + 1, 0); //因为在len这一次最后最大次数是*2的
        for (int i = 0; i < (len << 1); ++i) (b.x[i] *= MOD + 2ll - b.x[i] * c.x[i]);
        b.ntt(w + 1, 1); 
        for (int i = len; i < (len << 1); ++i) b.x[i] = 0;
    }
    return b;   
}