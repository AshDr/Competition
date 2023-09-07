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

const int N = 1e3 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
int n;
int get_id(int x) {
  if (x < 0)
    return -x + n;
  return x;
}
int get_rev(int x) {
  if (x > n)
    return x - n;
  else
    return x + n;
}
struct two_sat {
  bitset<N << 1> G[N << 1];
  int val[N << 1], flag, m;
  void dfs(int x) {
    val[x] = 1;
    val[get_rev(x)] = 0;
    for (int i = 1; i <= 2 * n; i++) {
      if (G[x][i] && val[i] == -1) {
        dfs(i);
      }
    }
  }
  void init() {
    for (int i = 1; i <= 2 * n; i++) {
      G[i][i] = 1;
      val[i] = -1;
    }
    for (int i = 1; i <= 2 * n; i++) {
      for (int j = 1; j <= 2 * n; j++) {
        if (G[j][i]) {
          G[j] |= G[i];
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      if (G[i][n + i] && G[n + i][i]) {
        flag = 0;
        return;
      }
    }
    flag = 1;
    for (int i = 1; i <= n; i++) {
      if (val[i] == -1 && val[i + n] == -1 && G[i][i + n]) {
        dfs(i + n);
      }
      if (val[i] == -1 && val[i + n] == -1 && G[i + n][i]) {
        dfs(i);
      }
    }
  }
  void gao() {
    for (int i = 1; i <= 2 * n; i++) {
      if (val[i] == -1) {
        dfs(i);
      }
    }
    for (int i = 1; i <= n; i++)
      cout << val[i] << " \n"[i == n];
  }
} A, B;
void solve() {
  cin >> n >> A.m >> B.m;
  for (int i = 1; i <= A.m; i++) {
    int u, v;
    cin >> u >> v;
    u = get_id(u);
    v = get_id(v);
    A.G[get_rev(u)][v] = 1;
    A.G[get_rev(v)][u] = 1;
  }
  for (int i = 1; i <= B.m; i++) {
    int u, v;
    cin >> u >> v;
    u = get_id(u);
    v = get_id(v);
    B.G[get_rev(u)][v] = 1;
    B.G[get_rev(v)][u] = 1;
  }
  A.init();
  B.init();
  if (A.flag == 0 && B.flag == 0)
    cout << "SIMILAR\n";
  else if (A.flag == 0 || B.flag == 0) {
    if (A.flag)
      A.gao();
    else
      B.gao();
  } else {
    for (int i = 1; i <= 2 * n; i++) {
      if (A.val[i] != -1 && B.val[i] != -1 && A.val[i] != B.val[i]) {
        A.gao();
        return;
      }
      if ((A.val[i] == -1) + (B.val[i] == -1) == 1) {
        if (A.val[i] == -1) {
          if (B.val[i] == 0) {
            A.dfs(i);
          } else {
            A.dfs(get_rev(i));
          }
          A.gao();
          return;
        } else {
          if (A.val[i] == 0) {
            B.dfs(i);
          } else {
            B.dfs(get_rev(i));
          }
          B.gao();
          return;
        }
      }
    }
    for (int i = 1; i <= 2 * n; i++) {
      for (int j = 1; j <= 2 * n; j++) {
        if (A.G[i][j] && B.G[i][j] == 0 && B.val[i] == -1 && B.val[j] == -1) {
          B.dfs(i);
          B.dfs(get_rev(j)); // i = 1 j = 0
          B.gao();
          return;
        }
        if (B.G[i][j] && A.G[i][j] == 0 && A.val[i] == -1 && A.val[j] == -1) {
          A.dfs(i);
          A.dfs(get_rev(j));
          A.gao();
          return;
        }
      }
    }
    cout << "SIMILAR\n";
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
