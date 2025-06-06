using ll = long long;
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
  constexpr MInt pow(long long n) const {
    if (n < 0) {
      return power(*this, -n).inv();
    }
    return power(*this, n);
  }
  constexpr MInt inv() const {
    assert(x != 0);
    return power(*this, getMod() - 2);
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
  constexpr MInt &operator++() {
    x = norm(x + 1);
    return *this;
  }
  constexpr MInt &operator--() {
    x = norm(x - 1);
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
  bool sqrt(MInt &res) const {
    if (P == 2 || x == 0) {
      res = *this;
      return true;
    }
    if (pow(*this, (P - 1) / 2) != 1) return false;
    if (P % 4 == 3) {
      res = pow(*this, (P + 1) / 4);
      return true;
    }
    int pw = (P - 1) / 2;
    int K = 30;
    while ((1 << K) > pw) K--;
    while (true) {
      MInt t = (ull)rng() % P;
      MInt a = 0, b = 0, c = 1;
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
      c *= MInt() - b.inv();
      if (c * c == *this) {
        res = c;
        return true;
      }
    }
    assert(false);
  }
  friend constexpr std::ostream &operator<<(std::ostream &os, const MInt &a) { return os << a.val(); }
  friend constexpr bool operator==(MInt lhs, MInt rhs) { return lhs.val() == rhs.val(); }
  friend constexpr bool operator!=(MInt lhs, MInt rhs) { return lhs.val() != rhs.val(); }
};
template <>
int MInt<0>::Mod = 998244353;

template <int V, int P>
constexpr MInt<P> CInv = MInt<P>(V).inv();

constexpr int MOD = 998244353;
using mint = MInt<MOD>;