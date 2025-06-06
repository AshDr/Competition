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
#define LOG(FMT...) fprintf(stderr, FMT)
#define sz(x) (int)x.size()
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef unsigned int ui;
typedef unsigned long long ull;
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

const int N = 2e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
int len, n, m;
int get(int x) { return x / len; }
struct Q {
  int l, r, x, id;
  friend bool operator<(const Q &x, const Q &y) {
    int l1 = get(x.l), l2 = get(y.l);
    if(l1 != l2) return l1 < l2;
    return l1 % 2? x.r < y.r : x.r > y.r;
  }
} qq[N];
int a[N];
int l, r;
ll ans, cnt[N], res[N];
ll get_val(ll x) {
  if (x < 3)
    return 0;
  else
    return x * (x - 1) * (x - 2) / 6;
}
// 优先用这个，否则的话要判一些边界情况
// int l=1, r; 这样的话必须使用先add再dec的写法
// auto dec=[&](int pos) {
// };
// auto add=[&](int pos) {
// };
// auto query=[&](int x, int y) { // 这里有的时候要先加再减, 关于指针移动的正确性，见 https://oi-wiki.org/misc/mo-algo/
//   while (l > x) add(--l);
//   while (r < y) add(++r);
//   while (l < x) dec(l++);
//   while (r > y) dec(r--);
// };
void update(int pos, int sign) {
  int x = a[pos];
  ans -= get_val(cnt[x]);
  cnt[x] += sign;
  ans += get_val(cnt[x]);
}
void query(int x, int y) { // 这里有的时候要先加再减, 关于指针移动的正确性，见 https://oi-wiki.org/misc/mo-algo/
  while (l < x) update(l++, -1);
  while (l > x) update(--l, 1);
  while (r < y) update(++r, 1);
  while (r > y) update(r--, -1);
}
void solve() {
  cin >> n >> m;
  len = sqrt(n);
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 1; i <= m; i++) {
    cin >> q[i].l >> q[i].r;
    q[i].id = i;
  }
  sort(q + 1, q + 1 + m);
  for (int i = 1; i <= m; i++) {
    query(q[i].l, q[i].r);
    res[q[i].id] = ans;
  }
  for (int i = 1; i <= m; i++) cout << res[i] << "\n";
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