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
#include <bitset>
#include <cassert>
#include <chrono>
#include <cstdio>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
#define LOG(FMT...) fprintf(stderr, FMT)
#define sz(x) (int)x.size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
using namespace std;
// using namespace __gnu_pbds;
// typedef tree<int,null_type,less<>,rb_tree_tag,tree_order_statistics_node_update> Bst;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef unsigned int ui;
typedef unsigned long long ull;
typedef pair<double, double> pdd;
template <class T>
istream &operator>>(istream &is, vector<T> &v) {
  for (T &x : v) is >> x;
  return is;
}
template <class T>
ostream &operator<<(ostream &os, const vector<T> &v) {
  if (!v.empty()) {
    os << v.front();
    for (int i = 1; i < (int)v.size(); ++i) os << ' ' << v[i];
  }
  return os;
}
void dbg_out() { cerr << "\b\b )" << endl; }
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
  cerr << H << ", ";
  dbg_out(T...);
}
#define debug(...) cerr << "( " << #__VA_ARGS__ << " ) = ( ", dbg_out(__VA_ARGS__)
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll myRand(ll B) { return (ull)rng() % B; }
ll gcd(ll x, ll y) { return y == 0 ? x : gcd(y, x % y); }
ll qpow(ll base, ll x, ll mod) {
  ll res = 1;
  base %= mod;
  while (x) {
    if (x & 1) res = (res * base) % mod;
    base = (base * base) % mod;
    x >>= 1;
  }
  return res;
}
ll exgcd(ll a, ll b, ll &x, ll &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  ll d = exgcd(b, a % b, y, x);
  y -= a / b * x;
  return d;
}  // (get inv) gcd(a,p) = 1

ll floor(ll x, ll m) {
  ll r = (x % m + m) % m;
  return (x - r) / m;
}  // neg floor (-1, 3) = -1
static ull randint() { return (rng() * 1ll << 32) ^ rng(); }
struct pair_hash {
  template <class T1, class T2>
  std::size_t operator()(const std::pair<T1, T2> &p) const {
    return std::hash<T1>()(p.first) ^ std::hash<T2>()(p.second);
  }
};
// gp_hash_table
const int N = 2e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
int TT = 1;
// 1_based HLD
//集成有基于边的修改
struct Edge{
    int to;
    int w;
    operator int() const { return to; }
};
 
struct HLD{
    int n;
    vector<int> sz, top, dep, fa, in, out, seq;
    vector<vector<Edge> > g;
    vector<ll> dis;
    int ts;
 
    HLD(const vector<vector<Edge> > &g, int root = 1) : n(int(g.size()) - 1), g(g)  {
        ts = 0;
        sz.resize(n + 1);
        top.resize(n + 1);
        dep.resize(n + 1);
        fa.resize(n + 1);
        in.resize(n + 1);
        out.resize(n + 1);
        seq.resize(n + 1);
        dis.resize(n + 1);
        dep[root] = 0;
        top[root] = root;
        dfs_sz(root);
        dfs_hld(root);
    }
 
    void dfs_sz(int u){
        if (fa[u]){
            for(auto it = g[u].begin(); it != g[u].end(); it++){
                if (*it == fa[u]){
                    g[u].erase(it);
                    break;
                }
            }
        }
        sz[u] = 1;
        for(auto &j : g[u]){
            fa[j] = u;
            dep[j] = dep[u] + 1;
            dis[j] = dis[u] + j.w;
            dfs_sz(j);
            sz[u] += sz[j];
            if (sz[j] > sz[g[u][0]])
                swap(j, g[u][0]);
        }
    }
 
    void dfs_hld(int u){
        in[u] = ++ts;
        seq[in[u]] = u;
        for (auto j : g[u]){
            top[j] = (j == g[u][0] ? top[u] : j);
            dfs_hld(j);
        }
        out[u] = ts;
    }
 
    int lca(int u, int v){
        while (top[u] != top[v]){
            if (dep[top[u]] > dep[top[v]]){
                u = fa[top[u]];
            } 
            else{
                v = fa[top[v]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    }
 
    ll dist(int u, int v){
        return dis[u] + dis[v] - 2 * dis[lca(u, v)];
    }
 
    bool in_subtree(int u, int v){
        return in[v] <= in[u] && in[u] <= out[v];
    }
     
    int jump(int u, int k) {
        if (dep[u] < k){
            return -1;
        }
        int d = dep[u] - k;
        while (dep[top[u]] > d){
            u = fa[top[u]];
        }
        return seq[in[u] - dep[u] + d];
    }
     
    int rooted_lca(int a, int b, int c){
        return lca(a, b) ^ lca(b, c) ^ lca(c, a);
    }
    // Q可以为lambda类型，作为一个数据结构的caller
    template<typename Q>
    void modify_path(int u, int v, const Q &q, bool edge = false){
        while(top[u] != top[v]){
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            q(in[top[u]], in[u]);
            u = fa[top[u]];        
        }
        if (dep[u] > dep[v]) swap(u, v);
        q(in[u] + edge, in[v]);
    }
 
    template<typename Q>
    void modify_subtree(int u, const Q &q){
        q(in[u], out[u]);
    }  
    
    template<typename T, typename Q>
    T query_path(int u, int v, const Q &q, bool edge = false){
        T ret = T();
        while(top[u] != top[v]){
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            ret = q(in[top[u]], in[u]) + ret;
            u = fa[top[u]];
        }
        if (dep[u] > dep[v]) swap(u, v);
        return q(in[u] + edge, in[v]) + ret;
    }
 
    template<typename T, typename Q>
    T query_subtree(int u, const Q &q){
        return q(in[u], out[u]);
    }
 
    template<typename T, typename Q, typename F>
    T query_path_noncommutative(int u, int v, const Q &q, const F &f, bool edge = false){
        T left = T(), right = T();
        while(top[u] != top[v]){
            if (dep[top[u]] < dep[top[v]]) swap(u, v), swap(left, right);
            left = q(in[top[u]], in[u]) + left;
            u = fa[top[u]];
        }
        if (dep[u] > dep[v]) swap(u, v), swap(left, right);
        return f(left, q(in[u] + edge, in[v]) + right);
    }
 
};
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    vector<vector<Edge>> G(n + 1); 
    for(int i = 1; i <= n; i++) {
    	cin >> a[i];
    }
    for(int i = 1; i < n; i++) {
    	int u, v;
    	cin >> u >> v;
    	G[u].push_back({v, 1});
    	G[v].push_back({u, 1});
    }
    HLD hld(G);
    int ans = (m + 2) / 3;
    for(int i = 1; i <= n; i++) {
    	int lca = hld.lca(i, a[i]);
    	int num = (hld.dep[i] + 1) + (hld.dep[a[i]] + 1) - (hld.dep[lca] + 1);
    	int cost = hld.dep[i] + hld.dep[a[i]] + num  + 1;
    	if(cost > m) continue;
    	num += (m - cost) / 3;
    	ans = max(ans, num);	
    }
    cout << min(ans, n) << "\n";
}
int main() {
#ifdef ASHDR
  freopen("data.in", "r", stdin);
  freopen("data.out", "w", stdout);
  int nol_cl = clock();
#endif
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  cout << fixed << setprecision(8);
  // cin>>TT;
  while (TT--) solve();
#ifdef ASHDR
  LOG("Time: %dms\n", int((clock() - nol_cl) / (double)CLOCKS_PER_SEC * 1000));
#endif
  return 0;
}