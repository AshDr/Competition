template <class T>
constexpr T power(T a, ll b) {
  T res = 1;
  for (; b; b /= 2, a *= a) {
    if (b % 2) {
      res *= a;
    }
  }
  return res;
}
constexpr ll mul(ll a, ll b, ll p) {
  ll res = a * b - ll(1.L * a * b / p) * p;
  res %= p;
  if (res < 0) {
    res += p;
  }
  return res;
}
template <int P>
struct MInt {
  int x;
  constexpr MInt() : x{} {}
  constexpr MInt(ll x) : x{norm(x % getMod())} {}

  static int Mod;
  constexpr static int getMod() {
    if (P > 0) {
      return P;
    } else {
      return Mod;
    }
  }
  constexpr static void setMod(int Mod_) { Mod = Mod_; }
  constexpr int norm(int x) const {
    if (x < 0) {
      x += getMod();
    }
    if (x >= getMod()) {
      x -= getMod();
    }
    return x;
  }
  constexpr int val() const { return x; }
  explicit constexpr operator int() const { return x; }
  constexpr MInt operator-() const {
    MInt res;
    res.x = norm(getMod() - x);
    return res;
  }
  constexpr MInt inv() const {
    assert(x != 0);
    return power(*this, getMod() - 2);
  }
  constexpr MInt pow(long long n) const {
    if (n < 0) {
      return power(*this, -n).inv();
    }
    return power(*this, n);
  }
  constexpr MInt &operator*=(MInt rhs) & {
    x = 1LL * x * rhs.x % getMod();
    return *this;
  }
  constexpr MInt &operator+=(MInt rhs) & {
    x = norm(x + rhs.x);
    return *this;
  }
  constexpr MInt &operator-=(MInt rhs) & {
    x = norm(x - rhs.x);
    return *this;
  }
  constexpr MInt &operator/=(MInt rhs) & { return *this *= rhs.inv(); }
  friend constexpr MInt operator*(MInt lhs, MInt rhs) {
    MInt res = lhs;
    res *= rhs;
    return res;
  }
  friend constexpr MInt operator+(MInt lhs, MInt rhs) {
    MInt res = lhs;
    res += rhs;
    return res;
  }
  friend constexpr MInt operator-(MInt lhs, MInt rhs) {
    MInt res = lhs;
    res -= rhs;
    return res;
  }
  friend constexpr MInt operator/(MInt lhs, MInt rhs) {
    MInt res = lhs;
    res /= rhs;
    return res;
  }
  friend constexpr std::istream &operator>>(std::istream &is, MInt &a) {
    ll v;
    is >> v;
    a = MInt(v);
    return is;
  }
  friend constexpr std::ostream &operator<<(std::ostream &os, const MInt &a) { return os << a.val(); }
  friend constexpr bool operator==(MInt lhs, MInt rhs) { return lhs.val() == rhs.val(); }
  friend constexpr bool operator!=(MInt lhs, MInt rhs) { return lhs.val() != rhs.val(); }
};

template <>
int MInt<0>::Mod = 1;

template <int V, int P>
constexpr MInt<P> CInv = MInt<P>(V).inv();
// 167772161 g=3,   924844033, g=5
constexpr int MOD = 998244353;
using mint = MInt<MOD>;

std::vector<int> rev;
template <int P>
std::vector<MInt<P>> roots{0, 1};

template <int P>
constexpr MInt<P> findPrimitiveRoot() {
  MInt<P> i = 2;
  int k = __builtin_ctz(P - 1);
  while (true) {
    if (power(i, (P - 1) / 2) != 1) {
      break;
    }
    i += 1;
  }
  return power(i, (P - 1) >> k);
}

template <int P>
constexpr MInt<P> primitiveRoot = findPrimitiveRoot<P>();

// if change P, no need to change this
template <>
constexpr MInt<998244353> primitiveRoot<998244353>{31};
// need sz(a)=2^k
template <int P>
constexpr void dft(std::vector<MInt<P>> &a) {
  int n = a.size();
  // 算一遍蝴蝶变换的数组
  if (int(rev.size()) != n) {
    int k = __builtin_ctz(n) - 1;
    rev.resize(n);
    for (int i = 0; i < n; i++) {
      rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
    }
  }

  for (int i = 0; i < n; i++) {
    if (rev[i] < i) {
      std::swap(a[i], a[rev[i]]);
    }
  }
  // 算一遍单位根数组
  if (roots<P>.size() < n) {
    int k = __builtin_ctz(roots<P>.size());
    roots<P>.resize(n);
    while ((1 << k) < n) {
      auto e = power(primitiveRoot<P>, (P - 1) >> (k + 1)); // or 1 << (__builtin_ctz(P - 1) - k - 1)
      for (int i = 1 << (k - 1); i < (1 << k); i++) {
        roots<P>[2 * i] = roots<P>[i];
        roots<P>[2 * i + 1] = roots<P>[i] * e;
      }
      k++;
    }
  }
  for (int k = 1; k < n; k *= 2) {
    for (int i = 0; i < n; i += 2 * k) {
      for (int j = 0; j < k; j++) {
        MInt<P> u = a[i + j];
        MInt<P> v = a[i + j + k] * roots<P>[k + j];
        a[i + j] = u + v;
        a[i + j + k] = u - v;
      }
    }
  }
}

template <int P>
constexpr void idft(std::vector<MInt<P>> &a) {
  int n = a.size();
  std::reverse(a.begin() + 1, a.end());
  dft(a);
  MInt<P> inv = (1 - P) / n;
  for (int i = 0; i < n; i++) {
    a[i] *= inv;
  }
}

template <int P = MOD>
struct Poly : public std::vector<MInt<P>> {
  using Value = MInt<P>;

  Poly() : std::vector<Value>() {}
  explicit constexpr Poly(int n) : std::vector<Value>(n) {}

  explicit constexpr Poly(const std::vector<Value> &a) : std::vector<Value>(a) {}
  constexpr Poly(const std::initializer_list<Value> &a) : std::vector<Value>(a) {}

  template <class InputIt, class = std::_RequireInputIter<InputIt>>
  explicit constexpr Poly(InputIt first, InputIt last) : std::vector<Value>(first, last) {}

  template <class F>
  explicit constexpr Poly(int n, F f) : std::vector<Value>(n) {
    for (int i = 0; i < n; i++) {
      (*this)[i] = f(i);
    }
  }

  constexpr Poly shift(int k) const {
    if (k >= 0) {
      auto b = *this;
      b.insert(b.begin(), k, 0);
      return b;
    } else if (this->size() <= -k) {
      return Poly();
    } else {
      return Poly(this->begin() + (-k), this->end());
    }
  }
  constexpr Poly trunc(int k) const {
    Poly f = *this;
    f.resize(k);
    return f;
  }
  constexpr friend Poly operator+(const Poly &a, const Poly &b) {
    Poly res(std::max(a.size(), b.size()));
    for (int i = 0; i < a.size(); i++) {
      res[i] += a[i];
    }
    for (int i = 0; i < b.size(); i++) {
      res[i] += b[i];
    }
    return res;
  }
  constexpr friend Poly operator-(const Poly &a, const Poly &b) {
    Poly res(std::max(a.size(), b.size()));
    for (int i = 0; i < a.size(); i++) {
      res[i] += a[i];
    }
    for (int i = 0; i < b.size(); i++) {
      res[i] -= b[i];
    }
    return res;
  }
  constexpr friend Poly operator-(const Poly &a) {
    std::vector<Value> res(a.size());
    for (int i = 0; i < int(res.size()); i++) {
      res[i] = -a[i];
    }
    return Poly(res);
  }
  constexpr friend Poly operator*(Poly a, Poly b) {
    if (a.size() == 0 || b.size() == 0) {
      return Poly();
    }
    if (a.size() < b.size()) {
      std::swap(a, b);
    }
    int n = 1, tot = a.size() + b.size() - 1;
    while (n < tot) {
      n *= 2;
    }
    if (((P - 1) & (n - 1)) != 0 || b.size() < 128) {
      Poly c(a.size() + b.size() - 1);
      for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
          c[i + j] += a[i] * b[j];
        }
      }
      return c;
    }
    a.resize(n);
    b.resize(n);
    dft(a);
    dft(b);
    for (int i = 0; i < n; ++i) {
      a[i] *= b[i];
    }
    idft(a);
    a.resize(tot);
    return a;
  }
  constexpr friend Poly operator*(Value a, Poly b) {
    for (int i = 0; i < int(b.size()); i++) {
      b[i] *= a;
    }
    return b;
  }
  constexpr friend Poly operator*(Poly a, Value b) {
    for (int i = 0; i < int(a.size()); i++) {
      a[i] *= b;
    }
    return a;
  }
  constexpr friend Poly operator/(Poly a, Value b) {
    for (int i = 0; i < int(a.size()); i++) {
      a[i] /= b;
    }
    return a;
  }
  constexpr Poly &operator+=(Poly b) { return (*this) = (*this) + b; }
  constexpr Poly &operator-=(Poly b) { return (*this) = (*this) - b; }
  constexpr Poly &operator*=(Poly b) { return (*this) = (*this) * b; }
  constexpr Poly &operator*=(Value b) { return (*this) = (*this) * b; }
  constexpr Poly &operator/=(Value b) { return (*this) = (*this) / b; }
  constexpr Poly deriv() const {
    if (this->empty()) {
      return Poly();
    }
    Poly res(this->size() - 1);
    for (int i = 0; i < this->size() - 1; ++i) {
      res[i] = (i + 1) * (*this)[i + 1];
    }
    return res;
  }
  constexpr Poly integr() const {
    Poly res(this->size() + 1);
    for (int i = 0; i < this->size(); ++i) {
      res[i + 1] = (*this)[i] / (i + 1);
    }
    return res;
  }
  /*
    a[0]!=0
    mod x^1->x^2->...->x^{2^k}->trunc(x^m)
    https://www.luogu.com.cn/problem/P4238
  */
  constexpr Poly inv(int m) const {
    Poly x{(*this)[0].inv()};
    int k = 1;
    while (k < m) {
      k *= 2;
      x = (x * (Poly{2} - trunc(k) * x)).trunc(k);
    }
    return x.trunc(m);
  }

  /*
    g'    mod x^(z/2)
    g=ln(f)
    g'=f'/f=f'*inv(f)
    g=integr(g')
    https://www.luogu.com.cn/problem/P4725
  */
  constexpr Poly log(int m) const { return (deriv() * inv(m)).integr().trunc(m); }
  
  /*
    use Newton iteration
    z(g(x))=ln(g(x))-f(x)
    g(x)=g'(x)*(1-ln(g'(x))+f(x))
    need f(0)=0,so tht g'(mod x^1) = e^f(0)=1
    https://www.luogu.com.cn/problem/P4726
  */
  constexpr Poly exp(int m) const {
    Poly x{1};
    int k = 1;
    while (k < m) {
      k *= 2;
      x = (x * (Poly{1} - x.log(k) + trunc(k))).trunc(k);
    }
    return x.trunc(m);
  }
  /*
    加强版pow，支持f(0)!=0
    https://www.luogu.com.cn/problem/P5273

    在次数不溢出的情况下，可以dft idft实现
  */
  constexpr Poly pow(int k, int m) const {
    if (k == 0) {
      Poly res(m);
      res[0] = 1;
      return res;
    }
    int i = 0;
    while (i < this->size() && (*this)[i] == 0) {
      i++;
    }
    // if all [x^i] are 0 or zero term is too much, return {0,0...}
    if (i == this->size() || 1LL * i * k >= m) {
      return Poly(m);
    }
    Value v = (*this)[i];
    // descend and mul inv(f[0]) make sure f(0) = 1
    auto f = shift(-i) * v.inv();
    return (f.log(m - i * k) * k).exp(m - i * k).shift(i * k) * power(v, k);
  }
  constexpr Poly pow(string s, int m) const {
    if (s == "0") {
      Poly res(m);
      res[0] = 1;
      return res;
    }
    int i = 0;
    while (i < this->size() && (*this)[i] == 0) {
      i++;
    }
    if (i == this->size() || (i && (s.size() > 8 || i * stoll(s) >= m))) {
      return Poly(m);
    }
    ll k1 = 0, k2 = 0;
    for (int i = 0; i < sz(s); i++) {
      k1 = k1 * 10 + (s[i] - '0');
      k2 = k2 * 10 + (s[i] - '0');
      k2 %= (P - 1);  // be careful
      k1 %= P;
    }
    Value v = (*this)[i];
    auto f = shift(-i) * v.inv();
    return (f.log(m - i * k1) * k1).exp(m - i * k1).shift(i * k1) * power(v, k2);
  }
  constexpr Poly sqrt(int m) const {
    Poly x{1};
    int k = 1;
    while (k < m) {
      k *= 2;
      x = (x + (trunc(k) * x.inv(k)).trunc(k)) * CInv<2, P>;
    }
    return x.trunc(m);
  }
  constexpr Poly mulT(Poly b) const {
    if (b.size() == 0) {
      return Poly();
    }
    int n = b.size();
    std::reverse(b.begin(), b.end());
    return ((*this) * b).shift(-(n - 1));
  }
  constexpr std::vector<Value> eval(std::vector<Value> x) const {
    if (this->size() == 0) {
      return std::vector<Value>(x.size(), 0);
    }
    const int n = std::max(x.size(), this->size());
    std::vector<Poly> q(4 * n);
    std::vector<Value> ans(x.size());
    x.resize(n);
    
    // c++20 friendly
    auto build = [&](auto&& self, int p, int l, int r) -> void {
      if (r - l == 1) {
        q[p] = Poly{1, -x[l]};
      } else {
        int m = (l + r) / 2;
        self(self, 2 * p, l, m);      
        self(self, 2 * p + 1, m, r);   
        q[p] = q[2 * p] * q[2 * p + 1];
      }
    };
    build(build, 1, 0, n);
    auto work = [&](auto&& self, int p, int l, int r, const Poly &num) -> void {
      if (r - l == 1) {
        if (l < int(ans.size())) {
          ans[l] = num[0];
        }
      } else {
        int m = (l + r) / 2;
        self(self, 2 * p, l, m, num.mulT(q[2 * p + 1]).resize(m - l));
        self(self, 2 * p + 1, m, r, num.mulT(q[2 * p]).resize(r - m));
      }
    };
    work(work, 1, 0, n, mulT(q[1].inv(n)));
    return ans;
  }
  // constexpr std::vector<Value> eval(std::vector<Value> x) const {
  //   if (this->size() == 0) {
  //     return std::vector<Value>(x.size(), 0);
  //   }
  //   const int n = std::max(x.size(), this->size());
  //   std::vector<Poly> q(4 * n);
  //   std::vector<Value> ans(x.size());
  //   x.resize(n);
  //   std::function<void(int, int, int)> build = [&](int p, int l, int r) {
  //     if (r - l == 1) {
  //       q[p] = Poly{1, -x[l]};
  //     } else {
  //       int m = (l + r) / 2;
  //       build(2 * p, l, m);
  //       build(2 * p + 1, m, r);
  //       q[p] = q[2 * p] * q[2 * p + 1];
  //     }
  //   };
  //   build(1, 0, n);
  //   std::function<void(int, int, int, const Poly &)> work = [&](int p, int l, int r, const Poly &num) {
  //     if (r - l == 1) {
  //       if (l < int(ans.size())) {
  //         ans[l] = num[0];
  //       }
  //     } else {
  //       int m = (l + r) / 2;
  //       work(2 * p, l, m, num.mulT(q[2 * p + 1]).resize(m - l));
  //       work(2 * p + 1, m, r, num.mulT(q[2 * p]).resize(r - m));
  //     }
  //   };
  //   work(1, 0, n, mulT(q[1].inv(n)));
  //   return ans;
  // }
};

constexpr Poly<MOD> Mul(Poly<MOD> a, Poly<MOD> b, int deg) {
  Poly<MOD> res=a*b;
  res.trunc(deg+1);
  return res;    
}
template <int P = MOD>
Poly<P> berlekampMassey(const Poly<P> &s) {
  Poly<P> c;
  Poly<P> oldC;
  int f = -1;
  for (int i = 0; i < s.size(); i++) {
    auto delta = s[i];
    for (int j = 1; j <= c.size(); j++) {
      delta -= c[j - 1] * s[i - j];
    }
    if (delta == 0) {
      continue;
    }
    if (f == -1) {
      c.resize(i + 1);
      f = i;
    } else {
      auto d = oldC;
      d *= -1;
      d.insert(d.begin(), 1);
      MInt<P> df1 = 0;
      for (int j = 1; j <= d.size(); j++) {
        df1 += d[j - 1] * s[f + 1 - j];
      }
      assert(df1 != 0);
      auto coef = delta / df1;
      d *= coef;
      Poly<P> zeros(i - f - 1);
      zeros.insert(zeros.end(), d.begin(), d.end());
      d = zeros;
      auto temp = c;
      c += d;
      if (i - temp.size() > f - oldC.size()) {
        oldC = temp;
        f = i;
      }
    }
  }
  c *= -1;
  c.insert(c.begin(), 1);
  return c;
}
template <int P = MOD>
MInt<P> linearRecurrence(Poly<P> p, Poly<P> q, ll n) {
  int m = q.size() - 1;
  while (n > 0) {
    auto newq = q;
    for (int i = 1; i <= m; i += 2) {
      newq[i] *= -1;
    }
    auto newp = p * newq;
    newq = q * newq;
    for (int i = 0; i < m; i++) {
      p[i] = newp[i * 2 + n % 2];
    }
    for (int i = 0; i <= m; i++) {
      q[i] = newq[i * 2];
    }
    n /= 2;
  }
  return p[0] / q[0];
}
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
  mint C(int n, int m) { return binom(n, m); }
  mint A(int n, int m) { return fac(n) * invfac(n - m); }
  mint Lucas(int x,int y) {
    if(x < y) return 0;
    if(!x) return 1;
    return Lucas(x / MOD,y / MOD) *1ll* binom(x % MOD,y % MOD);
  }
} comb;