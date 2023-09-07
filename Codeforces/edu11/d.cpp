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

const int N = 2e3 + 10;
const int M = 2e6 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
int n;
vector<pii> a;
map<ll,int> mp1[M];
map<int,int> mp2,mp3;
void solve() {
    cin >> n;
    vector<int> b, c;
    for(int i = 0; i < n; i++) {
    	int x, y;
    	cin >> x >> y;
    	a.push_back({x, y});
    	b.push_back({y});
    }
    sort(a.begin(),a.end());
    ll ans = 0;
    vector<double> D;
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(a[i].first == a[j].first) {
                ans += mp2[a[j].second - a[i].second], mp2[a[j].second - a[i].second]++;
                continue;
            }
            if(a[i].second == a[j].second) {
                ans += mp3[a[j].first - a[i].first];
                mp3[a[j].first - a[i].first]++;
                continue;
            }
            D.push_back({1.0*(a[j].second - a[i].second) / (a[j].first - a[i].first)});
        }
    }
    sort(D.begin(),D.end());
    int tot = sz(D);
 
    D.erase(unique(D.begin(),D.end()),D.end());
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(a[i].first == a[j].first) continue;
            if(a[i].second == a[j].second) continue;
            double k = 1.0*(a[j].second - a[i].second) / (a[j].first - a[i].first);
            ll len = 1ll*(a[j].second - a[i].second) * (a[j].second - a[i].second) + 1ll*(a[j].first - a[i].first) * (a[j].first - a[i].first);
            int idx = lower_bound(D.begin(),D.end(),k) - D.begin();
            ans += mp1[idx][len];
            mp1[idx][len]++;
        }
    }
    //292 40 50
    assert(ans % 2 == 0);
    cout << ans / 2 << "\n";
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