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
int n,m;
vector<int> G[N];
ll depth[N],anc[N][21],log_2[N],siz[N];
ll f[N],g[N];
void dfs(int u, int fa) {
    for(int i=1; i<=20; i++) anc[u][i]=anc[anc[u][i-1]][i-1];
    siz[u]=1;
    for(auto v: G[u]) {
        if(v==fa) continue;
        depth[v]=depth[u]+1;
        anc[v][0]=u;
        dfs(v,u);
        siz[u]+=siz[v];
        f[u]+=f[v]+siz[v];
    }
}
void dfs1(int u, int fa) {
    if(u!=1) {
        g[u]=g[fa]-siz[u]+n-siz[u];
    }
    for(auto v: G[u]) {
        if(v==fa) continue;
        dfs1(v,u);
    }
}
int gao(int x, int y) {
    for(int i=20; i>=0; i--) {
        if(depth[anc[y][i]]>depth[x]) y=anc[y][i];
    }
    return y;
}
int LCA(int x, int y) {
    if(depth[x]>depth[y]) swap(x,y);
    while(depth[x]<depth[y]) {
        y=anc[y][log_2[depth[y]-depth[x]]];
    }
    assert(depth[x]==depth[y]);
    if(x==y) return y;
    for(int i=20; i>=0; i--) {
        if(anc[x][i]==anc[y][i]) continue;
        else x=anc[x][i],y=anc[y][i];
    }
    assert(anc[x][0]==anc[y][0]);
    return anc[x][0];
}
void solve() {
    cin>>n>>m;
    log_2[1]=0;
    for(int i=2; i<=n; i++) log_2[i]=log_2[i/2]+1;
    for(int i=1; i<=n-1; i++) {
        int u,v;
        cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1,0);
    g[1]=f[1];
    dfs1(1,0);
    // for(int i=1; i<=n; i++) cout<<f[i]<<" \n"[i==n];
    // for(int i=1; i<=n; i++) cout<<g[i]<<" \n"[i==n];
    for(int i=1; i<=m; i++) {
        int x,y;
        cin>>x>>y;
        if(x==y) {
            cout<<0.0<<"\n";
        }else {
            if(depth[x]>depth[y]) swap(x,y);
            int lca=LCA(x,y);
            // cout<<lca<<"!\n";
            if(lca==x) {
                int child=gao(x,y);
                // cout<<child<<"\n";
                ll d=1+depth[y]-depth[x];
                ll tot=f[y]*(n-siz[child])+(g[x]-f[child]-siz[child])*siz[y]+1ll*siz[y]*(n-siz[child])*d;
                // cout<<siz[y]*(n-siz[child])<<"!\n";
                cout<<1.0*tot/(siz[y]*1ll*(n-siz[child]))<<"\n";
            }else {
                ll d=1+depth[x]-depth[lca]+depth[y]-depth[lca];
                ll tot=f[x]*siz[y]+f[y]*siz[x]+1ll*siz[x]*siz[y]*d;
                cout<<1.0*tot/(siz[x]*1ll*siz[y])<<"\n";
            }
        }
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