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
#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <string>
#include <queue>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <bitset>
#include <chrono>
#include <random>
#include <iomanip>
#include <random>
#include <cassert>
#include <cstring>
#include <set>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
#define LOG(FMT...) fprintf(stderr, FMT)
#define sz(x) (int)x.size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
#define pop_count(x) __builtin_popcountll(x)
#define ctz(x) __builtin_ctz(x)
#define clz(x) __builtin_clz(x)
#define ctzl(x) __builtin_ctzll(x)
#define clzl(x) __builtin_clzll(x)
using namespace std;
// using namespace __gnu_pbds;
// typedef tree<int,null_type,less<>,rb_tree_tag,tree_order_statistics_node_update> Bst;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef unsigned int ui;
typedef unsigned long long ull;
typedef pair<double,double> pdd;
template <class T>
istream& operator>>(istream& is, vector<T>& v) {
  for (T& x : v)
    is >> x;
  return is;
}
template <class T>
ostream& operator<<(ostream& os, const vector<T>& v) {
  if (!v.empty()) {
    os << v.front();
    for (int i = 1; i < (int)v.size(); ++i)
    os << ' ' << v[i];
  }
  return os;
}
void dbg_out() { cerr << "\b\b )" << endl; }
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T){cerr << H << ", ";dbg_out(T...);}
#define debug(...) cerr << "( " << #__VA_ARGS__ << " ) = ( ", dbg_out(__VA_ARGS__)
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll myRand(ll B) {return (ull)rng()%B;}
ll gcd(ll x, ll y) {return y == 0 ? x : gcd(y, x % y);}
ll qpow(ll base, ll x, ll mod) {
  ll res = 1;
  base %= mod;
  while(x) {
     if(x & 1) res = (res * base) % mod;
     base = (base * base) % mod;
     x >>= 1;
  } 
  return res;
}
ll exgcd(ll a,ll b,ll &x,ll &y) {
  if(b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  ll d = exgcd(b,a % b,y,x);
  y -= a / b * x;
  return d;
}// (get inv) gcd(a,p) = 1 

ll floor(ll x, ll m) {
  ll r = (x % m + m) % m;
  return (x - r) / m;
}// neg floor (-1, 3) = -1
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
struct Q{
  int op;
  int u,v;
};
struct DSU {
  std::vector<int> siz;
  std::vector<int> f;
  std::vector<std::array<int, 2>> his;

  DSU(int n) : siz(n + 1, 1), f(n + 1) { std::iota(f.begin(), f.end(), 0); }

  int find(int x) {
    while (f[x] != x) {
      x = f[x];
    }
    return x;
  }

  bool merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) {
      return false;
    }
    if (siz[x] < siz[y]) {
      std::swap(x, y);
    }
    his.push_back({x, y});
    siz[x] += siz[y];
    f[y] = x;
    return true;
  }

  int time() { return his.size(); }
  // 回滚到时刻tm
  void revert(int tm) {
    while (his.size() > tm) {
      auto [x, y] = his.back();
      his.pop_back();
      f[y] = y;
      siz[x] -= siz[y];
    }
  }

  void revert_cnt(int cnt) {
    assert(cnt<=his.size());
    while (cnt) {
      auto [x, y] = his.back();
      his.pop_back();
      f[y] = y;
      siz[x] -= siz[y];
      --cnt;
    }
  }
};
void solve() {
  int n;
  cin>>n;
  auto get_id=[&](int r, int c) {
    return (r-1) * n + c;
  };
  set<pii> st;
  map<pii,int> mp;
  string op;
  int tot=0;
  vector<Q> qs;
  qs.push_back({0, 0, 0}); // dummy
  while(true) {
    cin>>op;
    if(op=="Exit") break;
    ++tot;
    int r1,c1,r2,c2;
    cin>>r1>>c1>>r2>>c2;
    if(op=="Ask") {
      qs.push_back({0, get_id(r1, c1), get_id(r2, c2)});
    }else if(op=="Open") {
      int u=get_id(r1, c1),v=get_id(r2, c2);
      if(u>v) swap(u,v);
      qs.push_back({1,u,v});
    }else {
      int u=get_id(r1, c1),v=get_id(r2, c2);
      if(u>v) swap(u,v);
      qs.push_back({2,u,v});
    }
  }
  vector seg((tot+1)<<2, vector<Q>());
  auto ins=[&](auto&& self, int o, int L, int R, int l, int r, Q node) {
    if(l <= L && R <= r) {
      seg[o].push_back(node);
      return;
    }
    int mid = (L + R) >> 1;
    if(l <= mid) self(self, o<<1, L, mid, l, r, node);
    if(r > mid) self(self, o<<1|1, mid+1, R, l, r, node);
  };
  for(int i=1; i<=tot; i++) {
    if(qs[i].op==0) {
      ins(ins, 1, 1, tot, i, i, qs[i]);
    }else if(qs[i].op==1) {
      st.insert({qs[i].u, qs[i].v});
      mp[{qs[i].u, qs[i].v}] = i;
    }else {
      assert(st.count({qs[i].u, qs[i].v}));
      st.erase({qs[i].u, qs[i].v});
      ins(ins, 1, 1, tot, mp[{qs[i].u, qs[i].v}], i-1, qs[i]);
    }
  }
  for(auto [u, v]: st) {
    ins(ins, 1, 1, tot, mp[{u, v}], tot, {1, u, v});
  }
  DSU dsu(2*n+1);
  auto dfs=[&](auto&& self, int o, int L, int R)->void {
    int cnt=0;
    for(auto q: seg[o]) {
      if(q.op!=0) {
        if(dsu.merge(q.u, q.v)) {
          ++cnt;
        }
      }
    }
    if(L == R) {
      for(auto q: seg[o]) {
        if(q.op==0) {
          int u = dsu.find(q.u), v = dsu.find(q.v);
          cout << (u == v ? "Y" : "N") << '\n';
        }
      }
    }else {
      int mid = (L + R) >> 1;
      self(self, o<<1, L, mid);
      self(self, o<<1|1, mid+1, R);
    }
    dsu.revert_cnt(cnt);
  };
  dfs(dfs, 1, 1, tot);
}
int main() {
  #ifdef ASHDR
  freopen("data.in","r",stdin);
  freopen("data.out","w",stdout);
  int nol_cl = clock();
  #endif
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  cout<<fixed<<setprecision(8);
  //cin>>TT;
  while(TT--) solve();
  #ifdef ASHDR
  LOG("Time: %dms\n", int ((clock()
          -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
  #endif
  return 0;
}