template <int M>
struct static_mint {
  static_assert(0 < M, "Module must be positive");
  using mint = static_mint;
  int val;
  static_mint(): val() {}
  static_mint(long long x): val(x % M) { if (val < 0) val += M; }
  mint pow(long long n) const {
    mint ans = 1, x( * this);
    while (n) {
      if (n & 1) ans *= x;
      x *= x;
      n /= 2;
    }
    return ans;
  }
  mint inv() const {
    return pow(M - 2);
  }
  friend mint mpow(const mint & m, long long n) {
    return m.pow(n);
  }//外部使用时 需要对arg1进行强制转换
  friend mint inv(const mint & m) {
    if(m == 0 || m == 1) return mint(1);
    return m.inv();
  }
  mint operator + () const {
    mint m;
    m.val = val;
    return m;
  }
  mint operator - () const {
    mint m;
    m.val = M - val;
    return m;
  }
  mint & operator += (const mint & m) {
    if ((val += m.val) >= M) val -= M;
    return *this;
  }
  mint & operator -= (const mint & m) {
    if ((val -= m.val) < 0) val += M;
    return *this;
  }
  mint & operator *= (const mint & m) {
    val = (long long) val * m.val % M;
    return *this;
  }
  mint & operator /= (const mint & m) {
    val = (long long) val * m.inv().val % M;
    return *this;
  }
  friend mint operator + (const mint & lhs,
    const mint & rhs) {
    return mint(lhs) += rhs;
  }
  friend mint operator - (const mint & lhs,
    const mint & rhs) {
    return mint(lhs) -= rhs;
  }
  friend mint operator * (const mint & lhs,
    const mint & rhs) {
    return mint(lhs) *= rhs;
  }
  friend mint operator / (const mint & lhs,
    const mint & rhs) {
    return mint(lhs) /= rhs;
  }
  friend mint operator % (const mint & lhs,
    const LL & rhs) {
    return mint(lhs.val % rhs);
  }
  friend bool operator == (const mint & lhs,
    const mint & rhs) {
    return lhs.val == rhs.val;
  }
  friend bool operator != (const mint & lhs,
    const mint & rhs) {
    return lhs.val != rhs.val;
  }
  mint & operator++() {
    return *this += 1;
  }
  mint & operator--() {
    return *this -= 1;
  }
  mint operator++(int) {
    mint result( * this);* this += 1;
    return result;
  }
  mint operator--(int) {
    mint result( * this);* this -= 1;
    return result;
  }
  bool sqrt(mint &res) const {
    if (MOD == 2 || x == 0) {
      res = *this;
      return true;
    }
    if (pow((MOD - 1) / 2) != 1) return false;
    if (MOD % 4 == 3) {
      res = pow((MOD + 1) / 4);
      return true;
    }
    int pw = (MOD - 1) / 2;
    int K = 30;
    while((1 << K) > pw) K--;
    while(true) {
      mint t = myRand(MOD);
      mint a = 0, b = 0, c = 1;
      for (int k = K; k >= 0; k--) {
        a = b * b;
        b = b * c * 2;
        c = c * c + a * *this;
        if (((pw >> k) & 1) == 0) continue;
        a = b;
        b = b * t + c;
        c = c * t + a * *this;
      }
      if (b == 0) continue;
      c -= 1;
      c *= mint() - b.inv();
      if (c * c == *this) {
        res = c;
        return true;
      }
    }
    assert(false);
  }
  template <typename T> explicit operator T() const {
    return T(val);
  }
  friend std::ostream & operator << (std::ostream & os,
    const mint & m) {
    return os << m.val;
  }
  friend std::istream & operator >> (std::istream & is, mint & m) {
    long long x;
    is >> x;
    m = x;
    return is;
  }
};
using mint = static_mint<MOD>;
mint fac[N],invf[N],invv[N];
void init(int n) {
    fac[0] = 1;
    for(int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i;
    invf[n] = inv(fac[n]);
    invf[0] = invf[1] = 1;
    for(int i = n - 1; i >= 2; i--) invf[i] = invf[i + 1] * (i + 1); 
    invv[0] = invv[1] = 1;
    for(int i = 2; i <= n; i++) invv[i] = invv[MOD % i] * (MOD - MOD / i); 
}
mint binom(int x, int y) {
    if(y > x) return 0;
    return fac[x] * invf[x - y] * invf[y];
}
