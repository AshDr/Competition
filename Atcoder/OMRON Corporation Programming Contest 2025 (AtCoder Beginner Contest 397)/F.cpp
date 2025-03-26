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
#include <cstring>
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
#include <set>
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
// [1, n]
// init处易错
int lg(int x) { return static_cast<int>(std::log2(x)); }
template <class Info, class Tag>
struct LazySegmentTree {
  int n;
  vector<Info> info;
  vector<Tag> tag;

  LazySegmentTree() {}

  LazySegmentTree(int n, Info _init = Info()) { init(vector<Info>(n, _init)); }

  LazySegmentTree(const vector<Info> &_init) { init(_init); }

  void init(const vector<Info> &_init) {
    n = (int)_init.size() - 1;
    info.assign((n << 2) + 1, Info());
    tag.assign((n << 2) + 1, Tag());
    function<void(int, int, int)> build = [&](int p, int l, int r) {
      if (l == r) {
        info[p] = _init[l];  // init 1~n
        return;
      }
      int m = (l + r) / 2;
      build(2 * p, l, m);
      build(2 * p + 1, m + 1, r);
      pull(p);
    };
    build(1, 1, n);
  }

  void pull(int p) { info[p] = info[2 * p] + info[2 * p + 1]; }

  void apply(int l, int r, int p, const Tag &v) {
    info[p].apply(v);  // may be need l and r for length
    tag[p].apply(v);
    // ::apply(info[p], tag[p], v);
  }

  void push(int l, int r, int p) {
    int mid = (l + r) >> 1;
    apply(l, mid, 2 * p, tag[p]);
    apply(mid + 1, r, 2 * p + 1, tag[p]);
    tag[p] = Tag();
  }

  void modify(int p, int l, int r, int x, const Info &v) {
    if (l == r) {
      info[p] = v;
      return;
    }
    int m = (l + r) / 2;
    push(l, r, p);
    if (x <= m) {
      modify(2 * p, l, m, x, v);
    } else {
      modify(2 * p + 1, m + 1, r, x, v);
    }
    pull(p);
  }

  void modify(int p, const Info &v) { modify(1, 1, n, p, v); }

  Info query(int p, int l, int r, int x, int y) {
    if (l > y || r < x) {
      return Info();
    }
    if (l >= x && r <= y) {
      return info[p];
    }
    int m = (l + r) / 2;
    push(l, r, p);
    return query(2 * p, l, m, x, y) + query(2 * p + 1, m + 1, r, x, y);
  }

  Info query(int l, int r) { return query(1, 1, n, l, r); }

  void modify(int p, int l, int r, int x, int y, const Tag &v) {
    if (l > y || r < x) {
      return;
    }
    if (l >= x && r <= y) {
      apply(l, r, p, v);
      return;
    }
    int m = (l + r) / 2;
    push(l, r, p);
    modify(2 * p, l, m, x, y, v);
    modify(2 * p + 1, m + 1, r, x, y, v);
    pull(p);
  }

  void modify(int l, int r, const Tag &v) { return modify(1, 1, n, l, r, v); }
  template <class F>
  int findFirst(int p, int l, int r, int x, int y, F pred) {
    if (l > y || r < x || !pred(info[p])) {
      return -1;
    }
    if (l == r) {
      return l;
    }
    int m = (l + r) / 2;
    push(l, r, p);
    int res = findFirst(2 * p, l, m, x, y, pred);
    if (res == -1) {
      res = findFirst(2 * p + 1, m + 1, r, x, y, pred);
    }
    return res;
  }
  template <class F>
  int findFirst(int l, int r, F pred) {
    return findFirst(1, 1, n, l, r, pred);
  }
  template <class F>
  int findLast(int p, int l, int r, int x, int y, F pred) {
    if (l > y || r < x || !pred(info[p])) {
      return -1;
    }
    if (l == r) {
      return l;
    }
    int m = (l + r) / 2;
    push(l, r, p);
    int res = findLast(2 * p + 1, m + 1, r, x, y, pred);
    if (res == -1) {
      res = findLast(2 * p, l, m, x, y, pred);
    }
    return res;
  }
  template <class F>
  int findLast(int l, int r, F pred) {
    return findLast(1, 1, n, l, r, pred);
  }
};

struct Tag {
  // define tag maybe need contructor to determine init val
  int val;
  void apply(const Tag &t) & {
    // add tag to tag
    // determine if legal pushdown
    val += t.val;
  }
};

struct Info {
  // define info maybe need contructor to determine init val
  int mx;
  void apply(const Tag &t) & {
    // add tag to info
    // determine if legal pushdown
    mx += t.val;
  }
};
Info operator+(const Info &a, const Info &b) {
  Info c;
  // merge info
  c.mx = max(a.mx, b.mx);
  return c;
}
void solve() {
  int n;
  cin >> n;
  vector<int> a(n + 1),last(n + 1),sufsum(n + 1),presum(n + 1),vis(n + 1);
  for(int i = 1; i <= n; i++) {
    cin >> a[i];
    presum[i] = presum[i - 1] + (vis[a[i]] == 0);
    vis[a[i]] = 1;
  }
  if(n == 3) {
    cout << 3 << "\n";
    return ;
  }
  LazySegmentTree<Info, Tag> seg(n + 1);
  fill(all(vis),0);
  sufsum[n] = 1;
  vis[a[n]] = 1;
  for(int i = n - 1; i >= 1; i--) {
    sufsum[i] = sufsum[i + 1] + (vis[a[i]] == 0);
    vis[a[i]] = 1;
  }

  int ans = 0;
  vector<int> dp(n + 1);
  for(int i = 1; i <= n - 1; i++) {
    seg.modify(last[a[i]] == 0 ? 1 : last[a[i]], i - 1, {1});
    dp[i] = seg.query(1, i).mx;
    seg.modify(i, {presum[i]});
    // cout << i << " " << seg.query(2, i).mx << " " << sufsum[i + 1] << "?\n";
    ans = max(ans, dp[i] + sufsum[i + 1]);    
    last[a[i]] = i;
  }
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