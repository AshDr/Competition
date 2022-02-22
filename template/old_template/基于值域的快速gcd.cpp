#include<bits/stdc++.h>
//#define cerr cout<<"#case:"
#define LOG(FMT...) fprintf(stderr, FMT)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
const int N = 5e3 + 10;
const int M = 1e6 + 10;
const int V = 1e3 + 10; //sqrt(值域)
const int INF = 2147483647;
const LL MOD = 998244353;
int T,n,m;
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
    for (int i = 1; i < v.size(); ++i)
      os << ' ' << v[i];
  }
  return os;
}
void dbg_out() { cerr << "\b\b )" << endl; }
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T){cerr << H << ", ";dbg_out(T...);}
#define debug(...) cerr << "( " << #__VA_ARGS__ << " ) = ( ", dbg_out(__VA_ARGS__)
//LL fac[N],inv[N];
LL gcd(LL x, LL y) {return y == 0 ? x : gcd(y, x % y);}
LL qpow(LL base, LL x) {
  LL res = 1;
  while(x) {
    if(x & 1) res = (res * base) % MOD;
    base = (base * base) % MOD;
    x >>= 1;
  }
  return res;
}
LL MOD_sub(LL x,LL y) {
    return ((x - y) % MOD + MOD) %MOD;
}
LL MOD_add(LL x, LL y) {
    return ((x + y) % MOD + MOD) % MOD;
}
/*
LL binom(int n, int k) {
  if(k > n) return 0;
  return (fac[n] * inv[k] % mod * inv[n - k]) % mod;
}
*/
int a[N],b[N];
int prime[M],fac[M][3];
int not_prime[M],_gcd[V][V];
int cnt;
void init() {
    fac[1][0] = fac[1][1] = fac[1][2] = 1;
    for(int i = 2; i < M; i++) {
        if(!not_prime[i]) {
            prime[++cnt] = i;
            fac[i][0] = 1;
            fac[i][1] = 1;
            fac[i][2] = i;
        }
        for(int j = 1; j <= cnt && prime[j] * i < M; j++) {
            int tmp = i * prime[j];
            not_prime[tmp] = 1;
            fac[tmp][0] = fac[i][0] * prime[j];
            fac[tmp][1] = fac[i][1];
            fac[tmp][2] = fac[i][2];
            if(fac[tmp][0] > fac[tmp][1]) swap(fac[tmp][0],fac[tmp][1]);
            if(fac[tmp][1] > fac[tmp][2]) swap(fac[tmp][1],fac[tmp][2]);
            if(i % prime[j] == 0) break;
        }
    }
    for(int i = 1; i < V; i++) _gcd[i][0] = _gcd[0][i] = i;
    for(int i = 1; i < V; i++) {
        for(int j = 1; j <= i; j++) {
            _gcd[i][j] = _gcd[j][i] = _gcd[i % j][j];
        }
    }
}
LL get_gcd(int x, int y) {
    LL ans = 1;
    for(int i = 0; i < 3; i++) {
        int tmp;
        if(fac[x][i] > V) {
            if(y % fac[x][i] == 0) tmp = fac[x][i];
            else tmp = 1;
        }
        else tmp = _gcd[fac[x][i]][y % fac[x][i]];
        
        y /= tmp;
        ans *= tmp;
        ans %= MOD;
    }
    return ans;
}
void solve() {
    init();
    cin>>n;  
    for(int i = 1; i <= n; i++) cin>>a[i];
    for(int i = 1; i <= n; i++) cin>>b[i];
    for(int i = 1; i <= n; i++) {
        LL res = 0;
        LL t = i;
        for(int j = 1; j <= n; j++) {
            res = MOD_add(res,t * get_gcd(a[i],b[j]) % MOD);
            t = t * i % MOD;
            //debug(res);
        }
        cout<<res<<'\n';
    }
}
int main() {
  #ifdef ASHDR
  freopen("data.in","r",stdin);
  int nol_cl = clock();
  #endif
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  cout<<fixed<<setprecision(8);
  //cin>>T;
  T = 1;
  while(T--) solve();
  #ifdef ASHDR
    LOG("Time: %dms\n", int ((clock()
          -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
  #endif
  return 0;
}