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
void solve() {
  int n;
  cin >> n;
  vector<string> s(2 * n);
  cin >> s;
  vector<vector<int>> ans(n, vector<int>(4));
  int mx_len = 2 * n;
  auto gao = [&](int lev, pii b) {
    int cnt = 0;
    int x = b.first, y = b.second;
    while(1) {
      if(x == n - 1 && y == lev) ans[lev][0] = cnt;
      else if(x == lev && y == n) ans[lev][1] = cnt; 
      else if(x == n && y == mx_len - lev - 1) ans[lev][2] = cnt;
      else if(x == mx_len - lev - 1 && y == n - 1) ans[lev][3] = cnt;
      if(x == lev) {
        ++y;
      }else if(x == mx_len - lev - 1) {
        --y;
      }else {
        if(y == lev) {
          --x;
        }else {
          ++x;
        }
      }
      if(y == mx_len - lev) {
        ++x;
        --y;
      }
      else if(x == mx_len - lev) {
        --x;
        --y;        
      }
      else if(y == lev - 1) {
        --x;
        ++y;
      }else if(x == lev - 1) {
        ++x;
        ++y;
      }
      ++cnt;
      if(cnt == 8 * (n - lev) - 4) break;
    }
  };
  for(int i = 0; i < n; i++) {
    int cnt = 0, f = 0;
    if(!(s[mx_len - i - 1][i] == 'X' && s[mx_len - i - 1][i + 1] == 'X'))  {
      for(int j = mx_len - i - 1; j >= i; j--) {
        if(s[j][i] == 'X') {
          gao(i, {j, i});
          f = 1;
        }
      }  
    }
    if(f) continue;
    int x = i, y = i;
    while(1) {
      if(s[x][y] == 'X') {
        gao(i, {x, y});
        break;
      }
      if(x == i) {
        ++y;
      }else if(x == mx_len - i - 1) {
        --y;
      }else {
        if(y == i) {
          --x;
        }else {
          ++x;
        }
      }
      
      if(y == mx_len - i) {
        ++x;
        --y;
      }
      else if(x == mx_len - i) {
        --x;
        --y;        
      }
      else if(y == i - 1) {
        --x;
        ++y;
      }
      ++cnt;
      if(cnt == 8 * (n - i) - 4) break;
    }
  }
  vector<int> sum(4);
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < 4; j++) {
      sum[j] += ans[i][j];
    }
  }
  // cout << sum << "\n";
  cout << *min_element(all(sum)) << "\n";
  //side = 2 * (i + 1)    x = 2 * i + 1
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