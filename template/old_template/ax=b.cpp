#include<bits/stdc++.h>
//#define cerr cout<<"#case:"
#define LOG(FMT...) fprintf(stderr, FMT)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
const int N = 1e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const LL MOD = 1e9 + 7;
int TT,n,m;
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
mt19937 myrand(chrono::steady_clock::now().time_since_epoch().count());
//LL fac[N],inv[N];
LL gcd(LL x, LL y) {return y == 0 ? x : gcd(y, x % y);}
LL qpow(LL base, LL x, LL mod = MOD) {
    LL res = 1;
    while(x) {
       if(x & 1) res = (res * base) % mod;
       base = (base * base) % mod;
       x >>= 1;
    } 
    return res;
}
LL exgcd(LL a,LL b,LL &x,LL &y) {
    if(b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    LL d = exgcd(b,a % b,y,x);
    y -= a / b * x;
    return d;
}// (get inv) gcd(a,p) = 1 
const double eps = 1e-8;
LL a[1010][1010];
int flag;
void Gauss() {
  for(int i = 1; i <= n; i++) {
    int pos = i;
    for(int j = i + 1; j <= n; j++) if(abs(a[j][i]) > abs(a[pos][i])) pos = j;
    if(i != pos) swap(a[i],a[pos]);
    if(a[i][i] == 0) {
      flag = 1;
      return ;
    }
    LL inv = qpow(a[i][i],MOD - 2);
    for(int j = 1; j <= n; j++) {
      if(i == j) continue;
      LL tmp = a[j][i] * inv % MOD;
      for(int k = i; k <= 2 * n; k++) {
        a[j][k] = ((a[j][k] - tmp * a[i][k]) % MOD + MOD) % MOD;
      }
    }
    for(int j = 1; j <= 2 * n; j++) a[i][j] = (a[i][j] * inv) % MOD; 
  }
}
#define endl '\n'
void solve() {
  cin>>n;
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= n; j++) {
      cin>>a[i][j];
    }
      a[i][i + n] = 1;
  }
  Gauss();
  if(!flag) {
    for(int i = 1; i <= n; i++) {
      for(int j = n + 1; j <= 2 * n; j++) {
        cout<<a[i][j]<<' ';
      }
      cout<<endl;
    }
  }
  else cout<<"No Solution"<<endl;
}
int main() {
    #ifdef ASHDR
    freopen("data.in","r",stdin);
    int nol_cl = clock();
    #endif
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout<<fixed<<setprecision(8);
    //cin>>TT;
    TT = 1;
    while(TT--) solve();
    #ifdef ASHDR
    LOG("Time: %dms\n", int ((clock()
            -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
    #endif
    return 0;
}