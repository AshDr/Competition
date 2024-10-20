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
#include <algorithm>
#include <random>
#define LOG(FMT...) fprintf(stderr, FMT)
#define sz(x) (int)x.size()
using namespace std;
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
mt19937_64 myrand(chrono::steady_clock::now().time_since_epoch().count());
ll myRand(ll B) { return (ull)myrand() % B; }
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

const int N = 5e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
int n, m;
vector<pair<int, ll>> G[N];
vector<int> VT[N];
int par[N][21], log_2[N], dfn[N], depth[N], dfn_id;
ll mnweight[N];
void dfs(int u, int fa) {
  dfn[u] = ++dfn_id;
  depth[u] = depth[fa] + 1;
  for (int i = 1; i <= 20; i++) par[u][i] = par[par[u][i - 1]][i - 1];
  for (auto [v, w] : G[u]) {
    if (v == fa) continue;
    par[v][0] = u;
    mnweight[v] = min(mnweight[u], w);
    dfs(v, u);
  }
}
int LCA(int x, int y) {
  if (depth[x] > depth[y]) swap(x, y);
  while (depth[x] < depth[y]) y = par[y][log_2[depth[y] - depth[x]]];
  if (x == y) return x;
  for (int i = 20; i >= 0; i--) {
    if (par[x][i] == par[y][i]) continue;
    x = par[x][i];
    y = par[y][i];
  }
  // cerr <<"! " << x << " " << y << " " << par[x][0] << endl;
  assert(par[x][0] == par[y][0] && (par[x][0] != 0));
  return par[x][0];
}
int stk[N], top;
// 两次排序的做法，更简单. input是点子集
auto build = [&](vector<int> tmp) {
  int len = sz(tmp);
  sort(all(tmp), [&](int x, int y) { return tree.in[x] < tree.in[y]; });
  for (int i = 0; i < len - 1; i++) {  // 这里注意是n-1
    tmp.push_back(tree.lca(tmp[i], tmp[i + 1]));
  }
  tmp.push_back(0);  // 这样每次就从0开始dfd即可
  sort(all(tmp), [&](int x, int y) { return tree.in[x] < tree.in[y]; });
  tmp.erase(unique(all(tmp)), tmp.end());
  for (int i = 0; i < sz(tmp) - 1; i++) G[tree.lca(tmp[i], tmp[i + 1])].push_back(tmp[i + 1]);
};

// 单调栈建法
void build(vector<int> &node) {
  top = 0;
  stk[++top] = 1;
  for (auto x : node) {
    if (x == 1) continue;
    int lca = LCA(stk[top], x);
    if (lca != stk[top]) {
      while (top > 1 && dfn[stk[top - 1]] > dfn[lca]) VT[stk[top - 1]].push_back(stk[top]), --top;
      if (lca != stk[top - 1]) {
        VT[lca].push_back(stk[top]);
        stk[top] = lca;
      } else {
        VT[lca].push_back(stk[top]);
        --top;
      }
    }
    stk[++top] = x;
  }
  for (int i = 1; i < top; i++) VT[stk[i]].push_back(stk[i + 1]);
}
int vis[N];
ll dp[N];
void gao(int u, int fa) {
  ll sum = 0;
  for (auto v : VT[u]) {
    if (v == fa) continue;
    gao(v, u);
    sum += dp[v];
  }
  if (vis[u]) {
    dp[u] = mnweight[u];
  } else {
    dp[u] = min(1ll * mnweight[u], sum);
  }
  VT[u].clear();
}
void solve() {
  cin >> n;
  memset(mnweight, 0x3f, sizeof mnweight);
  fill(dp, dp + 1 + n, 1e18);
  log_2[1] = 0;
  for (int i = 2; i <= n; i++) log_2[i] = log_2[i / 2] + 1;
  for (int i = 1; i <= n - 1; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    G[u].push_back({v, w});
    G[v].push_back({u, w});
  }
  dfs(1, 0);
  cin >> m;
  while (m--) {
    int k;
    cin >> k;
    vector<int> node;
    for (int i = 1; i <= k; i++) {
      int x;
      cin >> x;
      vis[x] = 1;
      node.push_back(x);
    }
    sort(node.begin(), node.end(), [&](int x, int y) { return dfn[x] < dfn[y]; });
    node.erase(unique(node.begin(), node.end()), node.end());
    build(node);
    gao(1, 0);
    cout << dp[1] << "\n";
    for (auto x : node) vis[x] = 0, dp[x] = 1e18;
  }
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