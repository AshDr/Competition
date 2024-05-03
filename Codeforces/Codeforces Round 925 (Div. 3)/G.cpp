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
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
#include <random>
#define LOG(FMT...) fprintf(stderr, FMT)
#define sz(x) (int)x.size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
using namespace std;
// using namespace __gnu_pbds;
// typedef tree<int,null_type,less<>,rb_tree_tag,tree_order_statistics_node_update> Bst;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef unsigned int ui;
typedef unsigned long long ull;
typedef pair<double,double> pdd;
template <class T>
istream& operator>>(istream& is, vector<T>& v) {
  for (T& x : v)
    is >> x;
  return is;
}
template <class T>
ostream& operator<<(ostream& os, const vector<T>& v) {
  if (!v.empty()) {
    os << v.front();
    for (int i = 1; i < (int)v.size(); ++i)
    os << ' ' << v[i];
  }
  return os;
}
void dbg_out() { cerr << "\b\b )" << endl; }
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T){cerr << H << ", ";dbg_out(T...);}
#define debug(...) cerr << "( " << #__VA_ARGS__ << " ) = ( ", dbg_out(__VA_ARGS__)
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll myRand(ll B) {return (ull)rng()%B;}
ll gcd(ll x, ll y) {return y == 0 ? x : gcd(y, x % y);}
ll qpow(ll base, ll x, ll mod) {
    ll res = 1;
    base %= mod;
    while(x) {
       if(x & 1) res = (res * base) % mod;
       base = (base * base) % mod;
       x >>= 1;
    } 
    return res;
}
ll exgcd(ll a,ll b,ll &x,ll &y) {
    if(b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll d = exgcd(b,a % b,y,x);
    y -= a / b * x;
    return d;
}// (get inv) gcd(a,p) = 1 

ll floor(ll x, ll m) {
    ll r = (x % m + m) % m;
    return (x - r) / m;
}// neg floor (-1, 3) = -1
const int N = 2e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
int TT = 1;
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
      mint t = (ull)rng() % MOD;
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
void solve() {
    int c1,c2,c3,c4;
    cin >> c1 >> c2 >> c3 >> c4;
    auto f = [&](int x, int y) {
    	return comb.binom(x + y - 1, y - 1);
    };
    if(abs(c1 - c2) > 1) {
    	cout << 0 << "\n";
    }else if(c1 == c2) {
    	if(c1 == 0) {
    		if(c3 > 0 && c4 > 0) cout << 0 << "\n";
    		else cout << 1 << "\n";
    	}
    	else cout << f(c3, c1) * f(c4, c2 + 1) + f(c4, c2) * f(c3, c1 + 1) << "\n"; 
    }else {
    	int mx = max(c1, c2);
    	cout << f(c3, mx) * f(c4, mx) << "\n";
    }
}
int main() {
    #ifdef ASHDR
    freopen("data.in","r",stdin);
    freopen("data.out","w",stdout);
    int nol_cl = clock();
    #endif
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout<<fixed<<setprecision(8);
    comb.init(4000000);
    cin>>TT;
    while(TT--) solve();
    #ifdef ASHDR
    LOG("Time: %dms\n", int ((clock()
            -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
    #endif
    return 0;
}