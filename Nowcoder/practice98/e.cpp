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
#define LOG(FMT...) fprintf(stderr, FMT)
#define sz(x) (int)x.size()
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
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
mt19937 myrand(chrono::steady_clock::now().time_since_epoch().count());
LL gcd(LL x, LL y) {return y == 0 ? x : gcd(y, x % y);}
LL qpow(LL base, LL x, LL mod) {
    LL res = 1;
    base %= mod;
    while(x) {
       if(x & 1) res = (res * base) % mod;
       base = (base * base) % mod;
       x >>= 1;
    } 
    return res;
}
LL exgcd(LL a,LL b,LL &x,LL &y) {
    if(b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    LL d = exgcd(b,a % b,y,x);
    y -= a / b * x;
    return d;
}// (get inv) gcd(a,p) = 1 

const int N = 1e6 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const LL MOD = 998244353;
int TT = 1;
int a[N];
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
mint fac[N],invf[N];
void init(int n) {
    fac[0] = 1;
    for(int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i;
    invf[n] = inv(fac[n]);
    invf[0] = invf[1] = 1;
    for(int i = n - 1; i >= 2; i--) invf[i] = invf[i + 1] * (i + 1); 
}
mint binom(int x, int y) {
    if(y > x) return 0;
    return fac[x] * invf[x - y] * invf[y];
}
template <typename T>
struct Fenwick {
    const int n;
    std::vector<T> a;
    Fenwick(int n) : n(n), a(n) {}
    void add(int x, T v) {
        for (int i = x; i <= n; i += i & -i) {
            a[i] += v;
        }
    }
    T sum(int x) {
        T ans = 0;
        for (int i = x; i > 0; i -= i & -i) {
            ans += a[i];
        }
        return ans;
    }
    T rangeSum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};
void solve() {
    int n,k;
    cin >> n >> k;
    vector<int> b;
    for(int i = 1; i <= n; i++) {
    	cin >> a[i];
    	b.push_back(a[i]);
    }
    sort(b.begin(),b.end());
    b.erase(unique(b.begin(),b.end()),b.end());
    mint ans = 0;
    Fenwick<mint> c(n + 1);
    for(int i = 1; i <= n; i++) {
    	int pos = lower_bound(b.begin(),b.end(),a[i]) - b.begin() + 1;
    	ans += ((c.sum(n) - c.sum(pos)) * binom(n - i + k,k));
    	c.add(pos,binom(i + k - 1,k));
    }
    cout << ans << '\n';
}
int main() {
    #ifdef ASHDR
    freopen("data.in","r",stdin);
    int nol_cl = clock();
    #endif
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout<<fixed<<setprecision(8);
    init(N);
    cin>>TT;
    while(TT--) solve();
    #ifdef ASHDR
    LOG("Time: %dms\n", int ((clock()
            -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
    #endif
    return 0;
}