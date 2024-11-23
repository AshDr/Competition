/*
vector 实现的Matrix太慢了，所以直接用数组
n*n
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
*/

/*
n * n
*/
template <int P>
struct Matrix {
  int n;
  vector<vector<mint<P>>> v;

  Matrix(int n, int d = 0) : n(n), v(n, vector<mint<P>>(n)) {
    if (d)
      for (int i = 0; i < n; i++) v[i][i] = d;
  }

  Matrix operator*(const Matrix &a) const {
    Matrix re(n);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++) {
          re.v[i][j] += v[i][k] * a.v[k][j];
        }
      }
    }
    return re;
  }
  Matrix operator*=(const Matrix &a) {
    (*this) = (*this) * a;
    return (*this);
  }

  mint<P> elim(Matrix &b) {
    mint<P> re = 1;
    Matrix a = *this;
    for (int i = 0; i < n; i++) {
      if (a.v[i][i].v == 0) {
        for (int j = i + 1; j < n; j++) {
          if (a.v[j][i].v) {
            swap(a.v[i], a.v[j]);
            swap(b.v[i], b.v[j]);
            re = -re;
            break;
          }
        }
        if (a.v[i][i].v == 0) return 0;
      }
      const mint<P> x = a.v[i][i], invx = x.inv();
      re *= x;
      for (int j = 0; j < n; j++) {
        a.v[i][j] *= invx;
        b.v[i][j] *= invx;
      }
      for (int k = 0; k < n; k++) {
        if (k == i) continue;
        const mint<P> y = a.v[k][i];
        for (int j = 0; j < n; j++) {
          a.v[k][j] -= a.v[i][j] * y;
          b.v[k][j] -= b.v[i][j] * y;
        }
      }
    }
    return re;
  }

  mint<P> det() {
    Matrix e(n);
    return elim(e);
  }

  Matrix inv() {
    Matrix e(n, 1);
    const mint<P> d = elim(e);
    if (d.v == 0) return Matrix(0);
    return e;
  }

  Matrix pow(long long k) {
    Matrix r(n, 1), a = (*this);
    while (k) {
      if (k & 1) r *= a;
      a *= a;
      k >>= 1;
    }
    return r;
  }
};
