#include<bits/stdc++.h>
//#define cerr cout<<"case#:"
#define LOG(FMT...) fprintf(stderr, FMT)
using namespace std;
typedef long long LL;
const int N = 5e6 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const int MOD = 1e9 + 7;
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
LL gcd(LL x, LL y) {return y == 0 ? x : gcd(y, x % y);}
LL qpow(LL base, LL x) {
    LL res = 1;
    while(x) {
        if(x & 1) res *= base;
        base *= base;
        base %= MOD;
        res %= MOD;
        x >>= 1;
    }
    return res;
}
LL qmul(LL a,LL b,LL mod) {
    LL res = 0;
    while(b) {
        if(b & 1) res = (res + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return res;
}//快速乘
void exgcd(LL a, LL b, LL &x, LL &y) {
    if(b == 0) {
        x = 1;y = 0;
        return ;
    }
    exgcd(b,a % b,y,x);
    y -= (a / b) * x;
}//模数无限制
LL getinv(LL x,LL mod) {
    LL x_0,y_0;
    exgcd(x,mod,x_0,y_0);
    return x_0;
}
int deg[N];
int p[N],fa[N];
LL ans = 0;
void treetoprufer() {
	for(int i = 1; i <= n - 1; i++) {
		cin>>fa[i];
		deg[fa[i]]++;
	}
	for(int i = 1,j = 1; i <= n - 2; i++,j++) {
		while(deg[j]) j++;
		p[i] = fa[j];
		while(i <= n - 2 && --deg[p[i]] == 0 && p[i] < j) p[i + 1] = fa[p[i]],++i; 
	}
	for(int i = 1; i <= n - 2; i++)  ans ^= i *1ll* p[i];
	cout<<ans<<'\n';
}
void prufertotree() {
	for(int i = 1; i <= n - 2; i++) {
		cin>>p[i];
		deg[p[i]]++;
	}
	p[n - 1] = n;
	for(int i = 1,j = 1; i <= n - 1; i++,j++) {
		while(deg[j]) ++j;
		fa[j] = p[i];
		while(i <= n - 1 && --deg[p[i]] == 0 && p[i] < j) fa[p[i]] = p[i + 1],++i; 
	} 
	for(int i = 1; i <= n - 1; i++) ans ^= i * 1ll * fa[i]; 
	cout<<ans<<'\n';
}
void solve() {
    cin>>n>>m;
    if(m == 1) treetoprufer();
    else prufertotree();

}
int main() {
    #ifdef ASHDR
    freopen("data.in","r",stdin);
    int nol_cl = clock();
    #endif
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    //cin>>T;
   	T = 1;
    while(T--) solve();
    #ifdef ASHDR
    LOG("Time: %dms\n", int ((clock()
          -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
    #endif
    return 0;
}