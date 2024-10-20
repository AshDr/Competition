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
#include <cstring>
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
const int N = 2e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
int TT = 1;
map<ull, ll> mp;
void solve() {
  int n;
  cin >> n;
  vector<int> C(n + 1);
  vector<ll> W(n + 1);
  for (int i = 1; i <= n; i++) cin >> C[i];
  for (int i = 1; i <= n; i++) cin >> W[i];
  vector<vector<int>> G(n + 1);
  for (int i = 1; i <= n - 1; i++) {
    int u, v;
    cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  vector<ull> hsh1(n + 1), hsh2(n + 1), sum(n + 1);
  for (int i = 1; i <= n; i++) {
    hsh1[i] = rng();
    sum[i] = sum[i - 1] + hsh1[i];
  }
  for (int i = 1; i <= n; i++) {
    sum[i] += hsh1[i];
  }
  for (int i = 1; i <= n; i++) hsh2[i] = rng();
  vector<ll> ans(n + 1, numeric_limits<ll>::min());
  int mxpart = 1e9, root = 1, S = n;
  vector<int> siz(n + 1), vis(n + 1);
  function<void(int, int, ull, ll)> dfs = [&](int u, int fa, ull hsh, ll val) {
    ull x = sum[C[u]] - hsh + hsh1[C[root]] + hsh2[C[u]];
    if (mp.find(x) != mp.end()) {
      ans[C[u]] = max(ans[C[u]], val + mp[x] - W[root]);
    }
    if (mp.find(hsh + hsh2[C[u]]) == mp.end())
      mp[hsh + hsh2[C[u]]] = val;
    else
      mp[hsh + hsh2[C[u]]] = max(mp[hsh + hsh2[C[u]]], val);
    for (auto v : G[u]) {
      if (v == fa || vis[v]) continue;
      dfs(v, u, hsh + hsh1[C[v]], val + W[v]);
    }
  };

  function<void(int, int)> get_siz = [&](int u, int fa) {
    siz[u] = 1;
    for (auto v : G[u]) {
      if (v == fa || vis[v]) continue;
      get_siz(v, u);
      siz[u] += siz[v];
    }
  };
  function<void(int, int)> find_root = [&](int u, int fa) {
    int mx = 0;
    for (auto v : G[u]) {
      if (vis[v] || v == fa) continue;
      find_root(v, u);
      mx = max(mx, siz[v]);
    }
    mx = max(mx, S - siz[u]);
    if (mx < mxpart) mxpart = mx, root = u;
  };
  function<void(int, int)> work = [&](int u, int par) {
    mxpart = 1e9;
    root = u;
    get_siz(u, 0);
    S = siz[u];
    find_root(u, 0);
    // cout<<u<<" "<<root<<endl;
    vis[root] = 1;
    mp.clear();
    dfs(root, 0, hsh1[C[root]], W[root]);
    if (mp.find(sum[C[root]] + hsh2[C[root]]) != mp.end())
      ans[C[root]] = max(ans[C[root]], mp[sum[C[root]] + hsh2[C[root]]]);
    int curfa = root;
    for (auto v : G[root]) {
      if (!vis[v]) {
        work(v, curfa);
      }
    }
  };
  work(1, 0);
  for (int i = 1; i <= n; i++) {
    cout << (ans[i] == numeric_limits<ll>::min() ? -1 : ans[i]) << " \n"[i == n];
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
  cin >> TT;
  while (TT--) solve();
#ifdef ASHDR
  LOG("Time: %dms\n", int((clock() - nol_cl) / (double)CLOCKS_PER_SEC * 1000));
#endif
  return 0;
}