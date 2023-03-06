struct matrix {
    ll a[3][3];
    matrix() {
        for(int i=1;i<=2;i++) {
            for(int j=1;j<=2;j++) {
                a[i][j]=0;
            }
        }
    }
    friend matrix operator * (const matrix& lhs,const matrix& rhs) {
        matrix res;
        for(int i=1;i<=2;i++) {
            for(int j=1;j<=2;j++) {
                for(int k=1; k<=2; k++) {
                    res.a[i][j]+=(lhs.a[i][k]*rhs.a[k][j])%mod;
                    res.a[i][j]%=mod;
                }
            }
        }
        return res;
    };
};
matrix qpow(matrix base,ll x) {
    matrix res;
    for(int i=1;i<=2;i++) {
        for(int j=1;j<=2;j++) {
            if(i==j) res.a[i][j]=1;
            else res.a[i][j]=0;
        }
    }
    while(x) {
        if(x&1) {
            res=res*base;
        }
        base=base*base;
        x>>=1;
    }
    return res;
}