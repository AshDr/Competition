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
const ll MOD = 1e9 + 7;
int TT = 1;

struct Edge{
    int to;
    int id;
    operator int() const { return to; }
};

struct LowLink{
    int n;
    vector<vector<Edge> > g;
    vector<int> in, out, low;
    int ts;
    set<int> bridge;
    // map<int, int> bridge;

    LowLink(const vector<vector<Edge> > &g) : n(int(g.size()) - 1), g(g) {
        ts = 0;
        in.assign(n + 1, 0);
        out.assign(n + 1, 0);
        low.assign(n + 1, 0);
        for(int i = 1; i <= n; i++){
            if (in[i] == 0){
                tarjan(i, -1);
            }
        }
        
        id.assign(n + 1, 0);
        cnt = 0;
        for(int i = 1; i <= n; i++){
            if (id[i] == 0){
                dfs(i, -1);
            }
        }
        group.resize(cnt + 1);;
        for(int i = 1; i <= n; i++){
            group[id[i]].push_back(i);
        }
    }

    void tarjan(int u, int from){
        in[u] = low[u] = ++ts;
        for(auto j : g[u]){
            if (!in[j]){
                tarjan(j, j.id);
                low[u] = min(low[u], low[j]);
                if (low[j] > in[u]){
                    bridge.insert(j.id);
                }
            }
            else if (j.id != from) low[u] = min(low[u], in[j]);
        }
        out[u] = ts;
    }

    int cnt;
    vector<vector<int> > group;
    vector<int> id;

    void dfs(int u, int fa){
        if (fa != -1 && low[u] <= in[fa]){
            id[u] = id[fa];
        }
        else{
            id[u] = ++cnt;
        }
        for(auto j : g[u]){
            if (id[j] == 0){
                dfs(j, u);
            }
        }
    }

};
void solve() {
  	int n, m;
  	cin >> n >> m;
  	vector<vector<Edge>> g(n + 1);
  	vector<array<int,3>> edges(m);
  	for(int i = 0; i < m; i++) {
  		int u, v, w;
  		cin >> u >> v >> w;
  		edges[i] = {u, v, w};
  		g[u].push_back({v, i});
  		g[v].push_back({u, i});
  	}
  	auto bridge = LowLink(g).bridge;
  	int idx = -1;
  	for(int i = 0; i < m; i++) {
  		if(bridge.count(i)) continue;
  		if(idx == -1 || edges[idx][2] > edges[i][2]) {
  			idx = i;
  		}
  	}
  	int st = edges[idx][0], ed = edges[idx][1], w = edges[idx][2];
  	vector<int> res,vis(n+1);
  	vector<int> stk;
  	auto dfs = [&](auto self, int u)->void {
  		vis[u] = 1;
  		stk.push_back(u);
  		if(u == ed) {
  			res = stk;
  			return ;
  		}
  		for(auto [v, id]: g[u]) {
  			if(id == idx) continue;
  			if(vis[v]) continue;
  			if(bridge.count(id)) continue;
  			self(self, v);
  		}
  		stk.pop_back();
  	};
  	dfs(dfs, st);
  	cout << w << " " << sz(res) << "\n";
  	cout << res << "\n";
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