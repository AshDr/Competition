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
#include <iostream>
#include <iomanip>
#include <queue>
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
int TT = 1;
int n, a, b;
void solve() {
	cin >> n >> a >> b;
	vector<vector<int> > G(n + 1, vector<int>());
	vector<int> vis(n + 1),dep(n + 1);
    for(int i = 0; i < n; i++) {
		int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
	}
    if(a == b) {
        cout << "NO\n";
        return ;
    }
    int pt = 0,f = 0;
    function<void(int, int)> dfs = [&](int u, int pre) {
        vis[u] = 1; 
        for(auto v: G[u]) {
            if(v != pre) {
                if(vis[v] && !f) {
                    pt = v;
                    f = 1;
                    return ;
                }else if(vis[v]) continue;
                else {
                    dep[v] = dep[u] + 1;
                    dfs(v, u);
                }
            }
        }
    };
    dfs(b, 0);
    // cout << pt << "\n";
    // return ;
    queue<pii> q;
    q.push({a,0});
    fill(vis.begin(), vis.end(), 0);
    vis[a] = 1;
    int res = 0;
    while(!q.empty()) {
        auto [u, d] = q.front();q.pop();
        if(u == pt) {
            res = d;
            break;
        }
        for(auto v: G[u]) {
            if(vis[v]) continue;
            else {
                vis[v] = 1;
                q.push({v, d + 1});
            }
        }
    }
    // cout << pt << " " << res << "\n";
    if(res <= dep[pt]) {
        cout << "NO\n";
    }else {
        cout << "YES\n";
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
    cin>>TT;
    while(TT--) solve();
    #ifdef ASHDR
    LOG("Time: %dms\n", int ((clock()
            -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
    #endif
    return 0;
}