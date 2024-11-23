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
#define LOG(FMT...) fprintf(stderr, FMT)
#define sz(x) (int)x.size()
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
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
mt19937 myrand(chrono::steady_clock::now().time_since_epoch().count());
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

const int N = 3e6 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
int n, stk[N], ls[N], rs[N];
ll pre[N], a[N], b[N], mx[N], mn[N];
ll ans = LONG_LONG_MIN;
void build_cartesian() {
  for (int i = 1, pos = 0, tp = 0; i <= n; i++) {
    pos = tp;
    while (pos && a[stk[pos]] > a[i]) --pos;
    if (pos) rs[stk[pos]] = i;
    if (pos < tp) ls[i] = stk[pos + 1];
    stk[tp = ++pos] = i;
  }
}
void dfs(int u, int l, int r) {
  mx[u] = mn[u] = pre[u];
  ll pre_mx = pre[l - 1], pre_mn = pre[l - 1], suf_mx = pre[u], suf_mn = pre[u];
  if (ls[u]) {
    dfs(ls[u], l, u - 1);
    mn[u] = min(mn[u], mn[ls[u]]);
    mx[u] = max(mx[u], mx[ls[u]]);
    pre_mx = max(pre_mx, mx[ls[u]]);
    pre_mn = min(pre_mn, mn[ls[u]]);
  }
  if (rs[u]) {
    dfs(rs[u], u + 1, r);
    mn[u] = min(mn[u], mn[rs[u]]);
    mx[u] = max(mx[u], mx[rs[u]]);
    suf_mx = max(suf_mx, mx[rs[u]]);
    suf_mn = min(suf_mn, mn[rs[u]]);
  }
  if (a[u] > 0)
    ans = max(ans, 1ll * a[u] * (suf_mx - pre_mn));
  else
    ans = max(ans, 1ll * a[u] * (suf_mn - pre_mx));
}
void solve() {
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 1; i <= n; i++) cin >> b[i];
  for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] + b[i];
  build_cartesian();
  dfs(stk[1], 1, n);
  cout << ans << "\n";
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