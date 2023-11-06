constexpr int MOD = 998244353;
using ll = long long;
// assume -MOD <= x < 2P
int norm(int x) {
  if (x < 0) {
    x += MOD;
  }
  if (x >= MOD) {
    x -= MOD;
  }
  return x;
}
template <class T> T power(T a, ll b) {
  T res = 1;
  for (; b; b /= 2, a *= a) {
    if (b % 2) {
      res *= a;
    }
  }
  return res;
}
struct mint {
  int x;
  mint(int x = 0) : x(norm(x)) {}
  mint(ll x) : x(norm(x % MOD)) {}
  mint(ull x) : x(x % MOD) {}
  int val() const { return x; }
  mint operator-() const { return mint(norm(MOD - x)); }
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
    assert(x != 0);
    return power(*this, MOD - 2);
  }
  mint &operator*=(const mint &rhs) {
    x = ll(x) * rhs.x % MOD;
    return *this;
  }
  mint &operator+=(const mint &rhs) {
    x = norm(x + rhs.x);
    return *this;
  }
  mint &operator-=(const mint &rhs) {
    x = norm(x - rhs.x);
    return *this;
  }
  mint &operator/=(const mint &rhs) { return *this *= rhs.inv(); }
  mint & operator++() {
    return *this += 1;
  }
  mint & operator--() {
    return *this -= 1;
  }
  friend bool operator != (const mint & lhs, const mint & rhs) {
     return lhs.val() != rhs.val();
  }
  friend bool operator == (const mint & lhs, const mint & rhs) {
    return lhs.val() == rhs.val();
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
      mint t = (ull)myrand() % MOD;
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
  friend mint operator*(const mint &lhs, const mint &rhs) {
    mint res = lhs;
    res *= rhs;
    return res;
  }
  friend mint operator+(const mint &lhs, const mint &rhs) {
    mint res = lhs;
    res += rhs;
    return res;
  }
  friend mint operator-(const mint &lhs, const mint &rhs) {
    mint res = lhs;
    res -= rhs;
    return res;
  }
  friend mint operator/(const mint &lhs, const mint &rhs) {
    mint res = lhs;
    res /= rhs;
    return res;
  }
  friend std::istream &operator>>(std::istream &is, mint &a) {
    ll v;
    is >> v;
    a = mint(v);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const mint &a) {
    return os << a.val();
  }
};
struct Comb {
  int n;
  std::vector<mint> _fac;
  std::vector<mint> _invfac;
  std::vector<mint> _inv;

  Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}
  Comb(int n) : Comb() { init(n); }

  void init(int m) {
    if (m <= n)
      return;
    _fac.resize(m + 1);
    _invfac.resize(m + 1);
    _inv.resize(m + 1);

    for (int i = n + 1; i <= m; i++) {
      _fac[i] = _fac[i - 1] * i;
    }
    _invfac[m] = _fac[m].inv();
    for (int i = m; i > n; i--) {
      _invfac[i - 1] = _invfac[i] * i;
      _inv[i] = _invfac[i] * _fac[i - 1];
    }
    n = m;
  }

  mint fac(int m) {
    if (m > n)
      init(2 * m);
    return _fac[m];
  }
  mint invfac(int m) {
    if (m > n)
      init(2 * m);
    return _invfac[m];
  }
  mint inv(int m) {
    if (m > n)
      init(2 * m);
    return _inv[m];
  }
  mint binom(int n, int m) {
    if (n < m || m < 0)
      return 0;
    return fac(n) * invfac(m) * invfac(n - m);
  }
} comb;