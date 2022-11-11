#include<bits/stdc++.h>
#define LOG(FMT...) fprintf(stderr, FMT)
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
template<class T>
T qpow(T base, LL x, LL mod) {
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

const int N = 2e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const LL MOD = 1e9 + 7;
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
  friend mint pow(const mint & m, long long n) {
    return m.pow(n);
  }
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
int TT = 1;
void solve() {
	//考虑边的贡献
	int n,k;
    cin >> n >> k;
    vector<mint> pw(n),pre(n);
    mint all = 0,ans = 0,num = 1;
    pw[0] = 1,pre[0] = 1;
    for(int i = 1; i < n; i++) pw[i] = pw[i - 1] * k,pre[i] = pre[i - 1] + pw[i];
    all = accumulate(pw.begin(),pw.end(),mint(0));
    for(int i = 0; i < n - 1; i++) {
    	ans += pw[i + 1] * (all - pre[n - i - 2]) * pre[n - i - 2];
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
    //cin>>TT;
    while(TT--) solve();
    #ifdef ASHDR
    LOG("Time: %dms\n", int ((clock()
            -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
    #endif
    return 0;
}