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
#include <limits.h>
#include <random>
#define LOG(FMT...) fprintf(stderr, FMT)
#define sz(x) (int)x.size()
using namespace std;
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
mt19937_64 myrand(chrono::steady_clock::now().time_since_epoch().count());
ll myRand(ll B) {return (ull)myrand()%B;}
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

const int N = 2e6 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
int n, m;
//f[now] = 
void FWT_or(ll *a, int n, int opt) {
    for(int o = 2; o <= n; o <<= 1) { // cur len 
        for(int i = 0,k = o >> 1; i < n; i += o) {
            for(int j = 0; j < k; j++) {
                if(opt == 1) a[i + j + k] = (a[i + j + k] + a[i + j]);
                else a[i + j + k] = (a[i + j + k] - a[i + j]);
            }
        }
    }
}
void FWT_and(ll *a, int n, int opt) {
    for(int o = 2; o <= n; o <<= 1) { // cur len 
        for(int i = 0,k = o >> 1; i < n; i += o) {
            for(int j = 0; j < k; j++) {
                if(opt == 1) a[i + j] = (a[i + j] + a[i + j + k]);
                else a[i + j] = (a[i + j] - a[i + j + k]);
            }
        }
    }
}
void FWT_XOR(ll *a, int n, int opt) {
    for(int o = 2; o <= n; o <<= 1) {
        for(int i = 0, k = o >> 1; i < n; i += o) {
            for(int j = 0; j < k; j++) {
                ll tmp1 = a[i + j], tmp2 = a[i + j + k];
                if(opt == 1) {
                    a[i + j] = tmp1 + tmp2;
                    a[i + j + k] = tmp1 - tmp2;
                }else {
                    a[i + j] = (tmp1 + tmp2) / 2;
                    a[i + j + k] = (tmp1 - tmp2) / 2;
                }
            }
        }
    }
}
char s[N];
ll state[N], f[N], g[N], res[N];
void solve() {
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        cin >> (s + 1);
        for(int j = 1; j <= m; j++) {
            if(s[j] == '1') state[j] |= (1 << (i - 1));
        }
    }
    for(int i = 1; i <= m; i++) f[state[i]]++;
    for(int i = 0; i < (1 << n); i++) {
        g[i] = min(__builtin_popcount(i), n - __builtin_popcount(i));
    }
    FWT_XOR(f, 1 << n, 1);FWT_XOR(g, 1 << n, 1);
    for(int i = 0; i < (1 << n); i++) res[i] = f[i] * g[i];
    FWT_XOR(res, 1 << n, -1);
    ll ans = LLONG_MAX;
    for(int i = 0; i < (1 << n); i++) ans = min(ans, res[i]);
    cout << ans << "\n";
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