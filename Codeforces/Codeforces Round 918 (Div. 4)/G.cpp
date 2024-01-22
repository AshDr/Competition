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
#include <queue>
#include <random>
#define LOG(FMT...) fprintf(stderr, FMT)
#define sz(x) (int)x.size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
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
const ll MOD = 1e9 + 7;
int TT = 1;
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    vector<vector<pii>> G(n);
    for(int i = 0; i < m; i++) {
    	int u, v, w;
    	cin >> u >> v >>w;
    	--u;--v;
    	G[u].push_back({v, w});
    	G[v].push_back({u, w});
    }
    cin >> a;
    vector<vector<ll>> dis0(n, vector<ll>(n, 1e9));
    auto dijkstra = [&](int st)->void {
    	vector<int> vis(n);
    	priority_queue<pii,vector<pii>, greater<pii>> heap;
    	dis0[st][st] = 0;
    	heap.push({0 ,st});
    	while(!heap.empty()) {
    		auto [d, u] = heap.top();heap.pop();
    		if(vis[u]) continue;
    		vis[u] = 1;
    		for(auto [v, w]: G[u]) {
    			if(dis0[st][v] > dis0[st][u] + w) {
    				dis0[st][v] = dis0[st][u] + w;
    				heap.push({dis0[st][v], v});
    			}
    		}
    	}
    };
    for(int i = 0; i < n; i++) {
    	dijkstra(i);
    }
    priority_queue<pair<ll,int>,vector<pair<ll,int>>, greater<pair<ll,int>>> heap;
    heap.push({0, 0});
    vector<ll> dis(n,1e18);
    vector<int> vis(n);
    dis[0] = 0;
    while(!heap.empty()) {
    	auto [d, u] = heap.top();heap.pop();
    	if(vis[u]) continue;
    	vis[u] = 1;
    	for(int i = 0; i < n; i++) {
    		if(!vis[i]) {
    			if(dis[u] + dis0[u][i] * a[u] < dis[i]) {
    				dis[i] = dis[u] + dis0[u][i] * a[u];
    				heap.push({dis[i], i});
    			}
    		}
    	}
    }
    cout << dis[n - 1] << "\n";
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