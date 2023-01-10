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
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
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
LL gcd(LL x, LL y) {return y == 0 ? x : gcd(y, x % y);}
LL qpow(LL base, LL x, LL mod) {
    LL res = 1;
    base %= mod;
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

const int N = 1e6 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const LL MOD = 1e9 + 7;
int TT = 1;
int n;
vector<int>G[N];
LL dp1[N],dp2[N];//dp1以u为根的子树中，算u的贡献。dp2表示以u为总根，统计1~n每个点的贡献的和
int siz[N];
LL ans;
void dfs1(int u, int fa) {
    siz[u] = 1;
    for(auto v: G[u]) {
        if(fa == v) continue;
        dfs1(v,u);    
        dp1[u] += 2ll*u*(siz[u]-1)*siz[v];
        siz[u] += siz[v];
    }
    dp1[u] += (2ll*siz[u]-1)*u;
    ans += dp1[u];
}
void dfs2(int u, int fa) {
    //fa的值要少算siz[u]所能提供的贡献 
    //u的值要多算n-siz[u]所能提供的贡献
    // dp2[u] = dp1[u];
    if(u != 1) {
        dp2[u] = dp2[fa];
        //1*2*2
        dp2[u] -= 2ll*fa*siz[u]*(siz[fa]-siz[u]-1);//2*2*1
        dp2[u] -= 2ll*fa*siz[u];
        dp2[u] += 2ll*(n-siz[u])*u;
        dp2[u] += 2ll*u*(siz[u]-1)*(n-siz[u]);
        // cout << u  << " " << fa*siz[u]*(siz[fa]-siz[u]-1) << " " << 2*fa*siz[u] << " " <<2*(n-siz[u])*u << " " << 2*u*(siz[u]-1)*(n-siz[u]) << "\n"; 
    }
    siz[u] = n;
    for(auto v: G[u]) {
        if(fa == v) continue;
        dfs2(v,u);
    }
}
/*
*/
void solve() {
	//x的贡献分为两部分 1.x与它所有子树节点 2.x的两个不同子树中的节点
    cin >> n;
    for(int i = 1; i <= n - 1; i++) {
        int u,v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs1(1,0);
    dp2[1] = ans;
    //30
    // cout << ans << "\n";
    dfs2(1,0);

    // for(int i=1;i<=n;i++) cout << dp2[i] << " \n"[i==n]; 
    cout << max_element(dp2 + 1,dp2 + 1 + n) - dp2 << ' ' << *max_element(dp2 + 1,dp2 + 1 + n); 
}
int main() {
    #ifdef ASHDR
    freopen("data.in","r",stdin);
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