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
int n;
vector<int> G[N];
ll x,y,ans;
ll dp[N];
int f[N];
// bool dfs(int u, int fa) {
//     int son=2;
//     for(auto v:G[u]) {
//         if(v==fa) continue;
//         if(dfs(v,u)&&son) {
//             son--;
//             ++ans;
//         }
//     }
//     return son>0;
// }
void dfs(int u, int fa) {
    if(sz(G[u])==1&&u!=1) {
        dp[u]=1;
        f[u]=1;
        return ;
    }
    int num=0;
    for(auto v:G[u]) {
        if(v==fa) continue;
        dfs(v,u);
        dp[u]+=dp[v];
        num+=f[v];
    }
    if(num==0) dp[u]++,f[u]=1;
    if(num==1) f[u]=1;
    if(num>=2) dp[u]--,f[u]=0;
}
void solve() {
    cin>>n>>x>>y;
    for(int i=1; i<=n-1; i++) {
        int u,v;
        cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    int f=0;
    for(int i=1; i<=n; i++) if(sz(G[i])==n-1) f=1;

    if(x>=y) {
        if(!f) cout<<1ll*(n-1)*y<<"\n";
        else cout<<1ll*(n-2)*y+x<<"\n";
    }else {
        dfs(1,0);
        // cout<<1ll*ans*x+(n-1-ans)*y<<"\n";
        cout<<1ll*(dp[1]-1)*y+(n-dp[1])*x<<"\n";
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