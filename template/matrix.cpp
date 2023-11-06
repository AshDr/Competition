/*
vector 实现的Matrix太慢了，所以直接用数组
*/
struct Matrix {
    int r,w;
    ll a[2][2];
    void clear() {
        for(int i = 0 ; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                a[i][j] = 0;
            }
        }
    }
    void indetity() {
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                if(i == j) a[i][j] = 1;
                else a[i][j] = 0;
            }
        }
    }
    
}Turn;

Matrix operator + (const Matrix& A, const Matrix& B) {
    Matrix res;
    res.clear();
    for (int i = 0; i < 2; i ++ )
        for (int j = 0; j < 2; j ++ )
            res.a[i][j] = (A.a[i][j] + B.a[i][j]) % MOD;
    return res;
}
Matrix operator * (const Matrix& A, const Matrix& B) {
    Matrix res;
    res.clear();
    for (int i = 0; i < 2; i ++ )
        for (int j = 0; j < 2; j ++ )
            for (int k = 0; k < 2; k ++ )
                (res.a[i][j] += (A.a[i][k] * B.a[k][j])) %= MOD;
    return res;
}
Matrix qpow(Matrix A, ll b) {
    Matrix res;
    res.indetity();
    while (b) {
        if (b & 1) res = res * A;
        A = A * A;//, A = A % mod;
        b >>= 1;
    }
    return res;
}