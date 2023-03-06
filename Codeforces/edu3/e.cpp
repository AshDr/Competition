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
#include <limits.h>
#include <sstream>
#include <tuple>
#include <vector>
#define LOG(FMT...) fprintf(stderr, FMT)
#define sz(x) (int)x.size()
#define lt idx<<1
#define rt idx<<1|1
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
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
struct node {
	int lztag,mx;
}tr[N<<2];
int tot,siz[N],depth[N],son[N],dfn[N],top[N],fa[N],id[N];
int a[N];
vector<pii> G[N];
void dfs1(int u) {
	siz[u]=1;
	for(auto p: G[u]) {
		int v = p.first;
		if(v==fa[u]) continue;
		depth[v]=depth[u]+1;
		fa[v]=u;
		dfs1(v);
		if(siz[v]>siz[son[u]]) son[u]=v;
		siz[u]+=siz[v];
	}
}
void dfs2(int u,int tp){
	dfn[u]=++tot;
	id[tot]=u;
	top[u]=tp;
	if(son[u]) dfs2(son[u],tp);
	for(auto p:G[u]) {
		int v = p.first;
		if(v==son[u]||v==fa[u]) continue;
		dfs2(v,v);
	}
}

void push_down(int idx) {
    if(tr[idx].lztag) {
    	//TODO
    }
}
void push_up(int idx) {
    //TODO
    tr[idx].mx=max(tr[lt].mx,tr[rt].mx);
}
void build(int idx, int L, int R) {
	if(L == R) {
		//TODO
		tr[idx].mx=a[id[L]];
		return;
	}
	int mid=(L+R)>>1;
	build(lt, L, mid);
	build(rt, mid+1, R);
	push_up(idx);
}
void modify(int idx, int l, int r, int val, int L, int R) {
	if(l<=L && r>=R) {
		//TODO
		return;
	}
	push_down(idx);
	int mid = (L+R)>>1;
	if(l<=mid) modify(lt, l, r, val, L, mid);
	if(r>mid) modify(rt, l, r, val, mid+1, R);
	push_up(idx);
}
int query(int idx, int l, int r, int L, int R) {
	if(l>r) return 0;
	if(l<=L && r>=R) {
		//TODO
		return tr[idx].mx;
	}
	int res = 0;
	push_down(idx);
	int mid = (L+R)>>1;
	if(l<=mid) res=max(res,query(lt, l, r, L, mid));
	if(r>mid) res=max(res,query(rt, l, r, mid+1, R));
	return res;
}
void path_modify(int x, int y, int val) {
	while(top[x]!=top[y]) {
		if(depth[top[x]]<depth[top[y]]) swap(x,y);
		modify(1, dfn[top[x]], dfn[x], val, 2, tot);
		x=fa[top[x]];
	}
	if(depth[x]>depth[y]) swap(x,y);
	modify(1, dfn[son[x]], dfn[y], val, 2, tot);
}
int path_query(int x, int y) {
	int res=INT_MIN;
	while(top[x]!=top[y]) {
		if(depth[top[x]]<depth[top[y]]) swap(x,y);
		res = max(res,query(1, dfn[top[x]], dfn[x], 2, tot));
		x=fa[top[x]];
	}
	if(depth[x]>depth[y]) swap(x,y);
	res = max(res,query(1, dfn[son[x]], dfn[y], 2, tot));
	return res;
}
struct DSU {
    std::vector<int> f, siz;
    DSU(int n) : f(n), siz(n, 1) { std::iota(f.begin(), f.end(), 0); }
    int leader(int x) {
        while (x != f[x]) x = f[x] = f[f[x]];
        return x;
    }
    bool same(int x, int y) { return leader(x) == leader(y); }
    bool merge(int x, int y) {
        int fx = leader(x);
        int fy = leader(y);
        if (fx == fy) return false;
        siz[fx] += siz[fy];
        f[fy] = fx;
        return true;
    }
    int size(int x) { return siz[leader(x)]; }
};
int n,m;
int vis[N];
void solve() {
    cin >> n >> m;
    if(n==1){
    	return ;
    }
    vector<tuple<int,int,int,int>> edges,tmp;
    DSU dsu(n+1);
    for(int i = 0; i < m; i++) {
    	int u,v,w;
    	cin >> u >> v >>w;
    	edges.push_back({w,u,v,i});
    	tmp.push_back({w,u,v,i});
    }
    sort(edges.begin(),edges.end());
    ll ans=0;
    vector<tuple<int,int,int>> use;
    for(int i = 0; i < m; i++) {
    	int w=get<0>(edges[i]),u = get<1>(edges[i]),v=get<2>(edges[i]);
    	int fu=dsu.leader(u),fv=dsu.leader(v);
    	if(fu==fv) continue;
    	dsu.merge(u, v);
    	G[u].push_back({v,w});
    	G[v].push_back({u,w});
    	ans += w;
    	vis[get<3>(edges[i])]=1;
    	use.push_back({u,v,w});
    }
    dfs1(1);
    for(auto p: use) {
    	int u=get<0>(p),v=get<1>(p),w=get<2>(p);
    	if(depth[u]>depth[v]) swap(u,v);
    	a[v]=w;
    }
    dfs2(1,1);	
    build(1, 2, n);
    for(int i = 0; i < m; i++) {
    	if(vis[i]) cout<<ans<<"\n";
    	else {
    		cout << ans+get<0>(tmp[i])-path_query(get<1>(tmp[i]),get<2>(tmp[i]))<<"\n";
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