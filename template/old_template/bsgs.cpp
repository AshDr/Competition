/*
a^x = b  (mod p)
get x
p == prime

m = sqrt(p)
x = i * m - j;

a^{i*m} = b * a^j (mod p)

0~m iterate j and store into hashtable  O(sqrt(p))
then
1~n iterate i calculate all a^{i*m}, if a^{i*m} already in hashtable then i*m-j is a solution



*/

#include <bits/stdc++.h>
// #define cerr cout<<"#case:"
#define LOG(FMT...) fprintf(stderr, FMT)
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
typedef pair<LL, LL> pll;
const int N = 1e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const LL MOD = 1e9 + 7;
int TT, n, m;
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
// LL fac[N],inv[N];
LL gcd(LL x, LL y) { return y == 0 ? x : gcd(y, x % y); }
LL qpow(LL base, LL x, LL mod) {
  LL res = 1;
  base %= mod;
  while (x) {
    if (x & 1) res = (res * base) % mod;
    base = (base * base) % mod;
    x >>= 1;
  }
  return res;
}
LL exgcd(LL a, LL b, LL &x, LL &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  LL d = exgcd(b, a % b, y, x);
  y -= a / b * x;
  return d;
}  // (get inv) gcd(a,p) = 1
// unordered_map<LL,LL> hsh; // warn map 放外面更快?
long long bsgs(long long a, long long b, long long p) {  // bsgs
  if (1 % p == b % p) return 0;
  map<long long, long long> hash;
  hash.clear();  // 建立一个Hash表
  b %= p;
  long long t = sqrt(p) + 1;
  for (register long long i = 0; i < t; ++i) hash[(long long)b * qpow(a, i, p) % p] = i;  // 将每个j对应的值插入Hash表
  a = qpow(a, t, p);
  if (!a) return b == 0 ? 1 : -1;                // 特判
  for (register long long i = 1; i <= t; ++i) {  // 在Hash表中查找是否有i对应的j值
    long long val = qpow(a, i, p);
    int j = hash.find(val) == hash.end() ? -1 : hash[val];
    if (j >= 0 && i * t - j >= 0) return i * t - j;
  }
  return -1;  // 无解返回-1
}
void solve() {
  LL a, b, p;
  while (cin >> a >> p >> b, a | b | p) {
    int ans = bsgs(a, b, p);
    if (ans < 0)
      cout << "No Solution\n";
    else
      cout << ans << '\n';
  }
}
int main() {
#ifdef ASHDR
  freopen("data.in", "r", stdin);
  int nol_cl = clock();
#endif
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  cout << fixed << setprecision(8);
  // cin>>TT;
  TT = 1;
  while (TT--) solve();
#ifdef ASHDR
  LOG("Time: %dms\n", int((clock() - nol_cl) / (double)CLOCKS_PER_SEC * 1000));
#endif
  return 0;
}
