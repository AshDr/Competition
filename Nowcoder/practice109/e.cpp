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
#include <numeric>
#include <queue>
#include <string>
#define LOG(FMT...) fprintf(stderr, FMT)
#define sz(x) (int)x.size()
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
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
const int M = 1e7 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
int n,m;
vector<pii> G[N];
bool have[M],vis[N];
int S,rt,cnt,siz[N],q[N],d[N];
int ans[N],mx[N];
void find_rt(int u, int fa) {
    siz[u]=1;mx[u]=0;
    for(auto [v,w]: G[u]) {
        if(vis[v]||v==fa) continue;
        find_rt(v, u);
        siz[u]+=siz[v];
        mx[u]=max(mx[u],siz[v]);
    }
    mx[u]=max(mx[u],S-siz[u]);
    if(mx[u]<mx[rt]) rt=u;
}
void get_siz(int u, int fa) {
    siz[u]=1;
    for(auto [v,w]:G[u]) {
        if(vis[v]||v==fa) continue;
        get_siz(v, u);
        siz[u]+=siz[v];
    }
}
void get_dis(int u, int fa, int dis) {
    d[++cnt]=dis;
    for(auto [v,w]: G[u]) {
        if(vis[v]||v==fa) continue;
        get_dis(v, u, dis+w);
    }
}
int num;
void dfz(int u) {

    // cout<<u<<" "<<rt<<endl;
    vis[rt]=1;
    queue<int> tag;
    tag.push(0);
    have[0]=1;
    for(auto [v,w]: G[rt]) {
        if(vis[v]) continue;
        cnt=0;get_dis(v,u,w);
        for(int i=1; i<=cnt; i++) {
            for(int j=1; j<=m; j++) {
                if(q[j]>=d[i]) ans[j]|=have[q[j]-d[i]];
            }
        } 
        for(int i=1; i<=cnt; i++) {
            if(d[i]<M) tag.push(d[i]),have[d[i]]=1;
        }
    }
    while(!tag.empty()) {
        int x=tag.front();tag.pop();
        have[x]=0;
    }
    for(auto [v,w]:G[rt]) {
        if(!vis[v]) {
            // get_siz(v, rt); //应该是要这一行的 不加这一行复杂度不影响
            S=siz[v];
            find_rt(v, rt);find_rt(rt, -1);
            dfz(v);
        }
    }
    //874 594 1
}
#define ASHDR
void solve() {
    cin>>n>>m;
    for(int i=1; i<=n-1; i++) {
        int u,v,w;
        cin>>u>>v>>w;
        G[u].push_back({v,w});
        G[v].push_back({u,w});
    }
    for(int i=1; i<=m; i++) cin>>q[i];
    S=n;mx[rt=0]=1e9;find_rt(1, -1);find_rt(rt, -1);
    dfz(rt);
    // cout<<num<<"\n";
    for(int i=1; i<=m; i++) cout<<(ans[i]==1?"AYE\n":"NAY\n");
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