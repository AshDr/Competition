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
#include <set>
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
#define pop_count(x) __builtin_popcountll(x)
#define ctz(x) __builtin_ctz(x)
#define clz(x) __builtin_clz(x)
#define ctzl(x) __builtin_ctzll(x)
#define clzl(x) __builtin_clzll(x)
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
namespace namespace_FhqTreap {

template <typename T>
struct Node {
  T key;
  Node *left, *right;
  int size, priority;
  Node() : left(nullptr), right(nullptr) {}
  Node(T key, int pri) : key(key), left(nullptr), right(nullptr), size(1), priority(pri) {}  // init info
  ~Node() {
    if (left) delete left;
    if (right) delete right;
  }
};
template <typename T>
Node<T> *create(T key) {
  Node<T> *root = new Node(key, random());
  return root;
}
template <typename T>
void pushup(Node<T> *root) {
  if (root) {
    root->size = (root->left ? root->left->size : 0) + (root->right ? root->right->size : 0) + 1;
    // merge info, mayeb not merge root->info
  }
}
// split by val, key < val in x, key >= val in y
template <typename T>
void split1(Node<T> *root, T key, Node<T> *&x, Node<T> *&y) {
  if (root == nullptr) {
    x = y = nullptr;
    return;
  }
  if (root->key < key) {
    x = root;
    split1(root->right, key, root->right, y);
  } else {
    y = root;
    split1(root->left, key, x, root->left);
  }
  pushup(root);
}
// split by val, key <= val in x, key > val in y
template <typename T>
void split2(Node<T> *root, T key, Node<T> *&x, Node<T> *&y) {
  if (root == nullptr) {
    x = y = nullptr;
    return;
  }
  if (!(key < root->key)) {
    x = root;
    split2(root->right, key, root->right, y);
  } else {
    y = root;
    split2(root->left, key, x, root->left);
  }
  pushup(root);
}
template <typename T>
Node<T> *merge(Node<T> *x, Node<T> *y) {
  if (x == nullptr) return y;
  if (y == nullptr) return x;
  if (x->priority > y->priority) {
    x->right = merge(x->right, y);
    pushup(x);
    return x;
  } else {
    y->left = merge(x, y->left);
    pushup(y);
    return y;
  }
}
template <typename T>
struct FhqTreap {
 public:
  FhqTreap(int seed = 0) {
    this->seed = seed;
    root = nullptr;
  }

  ~FhqTreap() {
    if (root) delete root;
  }
  Node<T> *root;
  int seed;

  int random() { return seed = int((seed + 3) * 482711ll % 2147483647); }

  void insert(T key) {
    Node<T> *x, *y;
    split1(root, key, x, y);
    root = merge(merge(x, create(key)), y);
  }

  void remove(T key) {
    Node<T> *x, *y, *z;
    split2(root, key, x, z);
    split1(x, key, x, y);
    if (y) {
      y = merge(y->left, y->right);
    }
    root = merge(merge(x, y), z);
  }

  int rank(T key) {
    Node<T> *x, *y;
    int ans;
    split1(root, key, x, y);
    ans = (x ? x->size : 0) + 1;
    root = merge(x, y);
    return ans;
  }

  T at(int r) {
    if (root == nullptr || r > root->size) return T();
    Node<T> *cur = root;
    while (cur) {
      int ls = cur->left ? cur->left->size : 0;
      if (ls + 1 == r) {
        break;
      } else if (ls + 1 > r) {
        cur = cur->left;
      } else {
        r -= ls + 1;
        cur = cur->right;
      }
    }
    return cur->key;
  }

  T previous(T key) {
    Node<T> *x, *y, *cur;
    T ans;
    split1(root, key, x, y);
    cur = x;
    if (cur == nullptr) return std::numeric_limits<T>::min();
    while (cur->right) cur = cur->right;
    ans = cur->key;
    root = merge(x, y);
    return ans;
  }

  T next(T key) {
    Node<T> *x, *y, *cur;
    T ans;
    split2(root, key, x, y);
    cur = y;
    if (cur == nullptr) return std::numeric_limits<T>::max();
    while (cur->left) cur = cur->left;
    ans = cur->key;
    root = merge(x, y);
    return ans;
  }

  int size() { return (root ? root->size : 0); }

  bool find(T key) {
    Node<T> *x, *y, *z;
    split2(root, key, x, z);
    split1(x, key, x, y);
    bool ans;
    if (y)
      ans = true;
    else
      ans = false;
    root = merge(merge(x, y), z);
    return ans;
  }
};
}  // namespace FhqTreap
using namespace namespace_FhqTreap;
void solve() {
  int n;
  cin>>n;
  FhqTreap<int> fhq;
  for(int i=0; i<n; i++) {
    int op;
    cin>>op;
    switch (op) {
      case 1: {
        int x;
        cin>>x;
        fhq.insert(x);
        break;
      }
      case 2:{
        int x;
        cin>>x;
        fhq.remove(x);
        break;
      }
      case 3: {
        int x;
        cin>>x;
        cout<<fhq.rank(x)<<'\n';
        break;
      }
      case 4: {
        int r;
        cin>>r;
        cout<<fhq.at(r)<<'\n';
        break;
      }
      case 5: {
        int x;
        cin>>x;
        cout<<fhq.previous(x)<<'\n';
        break;
      }
      case 6: {
        int x;
        cin>>x;
        cout<<fhq.next(x)<<'\n';
        break;
      }
    }
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