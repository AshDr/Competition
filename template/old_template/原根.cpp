#include<bits/stdc++.h>
//#define cerr cout<<"#case:"
#define LOG(FMT...) fprintf(stderr, FMT)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
const int N = 1e6 + 10;
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
//LL fac[N],inv[N];
LL gcd(LL x, LL y) {return y == 0 ? x : gcd(y, x % y);}
LL qpow(LL base, LL x,LL mod) {
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
int bsgs(LL a,LL b,LL p) {
    if(1 % p == b % p) return 0;
    int k = sqrt(p) + 1;
    unordered_map<LL,LL> hsh; // warn
    LL tmp = b % p;
    for(int i = 0; i < k; i++) {
        hsh[tmp] = i;
        tmp = (tmp * a) % p;
    }
    LL ak = 1;
    for(int i = 1; i <= k; i++) ak = (ak * a) % p;
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
int dd;
int tot,phi[N],prime[N],d[N],yg[N];
void init() {
    phi[1] = 1;d[1] = 1;
    for(int i = 2; i < N; i++) {
        if(!d[i]) {prime[++tot] = i;phi[i] = i - 1;}
        for(int j = 1; j <= tot && prime[j] * i < N; j++) {
            int tmp = prime[j] * i;
            d[tmp] = prime[j];
            if(i % prime[j] == 0) {
                phi[tmp] = phi[i] * prime[j];
                break;
            }
            else phi[tmp] = phi[i] * (prime[j] - 1);
        }
    }
    yg[2] = yg[4] = 1;
    for(int i = 2; i <= tot; i++) {
        for(int j = 1; j *1ll* prime[i] < N; j *= prime[i]) yg[j * prime[i]] = 1;
        for(int j = 2; j *1ll* prime[i] < N; j *= prime[i]) yg[j * prime[i]] = 1;
    }

}
vector<int> b;
bool check(int x) {
    if(qpow(x,phi[n],n) != 1) return false;
    for(int i = 0 ; i < (int)b.size(); i++) {
        if(qpow(x,phi[n] / b[i],n) == 1) return false;
    }
    return true;
}
int anscnt = 0;
int ans[N];
void solve() {
    cin>>n>>dd;
    if(yg[n]) {
        int t = phi[n];
        b.clear();
        anscnt = 0;
        for(int i = 2; i * i <= t; i++) {
            if(t % i == 0) {
                while(t % i == 0) t /= i;
                b.push_back(i);
            }
        }
        if(t > 1) b.push_back(t);
        int mnyg;
        for(int i = 1; i < n; i++) {
            if(check(i)) {
                mnyg = i;
                break;
            }
        }
        //debug(mnyg);
        LL res = 1;
        for(int i = 1; i <= phi[n]; i++) {
            res = res * mnyg;
            res %= n;
            if(gcd(i,phi[n]) == 1) {
                ans[++anscnt] = res;
            }
        }
        sort(ans + 1,ans + 1 + anscnt);
        cout<<anscnt<<'\n';
        for(int i = 1; i <= anscnt / dd; i++) cout<<ans[i * dd]<<' ';
        cout<<'\n';
    }
    else cout<<0<<"\n\n";
    
}
int main() {
    #ifdef ASHDR
    freopen("data.in","r",stdin);
    int nol_cl = clock();
    #endif
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout<<fixed<<setprecision(8);
    init();
    cin>>TT;
    //TT = 1;
    while(TT--) solve();
    #ifdef ASHDR
    LOG("Time: %dms\n", int ((clock()
            -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
    #endif
    return 0;
}