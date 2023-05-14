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
#include <functional>
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
int n,m,k;
vector<int> G[N];
int vis[N],siz[N],vis_siz[N];
void dfs(int u, int fa) {
	siz[u]=1;
	if(vis[u]) vis_siz[u]=1;
	for(auto v: G[u]) {
		if(v==fa) continue;
		dfs(v,u);
		siz[u]+=siz[v];
		vis_siz[u]+=vis_siz[v];
	}
}

void solve() {
    cin>>n>>m;
    for(int i=1; i<=n-1; i++) {
    	int u,v;
    	cin>>u>>v;
    	G[u].push_back(v);
    	G[v].push_back(u);
    }
    cin>>k;
    for(int i=1; i<=k; i++) {
    	int x;
    	cin>>x;
    	vis[x]=1;
    }
    dfs(1,0);
    vector<vector<ll>> dp(n+1,vector<ll>(m+1,0));
    function<void(int ,int )> gao= [&](int u, int fa) {
        if(vis_siz[u]==1&&vis[u]==1) {
            return ;
        }
        for(auto v: G[u]) {
            if(v==fa||vis_siz[v]==0) continue;
            gao(v,u);
            vector<ll> ndp(m+1,0);
            for(int i=0; i<=min(vis_siz[u],m); i++) ndp[i]=dp[u][i]+dp[v][0]+2;
            for(int i=0; i<=min(vis_siz[u],m); i++) {
                for(int j=i; j>=0; j--) {
                    ndp[i]=min(ndp[i],dp[u][i-j]+(j>=vis_siz[v]?0:2+dp[v][j]));
                }
            }      
            dp[u]=ndp;
        }
    };
    gao(1,0);
    cout<<dp[1][min(vis_siz[1],m)]<<"\n";
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