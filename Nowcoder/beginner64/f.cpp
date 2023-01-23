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

const int N = 5e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const LL MOD = 998244353;
int TT = 1;
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
int n,m;
mint dp[N][4],res[4];
vector<pii> p;
vector<vector<pii>> tmp;
void solve() {
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int x,y;
        cin >> x >> y;
        p.push_back({y,x});
    }
    sort(p.begin(),p.end());
    int pos = 0;
    for(int i = 1; i < m; i++) {
        if(p[i].first != p[pos].first) {
            vector<pii> t;
            for(int j = pos; j < i; j++) {
                t.push_back(p[j]);
            }
            tmp.push_back(t);
            pos = i;
        }
    }
    vector<pii> t;
    for(int i = pos; i < m; i++) t.push_back(p[i]);
    tmp.push_back(t);
    // for(auto vec: tmp) {
    //     cout << vec[0].first <<": ";
    //     for(auto x: vec) {
    //         cout << x.second << " ";  
    //     }
    //     cout << "\n";
    // }

    dp[0][1] = 1;
    vector<bool> vis(4,0);
    for(auto p: tmp[0]) {vis[p.second]=1;}
    // cout << vis << "\n";
    for(int i = 1; i < sz(tmp); i++) {
        int dis = tmp[i][0].first - tmp[i-1][0].first;
        if(vis[1]) {
            dp[i][1] += dp[i-1][1];//up
            dp[i][2] += dp[i-1][1];//down
        }
        else {
            dp[i][1] += dp[i-1][1];
        }

        if(vis[2]) {
            dp[i][1] += dp[i-1][2];//up
            dp[i][3] += dp[i-1][2];//down
        }
        else {
            dp[i][2] += dp[i-1][2];
        }

        if(vis[3]) {
            dp[i][2] += dp[i-1][3];//up
            dp[i][3] += dp[i-1][3];//down
        }
        else {
            dp[i][3] += dp[i-1][3];
        }
        if(dis >= 2) {
            for(auto p: tmp[i-1]) {
                dp[i][p.second] += dp[i-1][p.second];
            }    
        }
        if(i-2>=0 && tmp[i-1][0].first-tmp[i-2][0].first<2){
            for(auto p: tmp[i-2]) {
                dp[i][p.second] += dp[i-2][p.second];
            }            
        }   
        fill(vis.begin(),vis.end(),0);
        for(auto p: tmp[i]) vis[p.second] = 1;
        // cout << vis << "\n";
    }
    m = sz(tmp);
    // cout << dis << "\n";
    if(vis[1]) {
        res[2] += dp[m-1][1];
        res[1] += dp[m-1][1];
        res[1] += dp[m-1][1];
    }
    else {
        res[1] += dp[m-1][1];    
    }

    if(vis[2]) {
        res[1] += dp[m-1][2];
        res[2] += dp[m-1][2];
        res[3] += dp[m-1][2];
    }
    else {
        res[2] += dp[m-1][2];
    }

    if(vis[3]) {
        res[2] += dp[m-1][3];
        res[3] += dp[m-1][3];
        res[3] += dp[m-1][3];
    }
    else {
        res[3] += dp[m-1][3];
    }
    if(m-2>=0 && tmp[m-1][0].first-tmp[m-2][0].first < 2) {
        for(auto p: tmp[m-2]) {
            res[p.second] += dp[m-2][p.second];
        }
    }
    for(int i = 1; i <= 3; i++) cout << res[i] << "\n";
    /*
    dp[i][j] = if((i-1,j+1))dp[i-1][j+1]+if((i-1,j-1))dp[i-1][j-1]+dp[i-1][j]
    
    */
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
    //cin>>TT;
    while(TT--) solve();
    #ifdef ASHDR
    LOG("Time: %dms\n", int ((clock()
            -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
    #endif
    return 0;
}