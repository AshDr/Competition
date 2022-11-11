#include<bits/stdc++.h>
//#define cerr cout<<"#case:"
#define LOG(FMT...) fprintf(stderr, FMT)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
const int NN = 2e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const LL MOD = 998244353;
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
unordered_map<LL,LL> hsh; // warn map 放外面更快?
int bsgs(LL a,LL b,LL p) {
    a%=p;b%=p;
    if(1 % p == b % p) return 0;
    int k = sqrt(p) + 1;
    hsh.clear();
    LL tmp = b % p;
    for(int i = 0; i < k; i++) {
        hsh[tmp] = i;
        tmp = (tmp * a) % p;
    }
    LL ak = qpow(a,k,p);
    tmp = ak;
    for(int i = 1; i <= k; i++) {
        if(hsh.count(tmp)) return k *1ll* i - hsh[tmp];
        tmp = tmp * ak % p;
    }
    return -INF;
}// gcd(a,p) == 1
int exbsgs(LL a,LL b,LL p) {
    b = (b % p + p) % p;
    if(1 % p == b % p) return 0;
    LL x,y;
    int d = exgcd(a,p,x,y);
    if(d > 1) {
        if(b % d) return -INF;
        exgcd(a/d,p/d,x,y);
        return exbsgs(a,b / d *1ll* x % (p / d),p / d) + 1;
    }
    return bsgs(a,b,p);
}
#define endl '\n'
int a[NN],b[NN],aa[NN],bb[NN];
LL inv2;
int N;
void FWT_or(int *a,int opt)
{
    for(int i=1;i<N;i<<=1)
        for(int p=i<<1,j=0;j<N;j+=p)
            for(int k=0;k<i;++k)
                if(opt==1)a[i+j+k]=(a[j+k]+a[i+j+k])%MOD;
                else a[i+j+k]=(a[i+j+k]+MOD-a[j+k])%MOD;
}
void FWT_and(int *a,int opt)
{
    for(int i=1;i<N;i<<=1)
        for(int p=i<<1,j=0;j<N;j+=p)
            for(int k=0;k<i;++k)
                if(opt==1)a[j+k]=(a[j+k]+a[i+j+k])%MOD;
                else a[j+k]=(a[j+k]+MOD-a[i+j+k])%MOD;
}
void FWT_xor(int *a,int opt)
{
    for(int i=1;i<N;i<<=1)
        for(int p=i<<1,j=0;j<N;j+=p)
            for(int k=0;k<i;++k)
            {
                int X=a[j+k],Y=a[i+j+k];
                a[j+k]=(X+Y)%MOD;a[i+j+k]=(X+MOD-Y)%MOD;
                if(opt==-1)a[j+k]=1ll*a[j+k]*inv2%MOD,a[i+j+k]=1ll*a[i+j+k]*inv2%MOD;
            }
}
void solve() {
    cin>>n;
    N = (1 << n);
    inv2 = qpow(2,MOD - 2);
    for(int i = 0; i < N; i++) cin>>aa[i];
    for(int i = 0; i < N; i++) cin>>bb[i];
    for(int i = 0; i < N; i++) a[i] = aa[i],b[i] = bb[i];
    FWT_or(a,1);
    FWT_or(b,1);
    for(int i = 0; i < N; i++) a[i] = 1ll * a[i] * b[i] % MOD;
    FWT_or(a,-1);
    for(int i = 0; i < N; i++) cout<<a[i]<<' ';
    cout<<endl;

    for(int i = 0; i < N; i++) a[i] = aa[i],b[i] = bb[i];
    FWT_and(a,1);
    FWT_and(b,1);
    for(int i = 0; i < N; i++) a[i] = 1ll * a[i] * b[i] % MOD;
    FWT_and(a,-1);
    for(int i = 0; i < N; i++) cout<<a[i]<<' ';
    cout<<endl;
    
    for(int i = 0; i < N; i++) a[i] = aa[i],b[i] = bb[i];
    FWT_xor(a,1);
    FWT_xor(b,1);
    for(int i = 0; i < N; i++) a[i] = 1ll * a[i] * b[i] % MOD;
    FWT_xor(a,-1);
    for(int i = 0; i < N; i++) cout<<a[i]<<' ';
    cout<<endl;
}
//#define ASHDR
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