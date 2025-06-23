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
const double eps=1e-8;

template <typename T>
struct Matrix {
  int n;
  vector<vector<T>> v;

  Matrix(int n, int d = 0) : n(n), v(n, vector<T>(n)) {
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

  // double version
 T elim(Matrix &b, int& flag) { // b是增广矩阵的右侧ans列
    T re = 1;
    Matrix a = *this;
    for (int i = 0; i < n; i++) {
      if (fabs(a.v[i][i]) < eps) {
        for (int j = 0; j < n; j++) {
          if(fabs(a.v[j][j])>eps&&j<i) continue;
          if (fabs(a.v[j][i]) > eps) {
            swap(a.v[i], a.v[j]);
            swap(b.v[i], b.v[j]);
            re = -re;
            break;
          }
        }
        if (fabs(a.v[i][i]) < eps) {
          continue; // 系数矩阵不满秩，无解或者没有唯一解 
        }
      }
      const T x = a.v[i][i], invx = 1.0 / x;
      re *= x;
      for (int j = 0; j < n; j++) {
        a.v[i][j] *= invx;
        b.v[i][j] *= invx;
      }
      for (int k = 0; k < n; k++) {
        if (k == i) continue;
        const T y = a.v[k][i];
        for (int j = 0; j < n; j++) {
          a.v[k][j] -= a.v[i][j] * y;
          b.v[k][j] -= b.v[i][j] * y;
        }
      }
    }
    // 1 唯一解， 0 无穷解， -1 无解
    int key=1;
    for(int i=0;i<n;i++){
  		if(fabs(a.v[i][i])<eps){
	  		if(fabs(b.v[i][0])>eps) key=-1;//无解优先级更高
	  		else if(key!=-1) key=0;
		  }
	  }
    if(key==1) {
      for(int i=0; i<n; i++) {
        cout << "x" << i+1 << "=" << fixed << setprecision(2) << (fabs(b.v[i][0]/a.v[i][i])<eps?0:b.v[i][0]/a.v[i][i]) << "\n";
      }
    }else {
      cout<<key<<"\n";
      re=0;
    }
    flag=key;
    return re;
  }

  T det() {
    Matrix e(n);
    int flag=0;
    return elim(e,flag);
  }

  T det_noinv() {
    T ret=1;
    Matrix a = *this;
    int f=0;
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; ++j) {
        while (a.v[i][i] != 0) {
          T div = a.v[j][i] / a.v[i][i];
          for (int k = i; k < n; ++k) {
            a.v[j][k] = (a.v[j][k] - 1ll * div * a.v[i][k]);
          }
          swap(a.v[i], a.v[j]);
          f^=1;
        }  // 对第 i 行和第 j 行做辗转相减。
        swap(a.v[i], a.v[j]);
        f^=1;
      }
    }
    for (int i = 0; i < n; i++) ret *= a.v[i][i];
    if(f) ret=-ret;
    return ret;
  }

  Matrix inv() {
    Matrix e(n, 1);
    int flag=1;
    const T d = elim(e,flag);
    if (d == 0) return Matrix(0);
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