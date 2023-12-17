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
constexpr LL MOD = 998244353;
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
LL qpow(LL base, LL x, LL MOD = MOD) {
    LL res = 1;
    while(x) {
       if(x & 1) res = (res * base) % MOD;
       base = (base * base) % MOD;
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
/*
快速莫比乌斯变换和莫比乌斯函数/反演并无关系。

FMT 处理 or/and 时的问题，可以看作是集合的 交/并 来看。

FWT 处理 xor 时的问题。但是有时把 FMT 和 FWT 统称为 FWT

FMT 是从sosdp的角度(高位前缀和)入手


FMT 是从DP方向推出的结论，而 FWT 是从变换方向推出的结论。殊途同归，它们在 OR 和 AND 卷积中得到了一样的结果，不同的是 FWT 有着更像 FFT 的结构。
但正因如此，OR 和 AND 的 FWT 要比 FMT 难写很多，且不方便理解。所以，这两种情形推荐直接使用 FMT，而把 FWT 留到 XOR 卷积上使用。


*/
/*

*/
int all;
int A[NN],B[NN];
void FMT_or(int *a,int tp){for(int i=0;i<n;i++)for(int j=0;j<all;j++)if(j&(1<<i))(a[j]+=(MOD+tp*a[j^(1<<i)])%MOD)%=MOD;}
void OR(int *a,int *b,int *c){
    for(int i=0;i<all;i++)A[i]=a[i],B[i]=b[i];
    FMT_or(A,1),FMT_or(B,1);
    for(int i=0;i<all;i++)A[i]=1ll*A[i]*B[i]%MOD;
    FMT_or(A,-1);
    for(int i=0;i<all;i++)(c[i]+=A[i])%=MOD;
}
void FMT_and(int *a,int tp){for(int i=0;i<n;i++)for(int j=all-1;j>=0;j--)if(j&(1<<i))(a[j^(1<<i)]+=(MOD+tp*a[j])%MOD)%=MOD;}
void AND(int *a,int *b,int *c){
    for(int i=0;i<all;i++)A[i]=a[i],B[i]=b[i];
    FMT_and(A,1),FMT_and(B,1);
    for(int i=0;i<all;i++)A[i]=1ll*A[i]*B[i]%MOD;
    FMT_and(A,-1);
    for(int i=0;i<all;i++)(c[i]+=A[i])%=MOD;
}
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
    all = N;
    inv2 = qpow(2,MOD - 2);
    for(int i = 0; i < N; i++) cin>>aa[i];
    for(int i = 0; i < N; i++) cin>>bb[i];
    for(int i = 0; i < N; i++) a[i] = aa[i],b[i] = bb[i];
    FMT_or(a,1);
    FMT_or(b,1);
    for(int i = 0; i < N; i++) a[i] = 1ll * a[i] * b[i] % MOD;
    FWT_or(a,-1);
    for(int i = 0; i < N; i++) cout<<a[i]<<' ';
    cout<<endl;

    for(int i = 0; i < N; i++) a[i] = aa[i],b[i] = bb[i];
    FMT_and(a,1);
    FMT_and(b,1);
    for(int i = 0; i < N; i++) a[i] = 1ll * a[i] * b[i] % MOD;
    FMT_and(a,-1);
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
/*
    经典多合一 适合复习


#include <bits/stdc++.h>
#include <functional>
#include <random>
#define LOG(FMT...) fprintf(stderr, FMT)
#define sz(x) (int)x.size()
using namespace std;
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

const int N = 1e6 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 9;
int TT = 1;
using ll = long long;
template<class T>
constexpr T power(T a, ll b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
 
constexpr ll mul(ll a, ll b, ll p) {
    ll res = a * b - ll(1.L * a * b / p) * p;
    res %= p;
    if (res < 0) {
        res += p;
    }
    return res;
}
template<ll P>
struct MLong {
    ll x;
    constexpr MLong() : x{} {}
    constexpr MLong(ll x) : x{norm(x % getMod())} {}
    
    static ll Mod;
    constexpr static ll getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(ll Mod_) {
        Mod = Mod_;
    }
    constexpr ll norm(ll x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr ll val() const {
        return x;
    }
    explicit constexpr operator ll() const {
        return x;
    }
    constexpr MLong operator-() const {
        MLong res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MLong inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr MLong &operator*=(MLong rhs) & {
        x = mul(x, rhs.x, getMod());
        return *this;
    }
    constexpr MLong &operator+=(MLong rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MLong &operator-=(MLong rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MLong &operator/=(MLong rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr MLong operator*(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MLong operator+(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MLong operator-(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MLong operator/(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, MLong &a) {
        ll v;
        is >> v;
        a = MLong(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const MLong &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MLong lhs, MLong rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MLong lhs, MLong rhs) {
        return lhs.val() != rhs.val();
    }
};
 
template<>
ll MLong<0LL>::Mod = ll(1E18) + 9;
 
template<int P>
struct MInt {
    int x;
    constexpr MInt() : x{} {}
    constexpr MInt(ll x) : x{norm(x % getMod())} {}
    
    static int Mod;
    constexpr static int getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(int Mod_) {
        Mod = Mod_;
    }
    constexpr int norm(int x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr int val() const {
        return x;
    }
    explicit constexpr operator int() const {
        return x;
    }
    constexpr MInt operator-() const {
        MInt res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MInt inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr MInt &operator*=(MInt rhs) & {
        x = 1LL * x * rhs.x % getMod();
        return *this;
    }
    constexpr MInt &operator+=(MInt rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MInt &operator-=(MInt rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MInt &operator/=(MInt rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr MInt operator*(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MInt operator+(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MInt operator-(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MInt operator/(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, MInt &a) {
        ll v;
        is >> v;
        a = MInt(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const MInt &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MInt lhs, MInt rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MInt lhs, MInt rhs) {
        return lhs.val() != rhs.val();
    }
};
 
template<>
int MInt<0>::Mod = 998244353;
template<int V, int P>
constexpr MInt<P> CInv = MInt<P>(V).inv();
constexpr int P = 1e9+7;
using mint = MInt<P>;
int LIM = (1 << 17), n = 17;
mint inv2;
void ORFMT(vector<mint>& a,int tp){
    for(int i = 0; i < n; i++)
        for(int j = 0;j < LIM; j++)
            if(j >> i & 1) a[j] += tp * a[j ^ (1 << i)];
}
void ANDFMT(vector<mint>& a, int tp) {
    for(int i = 0; i < n; i++) {
        for(int j = LIM - 1; j >= 0; j--) {
            if(j >> i & 1) a[j ^ (1 << i)] += tp * a[j];
        }
    }
}
void FWT_xor(vector<mint>& a,int opt)
{
    for(int i=1;i<LIM;i<<=1)
        for(int p=i<<1,j=0;j<LIM;j+=p)
            for(int k=0;k<i;++k)
            {
                mint X=a[j+k],Y=a[i+j+k];
                a[j+k]=(X+Y);a[i+j+k]=(X-Y);
                if(opt==-1)a[j+k]=1ll*a[j+k]*inv2,a[i+j+k]=1ll*a[i+j+k]*inv2;
            }
}
int m;
void solve() {
    cin >> m;
    LIM = (1 << n);
    inv2 = mint(2).inv();   
    vector<vector<mint>> a(n + 1,vector<mint>(LIM));
    vector<mint> b(LIM), c(LIM),d(LIM),ans(LIM),fib(LIM);
    for(int i = 0; i < m; i++) {
        int x;
        cin >> x;
        a[__builtin_popcount(x)][x] += 1;
        c[x] += 1;
        d[x] += 1;
    }
    for(int i = 0; i <= n; i++) ORFMT(a[i], 1);
    for(int i = n; i >= 0; i--) {
        for(int j = 0; j < LIM; j++) {
            mint x = 0;
            for(int k = 0; k <= i; k++) {
                x += a[k][j] * a[i - k][j];
            }
            a[i][j] = x;
        }
    }
    //子集自卷积
    for(int i = 0; i <= n; i++) ORFMT(a[i], -1);

    for(int i = 0; i < LIM; i++) b[i] = a[__builtin_popcount(i)][i];
    FWT_xor(c, 1);
    for(int i = 0; i < LIM; i++) c[i] = c[i] * c[i];
    FWT_xor(c, -1);
    
    // c b d
    fib[0] = 0;fib[1] = 1;
    for(int i = 2; i < LIM; i++) fib[i] = fib[i - 1] + fib[i - 2];
    for(int i = 0; i < LIM; i++) {
        b[i] *= fib[i];
        c[i] *= fib[i];
        d[i] *= fib[i];
    }
    ANDFMT(b, 1);ANDFMT(c, 1);ANDFMT(d, 1);
    for(int i = 0; i < LIM; i++) ans[i] = b[i] * c[i] * d[i];
    ANDFMT(ans, -1);
    mint res = 0;
    for(int i = 0; i < n; i++) res += ans[1 << i];
    cout << res << "\n";
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
*/