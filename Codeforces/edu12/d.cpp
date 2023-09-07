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
#include <set>
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

const int N = 2e6 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
int n, a[N];
int cnt, vis[N], prime[N];
void solve() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 2; i < N; i++) {
    if (!vis[i]) {
      prime[++cnt] = i;
    }
    for (int j = 1; j <= cnt && 1ll*prime[j] * i < N; j++) {
      vis[prime[j] * i] = 1;
      if (i % prime[j] == 0)
        break;
    }
  }
  multiset<int> st;
  vector<pii> b;
  int one_num = 0;
  for (int i = 1; i <= n; i++) {
    int num = 0;
    if(a[i] == 1) {
      ++one_num;
    }
    for (int j = 1; j <= n; j++) {
      if (i == j)
        continue;
      else {
        if (!vis[a[i] + a[j]])
          ++num;
      }
    }
    b.push_back({num, a[i]});
  }
  int ff = 0;
  if(one_num >= 2) {
    ff = 1;
    for(int i = 0; i < one_num; i++) {
      st.insert(1);
    }
  }
  sort(b.begin(), b.end(), greater<pii>());
  for(auto [x, y]: b) {
    if(y == 1 && ff) continue;
    int f = 1;
    for(auto val: st) {
      if(vis[val + y]) {
        f = 0;
        break;
      }
    }
    if(f) st.insert(y);
  }
  cout << sz(st) << "\n";
  for(auto x: st) cout << x << " ";

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
