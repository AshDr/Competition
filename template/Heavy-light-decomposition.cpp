// 1_based HLD
struct Edge{
    int to;
    int w;
    operator int() const { return to; }
};
 
struct HLD{
    int n;
    vector<int> sz, top, dep, fa, in, out, seq;
    vector<vector<Edge> > g;
    vector<LL> dis;
    int ts;
 
    HLD(const vector<vector<Edge> > &g, int root = 1) : n(int(g.size()) - 1), g(g)  {
        ts = 0;
        sz.resize(n + 1);
        top.resize(n + 1);
        dep.resize(n + 1);
        fa.resize(n + 1);
        in.resize(n + 1);
        out.resize(n + 1);
        seq.resize(n + 1);
        dis.resize(n + 1);
        dep[root] = 1;
        top[root] = root;
        dfs_sz(root);
        dfs_hld(root);
    }
 
    void dfs_sz(int u){
        if (fa[u]){
            for(auto it = g[u].begin(); it != g[u].end(); it++){
                if (*it == fa[u]){
                    g[u].erase(it);
                    break;
                }
            }
        }
        sz[u] = 1;
        for(auto &j : g[u]){
            fa[j] = u;
            dep[j] = dep[u] + 1;
            dis[j] = dis[u] + j.w;
            dfs_sz(j);
            sz[u] += sz[j];
            if (sz[j] > sz[g[u][0]])
                swap(j, g[u][0]);
        }
    }
 
    void dfs_hld(int u){
        in[u] = ++ts;
        seq[in[u]] = u;
        for (auto j : g[u]){
            top[j] = (j == g[u][0] ? top[u] : j);
            dfs_hld(j);
        }
        out[u] = ts;
    }
 
    int lca(int u, int v){
        while (top[u] != top[v]){
            if (dep[top[u]] > dep[top[v]]){
                u = fa[top[u]];
            } 
            else{
                v = fa[top[v]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    }
 
    LL dist(int u, int v){
        return dis[u] + dis[v] - 2 * dis[lca(u, v)];
    }
 
    bool in_subtree(int u, int v){
        return in[v] <= in[u] && in[u] <= out[v];
    }
     
    int jump(int u, int k) {
        if (dep[u] < k){
            return -1;
        }
        int d = dep[u] - k;
        while (dep[top[u]] > d){
            u = fa[top[u]];
        }
        return seq[in[u] - dep[u] + d];
    }
     
    int rooted_lca(int a, int b, int c){
        return lca(a, b) ^ lca(b, c) ^ lca(c, a);
    }
 
    template<typename Q>
    void modify_path(int u, int v, const Q &q, bool edge = false){
        while(top[u] != top[v]){
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            q(in[top[u]], in[u]);
            u = fa[top[u]];        
        }
        if (dep[u] > dep[v]) swap(u, v);
        q(in[u] + edge, in[v]);
    }
 
    template<typename Q>
    void modify_subtree(int u, const Q &q){
        q(in[u], out[u]);
    }  
 
    template<typename T, typename Q>
    T query_path(int u, int v, const Q &q, bool edge = false){
        T ret = T();
        while(top[u] != top[v]){
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            ret = q(in[top[u]], in[u]) + ret;
            u = fa[top[u]];
        }
        if (dep[u] > dep[v]) swap(u, v);
        return q(in[u] + edge, in[v]) + ret;
    }
 
    template<typename T, typename Q>
    T query_subtree(int u, const Q &q){
        return q(in[u], out[u]);
    }
 
    template<typename T, typename Q, typename F>
    T query_path_noncommutative(int u, int v, const Q &q, const F &f, bool edge = false){
        T left = T(), right = T();
        while(top[u] != top[v]){
            if (dep[top[u]] < dep[top[v]]) swap(u, v), swap(left, right);
            left = q(in[top[u]], in[u]) + left;
            u = fa[top[u]];
        }
        if (dep[u] > dep[v]) swap(u, v), swap(left, right);
        return f(left, q(in[u] + edge, in[v]) + right);
    }
 
};
/*
struct HLD {
    int n;
    std::vector<int> siz, top, dep, parent, in, out, seq;
    std::vector<std::vector<int>> adj;
    int cur;
    
    HLD() {}
    HLD(int n) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        siz.resize(n);
        top.resize(n);
        dep.resize(n);
        parent.resize(n);
        in.resize(n);
        out.resize(n);
        seq.resize(n);
        cur = 0;
        adj.assign(n, {});
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void work(int root = 0) {
        top[root] = root;
        dep[root] = 0;
        parent[root] = -1;
        dfs1(root);
        dfs2(root);
    }
    void dfs1(int u) {
        if (parent[u] != -1) {
            adj[u].erase(std::find(adj[u].begin(), adj[u].end(), parent[u]));
        }
        
        siz[u] = 1;
        for (auto &v : adj[u]) {
            parent[v] = u;
            dep[v] = dep[u] + 1;
            dfs1(v);
            siz[u] += siz[v];
            if (siz[v] > siz[adj[u][0]]) {
                std::swap(v, adj[u][0]);
            }
        }
    }
    void dfs2(int u) {
        in[u] = cur++;
        seq[in[u]] = u;
        for (auto v : adj[u]) {
            top[v] = v == adj[u][0] ? top[u] : v;
            dfs2(v);
        }
        out[u] = cur;
    }
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]]) {
                u = parent[top[u]];
            } else {
                v = parent[top[v]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    }
    
    int dist(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }
    
    int jump(int u, int k) {
        if (dep[u] < k) {
            return -1;
        }
        
        int d = dep[u] - k;
        
        while (dep[top[u]] > d) {
            u = parent[top[u]];
        }
        
        return seq[in[u] - dep[u] + d];
    }
    
    bool isAncester(int u, int v) {
        return in[u] <= in[v] && in[v] < out[u];
    }
    
    int rootedParent(int u, int v) {
        std::swap(u, v);
        if (u == v) {
            return u;
        }
        if (!isAncester(u, v)) {
            return parent[u];
        }
        auto it = std::upper_bound(adj[u].begin(), adj[u].end(), v, [&](int x, int y) {
            return in[x] < in[y];
        }) - 1;
        return *it;
    }
    
    int rootedSize(int u, int v) {
        if (u == v) {
            return n;
        }
        if (!isAncester(v, u)) {
            return siz[v];
        }
        return n - siz[rootedParent(u, v)];
    }
    
    int rootedLca(int a, int b, int c) {
        return lca(a, b) ^ lca(b, c) ^ lca(c, a);
    }
};
*/

/*
//轻重链剖分 边权 注意query和modify有可能会l>r 要判一下
#include <bits/stdc++.h>
#include <vector>
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
int n,m;
vector<pii> G[N];
int tot,siz[N],son[N],dfn[N],top[N],fa[N],id[N],eval[N],a[N];
ll depth[N];
struct node {
	int lztag;
	ll sum;
}tr[N<<2];
#define lt idx<<1
#define rt idx<<1|1
void dfs1(int u) {
	siz[u]=1;
	for(auto [v,w]: G[u]) {
		if(v==fa[u]) continue;
		depth[v]=depth[u]+w;
		fa[v]=u;
		dfs1(v);
		if(siz[v]>siz[son[u]]) son[u]=v;
		siz[u]+=siz[v];
	}
}
void dfs2(int u,int tp){
	dfn[u]=++tot;
	a[tot]=eval[u];
	id[tot]=u;
	top[u]=tp;
	if(son[u]) dfs2(son[u],tp);
	for(auto [v,w]:G[u]) {
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
    tr[idx].sum = tr[lt].sum+tr[rt].sum;
}
void build(int idx, int L, int R) {
	if(L == R) {
		tr[idx].sum=a[L];
		return;
	}
	int mid=(L+R)>>1;
	build(lt, L, mid);
	build(rt, mid+1, R);
	push_up(idx);
}
void modify(int idx, int l, int r, int val, int L, int R) {
	if(l>r) return ;
	if(l<=L && r>=R) {
		tr[idx].sum=val;
		return ;
	}
	push_down(idx);
	int mid = (L+R)>>1;
	if(l<=mid) modify(lt, l, r, val, L, mid);
	if(r>mid) modify(rt, l, r, val, mid+1, R);
	push_up(idx);
}
ll query(int idx, int l, int r, int L, int R) {
	if(l>r) return 0;
	if(l<=L && r>=R) {
		return tr[idx].sum;
	}
	ll res = 0;
	push_down(idx);
	int mid = (L+R)>>1;
	if(l<=mid) res+=query(lt, l, r, L, mid);
	if(r>mid) res+=query(rt, l, r, mid+1, R);
	return res;
}
void path_modify(int x, int y, int val) {
	while(top[x]!=top[y]) {
		if(depth[top[x]]<depth[top[y]]) swap(x,y);
		modify(1, dfn[top[x]], dfn[x], val, 1, tot);
		x=fa[top[x]];
	}
	if(depth[x]>depth[y]) swap(x,y);
	
	modify(1,dfn[x]+1,dfn[y],val,1,tot);
}
ll path_query(int x, int y) {
	ll res=0;
	while(top[x]!=top[y]) {
		if(depth[top[x]]<depth[top[y]]) swap(x,y);
		res += query(1, dfn[top[x]], dfn[x], 1, tot);
		x=fa[top[x]];
	}
	if(depth[x]>depth[y]) swap(x,y);
	res += query(1,dfn[x]+1,dfn[y],1,tot);
	return res;
}
pii idd[N];
struct edge {
	int u,v,w;
}e[N];
void solve() {
	cin>>n;
    for(int i=1; i<n; i++) {
    	int u,v,w;
    	cin>>u>>v>>w;
    	G[u].push_back({v,w});
    	G[v].push_back({u,w});
    	e[i].u=u;e[i].v=v;e[i].w=w;
    	idd[i]={min(u,v),max(u,v)};
    }
    dfs1(1);
    for(int i=1; i<n; i++) {
    	if(siz[e[i].u]<siz[e[i].v]) swap(e[i].u,e[i].v);
    	eval[e[i].v]=e[i].w;
    }
    dfs2(1,0);
    build(1, 1, n);
    cin>>m;
    for(int i=1; i<=m; i++) {
    	int op;
    	cin>>op;
    	if(op==1) {
    		int x,w;
    		cin>>x>>w;
    		path_modify(idd[x].first,idd[x].second, w);
    	}else {
    		int u,v;
    		cin>>u>>v;
    		cout<<path_query(u, v)<<"\n";
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
*/