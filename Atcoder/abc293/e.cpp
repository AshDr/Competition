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
#include <bits/stdc++.h>
#define LOG(FMT...) fprintf(stderr, FMT)
#define sz(x) (int)x.size()
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef unsigned int ui;
typedef unsigned long long ull;
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

const int N = 2e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
ll a,n,mod;
struct matrix {
    ll a[3][3];
    matrix() {
        for(int i=1;i<=2;i++) {
            for(int j=1;j<=2;j++) {
                a[i][j]=0;
            }
        }
    }
    friend matrix operator * (const matrix& lhs,const matrix& rhs) {
        matrix res;
        for(int i=1;i<=2;i++) {
            for(int j=1;j<=2;j++) {
                for(int k=1; k<=2; k++) {
                    res.a[i][j]+=(lhs.a[i][k]*rhs.a[k][j])%mod;
                    res.a[i][j]%=mod;
                }
            }
        }
        return res;
    };
};
matrix qpow(matrix base,ll x) {
    matrix res;
    for(int i=1;i<=2;i++) {
        for(int j=1;j<=2;j++) {
            if(i==j) res.a[i][j]=1;
            else res.a[i][j]=0;
        }
    }
    while(x) {
        if(x&1) {
            res=res*base;
        }
        base=base*base;
        x>>=1;
    }
    return res;
}
void solve() {
    cin>>a>>n>>mod;
    if(n==0) {
        cout<<0<<"\n";
        return ;
    }
    if(a==1) {
    	cout<<n%mod<<"\n";
    }
    else {
    	matrix b;
        b.a[1][1]=1;
        b.a[2][1]=0;
        matrix trans;
        trans.a[1][1]=a;
        trans.a[2][1]=1;trans.a[2][2]=1;
        matrix res=qpow(trans,n);
        res=res*b;
        cout<<res.a[2][1]<<"\n";
    }
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