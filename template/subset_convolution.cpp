/*
           ▃▆█▇▄▖
       ▟◤▖　　　  ◥█
   ◢◤ 　  ◢▐　　     ▐▉
 ▗◤　  　   ▂ ▗▖　 ▕ █▎
 ◤　▗▅▖ ◥▄　 ▀▀▀◣　█▊
▐　▕▎  ◥▖◣◤　 　　◢██
█◣　◥▅█▀　     　▐███◤
▐█▙▂　　　      ◢███◤
　◥██◣　　　　 ◢▄◤
　　　▀██▅▇▀▎▇

*/
#include <bits/stdc++.h>
#include <functional>
#include <random>
#define LOG(FMT...) fprintf(stderr, FMT)
#define sz(x) (int)x.size()
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef unsigned int ui;
typedef unsigned long long ull;
typedef pair<double, double> pdd;
template <class T>
istream &operator>>(istream &is, vector<T> &v) {
  for (T &x : v) is >> x;
  return is;
}
template <class T>
ostream &operator<<(ostream &os, const vector<T> &v) {
  if (!v.empty()) {
    os << v.front();
    for (int i = 1; i < (int)v.size(); ++i) os << ' ' << v[i];
  }
  return os;
}
void dbg_out() { cerr << "\b\b )" << endl; }
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
  cerr << H << ", ";
  dbg_out(T...);
}
#define debug(...) cerr << "( " << #__VA_ARGS__ << " ) = ( ", dbg_out(__VA_ARGS__)
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll myRand(ll B) { return (ull)rng() % B; }
ll gcd(ll x, ll y) { return y == 0 ? x : gcd(y, x % y); }
ll qpow(ll base, ll x, ll mod) {
  ll res = 1;
  base %= mod;
  while (x) {
    if (x & 1) res = (res * base) % mod;
    base = (base * base) % mod;
    x >>= 1;
  }
  return res;
}
ll exgcd(ll a, ll b, ll &x, ll &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  ll d = exgcd(b, a % b, y, x);
  y -= a / b * x;
  return d;
}  // (get inv) gcd(a,p) = 1

const int N = 1e6 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 9;
int TT = 1;
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
template <ll P>
struct MLong {
  ll x;
  constexpr MLong() : x{} {}
  constexpr MLong(ll x) : x{norm(x % getMod())} {}

  static ll Mod;
  constexpr static ll getMod() {
    if (P > 0) {
      return P;
    } else {
      return Mod;
    }
  }
  constexpr static void setMod(ll Mod_) { Mod = Mod_; }
  constexpr ll norm(ll x) const {
    if (x < 0) {
      x += getMod();
    }
    if (x >= getMod()) {
      x -= getMod();
    }
    return x;
  }
  constexpr ll val() const { return x; }
  explicit constexpr operator ll() const { return x; }
  constexpr MLong operator-() const {
    MLong res;
    res.x = norm(getMod() - x);
    return res;
  }
  constexpr MLong inv() const {
    assert(x != 0);
    return power(*this, getMod() - 2);
  }
  constexpr MLong &operator*=(MLong rhs) & {
    x = mul(x, rhs.x, getMod());
    return *this;
  }
  constexpr MLong &operator+=(MLong rhs) & {
    x = norm(x + rhs.x);
    return *this;
  }
  constexpr MLong &operator-=(MLong rhs) & {
    x = norm(x - rhs.x);
    return *this;
  }
  constexpr MLong &operator/=(MLong rhs) & { return *this *= rhs.inv(); }
  friend constexpr MLong operator*(MLong lhs, MLong rhs) {
    MLong res = lhs;
    res *= rhs;
    return res;
  }
  friend constexpr MLong operator+(MLong lhs, MLong rhs) {
    MLong res = lhs;
    res += rhs;
    return res;
  }
  friend constexpr MLong operator-(MLong lhs, MLong rhs) {
    MLong res = lhs;
    res -= rhs;
    return res;
  }
  friend constexpr MLong operator/(MLong lhs, MLong rhs) {
    MLong res = lhs;
    res /= rhs;
    return res;
  }
  friend constexpr std::istream &operator>>(std::istream &is, MLong &a) {
    ll v;
    is >> v;
    a = MLong(v);
    return is;
  }
  friend constexpr std::ostream &operator<<(std::ostream &os, const MLong &a) { return os << a.val(); }
  friend constexpr bool operator==(MLong lhs, MLong rhs) { return lhs.val() == rhs.val(); }
  friend constexpr bool operator!=(MLong lhs, MLong rhs) { return lhs.val() != rhs.val(); }
};

template <>
ll MLong<0LL>::Mod = ll(1E18) + 9;

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
int MInt<0>::Mod = 998244353;
template <int V, int P>
constexpr MInt<P> CInv = MInt<P>(V).inv();
constexpr int P = 1e9 + 9;
using mint = MInt<P>;
int LIM, n;
void ORFMT(vector<mint> &a, ll tp) {
  for (int i = 0; i < n; i++)
    for (int j = 0; j < LIM; j++)
      if (j >> i & 1) a[j] += tp * a[j ^ (1 << i)];
}
void solve() {
  cin >> n;
  LIM = (1 << n);
  // 本质是分bit做fmt
  vector<vector<mint>> a(n + 1, vector<mint>(LIM)), b(n + 1, vector<mint>(LIM)), c(n + 1, vector<mint>(LIM));
  for (int i = 0; i < LIM; i++) {
    cin >> a[__builtin_popcount(i)][i];
  }
  for (int i = 0; i < LIM; i++) {
    cin >> b[__builtin_popcount(i)][i];
  }
  for (int i = 0; i <= n; i++) {
    ORFMT(a[i], 1);
    ORFMT(b[i], 1);
  }
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= i; j++) {
      for (int k = 0; k < LIM; k++) {
        c[i][k] += a[j][k] * b[i - j][k];
      }
    }
  }  // get c[i][k]
  // 子集自卷积的时候可以选择用tmp数组接收或者在本身a上做
  // 写法如下
  /*
      for(int i = 0; i <= n; i++) ORFMT(a[i], 1);
      for(int i = n; i >= 0; i--) {
          for(int j = 0; j < LIM; j++) {
              mint x = 0;
              for(int k = 0; k <= i; k++) {
                  x += a[k][j] * a[i - k][j];
              }
              a[i][j] = x;
          }
      }
      //子集自卷积
      for(int i = 0; i <= n; i++) ORFMT(a[i], -1);
  */
  for (int i = 0; i <= n; i++) ORFMT(c[i], -1);
  for (int i = 0; i < LIM; i++) cout << c[__builtin_popcount(i)][i] << " \n"[i == LIM - 1];
}
int main() {
#ifdef ASHDR
  freopen("data.in", "r", stdin);
  freopen("data.out", "w", stdout);
  int nol_cl = clock();
#endif
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  cout << fixed << setprecision(8);
  // cin>>TT;
  while (TT--) solve();
#ifdef ASHDR
  LOG("Time: %dms\n", int((clock() - nol_cl) / (double)CLOCKS_PER_SEC * 1000));
#endif
  return 0;
}