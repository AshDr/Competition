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
template <class T> istream &operator>>(istream &is, vector<T> &v) {
  for (T &x : v)
    is >> x;
  return is;
}
template <class T> ostream &operator<<(ostream &os, const vector<T> &v) {
  if (!v.empty()) {
    os << v.front();
    for (int i = 1; i < (int)v.size(); ++i)
      os << ' ' << v[i];
  }
  return os;
}
void dbg_out() { cerr << "\b\b )" << endl; }
template <typename Head, typename... Tail> void dbg_out(Head H, Tail... T) {
  cerr << H << ", ";
  dbg_out(T...);
}
#define debug(...)                                                             \
  cerr << "( " << #__VA_ARGS__ << " ) = ( ", dbg_out(__VA_ARGS__)
mt19937_64 myrand(chrono::steady_clock::now().time_since_epoch().count());
ll myRand(ll B) { return (ull)myrand() % B; }
ll gcd(ll x, ll y) { return y == 0 ? x : gcd(y, x % y); }
ll qpow(ll base, ll x, ll mod) {
  ll res = 1;
  base %= mod;
  while (x) {
    if (x & 1)
      res = (res * base) % mod;
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
} // (get inv) gcd(a,p) = 1

const int N = 2e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
int n, m;
struct Graph {
  vector<int> G[N], res;
  vector<int> store[N];
  int ans;
  int vis[N], scc_num, dfn[N], low[N], stk[N], top, instk[N], belong[N], tot;
  void tarjan(int u) {
    dfn[u] = low[u] = ++tot;
    stk[++top] = u;
    instk[u] = 1;
    for (auto v : G[u]) {
      if (!instk[v]) {
        tarjan(v);
        low[u] = min(low[u], low[v]);
      } else if (instk[u]) {
        low[u] = min(low[u], dfn[v]);
      }
    }
    if (dfn[u] == low[u]) {
      ++scc_num;
      int x;
      do {
        x = stk[top--];
        belong[x] = scc_num;
        instk[x] = 0;
        if (x > n)
          store[scc_num].push_back(x - n);
      } while (x != u);
    }
  }
  void mian() {
    for (int i = 1; i <= n; i++)
      if (!dfn[i])
        tarjan(i);
    for (int i = 1; i <= n; i++)
      if (belong[i] == belong[i + n]) {
        ans = n;
        return;
      }
    for (int i = 1; i <= n; i++) {
      if (!vis[belong[i]]) {
        vis[belong[i]] = vis[belong[i + n]] = 1;
        if (store[belong[i]].size() < store[belong[i + n]].size()) {
          ans += store[belong[i]].size();
          res.insert(res.end(), store[belong[i]].begin(),
                     store[belong[i]].end());
        } else {
          ans += store[belong[i + n]].size();
          res.insert(res.end(), store[belong[i + n]].begin(),
                     store[belong[i + n]].end());
        }
      }
    }
  }
} graphs[2];
void solve() {
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int u, v;
    char ch;
    cin >> u >> v >> ch;
    if (ch == 'R') {
      graphs[0].G[u].push_back(v);
      graphs[0].G[v].push_back(u);
      graphs[0].G[u + n].push_back(v + n);
      graphs[0].G[v + n].push_back(u + n);
      graphs[1].G[u + n].push_back(v);
      graphs[1].G[v].push_back(u + n);
      graphs[1].G[u].push_back(v + n);
      graphs[1].G[v + n].push_back(u);
    } else {
      graphs[0].G[u].push_back(v + n);
      graphs[0].G[v + n].push_back(u);
      graphs[0].G[u + n].push_back(v);
      graphs[0].G[v].push_back(u + n);
      graphs[1].G[u].push_back(v);
      graphs[1].G[v].push_back(u);
      graphs[1].G[u + n].push_back(v + n);
      graphs[1].G[v + n].push_back(u + n);
    }
  }
  graphs[0].mian();
  graphs[1].mian();
  if (min(graphs[0].ans,graphs[1].ans) == n)
    cout << -1 << "\n";
  else {
    int id = graphs[1].ans < graphs[0].ans;
    cout << graphs[id].ans << "\n";
    for (auto x : graphs[id].res)
      cout << x << " ";
    cout << "\n";
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
  while (TT--)
    solve();
#ifdef ASHDR
  LOG("Time: %dms\n", int((clock() - nol_cl) / (double)CLOCKS_PER_SEC * 1000));
#endif
  return 0;
}