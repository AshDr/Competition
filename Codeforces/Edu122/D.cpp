#include<bits/stdc++.h>
//#define cerr cout<<"#case:"
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
const int N = 2e5 + 10;
const int M = 1e5 + 10;
const int INF = 1e9;
const LL MOD = 1e9 + 7;
int TT = 1;
LL gcd(LL x, LL y) {return y == 0 ? x : gcd(y, x % y);}
LL qpow(LL base, LL x, LL mod = MOD) {
    LL res = 1;
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
int norm(int x) { return x >= MOD ? x - MOD : x; }
void add(int& x, int y) {
  if ((x += y) >= MOD)
    x -= MOD;
}

void sub(int& x, int y) {
  if ((x -= y) < 0)
    x += MOD;
}
#define sz(x) (int)x.size()
void solve() {
    int n,k;
    cin >> n >> k;
    vector<int> b(n),c(n);
    cin >> b >> c;
    vector<vector<int>> p(1001,vector<int>());
    vector<int> dp(1001,INF);
    dp[0] = dp[1] = 0;
    for(int i = 1; i <= 1000; i++) {
        for(int j = 1; j <= i; j++) {
            int t = i + i / j;
            if(t <= 1000) dp[t] = min(dp[t],dp[i] + 1);
        }
    }   
    //cout << *max_element(dp.begin(),dp.end()) << '\n';
    k = min(k,12 * n);
    vector<pii> a(n);
    vector<int> f(k + 1);
    for(int i = 0; i < n; i++) {
        a[i].first = dp[b[i]];
        a[i].second = c[i];
    }    
    for(int i = 0; i < n; i++) {
        for(int j = k; j >= a[i].first; j--) {
            f[j] = max(f[j],f[j - a[i].first] + a[i].second);
        }
    }
    cout << *max_element(f.begin(),f.end()) << '\n';
}
int main() {
    #ifdef ASHDR
    freopen("data.in","r",stdin);
    int nol_cl = clock();
    #endif
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout<<fixed<<setprecision(8);
    cin>>TT;
    while(TT--) solve();
    #ifdef ASHDR
    LOG("Time: %dms\n", int ((clock()
            -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
    #endif
    return 0;
}