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
#include <random>
#define LOG(FMT...) fprintf(stderr, FMT)
#define sz(x) (int)x.size()
#define all(x) (x).begin(),(x).end()
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

const int N = 2e5 + 10;
const int M = N + N * 2 * 18;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
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
#define lt idx<<1
#define rt idx<<1|1
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> depth(n),indeg(M);
    vector<int> lg2(n + 1);
    for(int i = 2; i <= n; i++) lg2[i] = lg2[i / 2] + 1;
    vector<vector<int>> adj(M);
    HLD hld(n);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        --u;--v;
        hld.addEdge(u, v);
    }
    hld.work();
    auto add_edge = [&](int x, int y) {
        adj[x].push_back(y);
        indeg[y]++;
    };
    
    int tot_ecnt = n;
    vector<vector<int>> edgedown(n,vector<int>(22)),edgeup(n,vector<int>(22)); 
    for(int i = 0; i < n; i++) edgedown[hld.in[i]][0] = edgeup[hld.in[i]][0] = i;
    
    for(int o = 1; o <= lg2[n]; o++) {
        for(int i = 0; i + (1 << o) <= n; i++) {
            edgedown[i][o] = tot_ecnt++;
            edgeup[i][o] = tot_ecnt++;
            add_edge(edgedown[i][o], edgedown[i][o - 1]);
            add_edge(edgedown[i][o], edgedown[i + (1 << (o - 1))][o - 1]);

            add_edge(edgeup[i][o - 1], edgeup[i][o]);
            add_edge(edgeup[i + (1 << (o - 1))][o - 1], edgeup[i][o]);
        }
    }
    auto gao1 = [&](auto self, int l, int r, int p)->void {
        if(l <= hld.in[p] && hld.in[p] <= r) {
            if(l < hld.in[p]) self(self, l, hld.in[p] - 1, p);
            if(r > hld.in[p]) self(self, hld.in[p] + 1, r, p);
        }else {
            int bit = lg2[r - l + 1];
            add_edge(p, edgedown[l][bit]);
            add_edge(p, edgedown[r - (1 << bit) + 1][bit]);
        }
    };
    auto gao2 = [&](auto self, int l, int r, int p)->void {
        if(l <= hld.in[p] && hld.in[p] <= r) {
            if(l < hld.in[p]) self(self, l, hld.in[p] - 1, p);
            if(r > hld.in[p]) self(self, hld.in[p] + 1, r, p);
        }else {
            int bit = lg2[r - l + 1];
            assert(l >= 0 && r < n);
            add_edge(edgeup[l][bit], p);
            add_edge(edgeup[r - (1 << bit) + 1][bit], p);
            assert((r - (1 << bit) + 1) < n);
        }
    };

    for(int i = 0; i < m; i++) {
        int op, a, b, c;
        cin >> op >> a >> b >> c;
        --a;--b;--c;
        if(op == 1) { //c向a~b连边
            while(hld.top[a] != hld.top[b]) {
                if(hld.dep[hld.top[a]] < hld.dep[hld.top[b]]) swap(a, b);
                gao1(gao1, hld.in[hld.top[a]], hld.in[a], c);
                a = hld.parent[hld.top[a]];
            }
            if(hld.in[a] > hld.in[b]) swap(a ,b);
            gao1(gao1, hld.in[a], hld.in[b], c);
        }else {//a~b向c连边
            while(hld.top[a] != hld.top[b]) {
                if(hld.dep[hld.top[a]] < hld.dep[hld.top[b]]) swap(a, b);
                gao2(gao2, hld.in[hld.top[a]], hld.in[a], c);
                a = hld.parent[hld.top[a]];
            }
            if(hld.in[a] > hld.in[b]) swap(a ,b);
            gao2(gao2, hld.in[a], hld.in[b], c);
        }
    }
    queue<int> q;
    for(int i = 0; i < M; i++) {
        if(indeg[i] == 0) {
            q.push(i);
        }
    }
    vector<int> ord;
    while(!q.empty()) {
        int u = q.front();q.pop();
        if(u < n) {
            ord.push_back(u);
        }
        for(auto v: adj[u]) {
            indeg[v]--;
            if(indeg[v] == 0) q.push(v);
        }
    }
    if(sz(ord) != n) cout << -1 << "\n";
    else {
        vector<int> ans(n);
        for(int i = 0; i < n; i++) {
            ans[ord[i]] = i + 1;
        }
        cout << ans << "\n";
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