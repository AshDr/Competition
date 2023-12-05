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
#include <algorithm>
#include <bits/stdc++.h>
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

const int N = 2e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
#define int long long 
int TT = 1;
ll prex[N],prey[N];
int x[N],y[N];
void solve() {
    int n;
    ll k;
    cin >> n >> k;
    vector<int> xx,yy;
    for(int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
    }
    sort(x + 1, x + 1 + n);
    sort(y + 1, y + 1 + n);

    for(int i = 1; i <= n; i++) {
        prex[i] = prex[i - 1] + x[i];
    }
    for(int i = 1; i <= n; i++) {
        prey[i] = prey[i - 1] + y[i];
    }
    ll l = 0, r = 1e9;
    auto ask = [&](ll pre[], int xy[], int len) {
        ll res = 1e18;
        for(int i = 1; i <= n; i++) {
        	ll sum = 0;
        	int zz = lower_bound(xy + 1, xy + 1 + n, xy[i] + len) - xy;
        	if(zz <= n) sum += pre[n] - pre[zz - 1] - 1ll*(n - zz + 1)*(xy[i] + len);
        	sum += 1ll*i * xy[i] - pre[i];
        	res = min(res, sum);
        }
        for(int i = 1; i <= n; i++) {
        	ll sum = 0;
        	int zz = upper_bound(xy + 1, xy + 1 + n, xy[i] - len) - xy - 1;
        	if(zz) sum += 1ll*(xy[i] - len) * zz - pre[zz];
        	sum += pre[n] - pre[i - 1] - 1ll*(n - i + 1) * xy[i];
        	res = min(res, sum);
        }
        return res;
    };
    auto check = [&](int len) {
        return ask(prex, x, len) + ask(prey, y, len) <= k;
    };
    while(l < r) {
        ll mid = (l + r) >> 1;
        if(check(mid)) {
            r = mid;
        }else l = mid + 1;
    } 
    cout << l << "\n";
    // cout << mn << "\n";
}
signed main() {
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