// 最小路径覆盖
#include<bits/stdc++.h>
//#define cerr cout<<"#case:"
#define LOG(FMT...) fprintf(stderr, FMT)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
const int N = 1e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const LL MOD = 1e9 + 7;
int TT,n,m;
int S,T;
int tot,head[N],to[M << 1],nxt[M << 1],cc[M << 1];
int q[N],d[N],skip[N];
void addedge(int u, int v, int w) {
    to[tot] = v;cc[tot] = w;nxt[tot] = head[u];head[u] = tot++;
    to[tot] = u;cc[tot] = 0;nxt[tot] = head[v];head[v] = tot++;    
}
bool bfs() {
    int hh = 1,tt = 0;
    memset(d,-1,sizeof d);
    q[++tt] = S;d[S] = 0;skip[S] = head[S];
    while(hh <= tt) {
        int u = q[hh++];
        for(int i = head[u]; ~i; i = nxt[i]) {
            int v = to[i];
            if(d[v] == -1 && cc[i]) {
                d[v] = d[u] + 1;
                skip[v] = head[v];
                if(v == T) return true;
                q[++tt] = v;
            }
        }
    }
    return false;
}
int dfs(int u, int limit) {
    if(u == T) return limit;
    int flow = 0;
    for(int i = skip[u]; ~i && flow < limit; i = nxt[i]) {
        skip[u] = i;
        int v = to[i];
        if(d[v] == d[u] + 1 && cc[i]) {
            int tmp = dfs(v,min(limit - flow,cc[i]));
            if(!tmp) d[v] = -1;
            cc[i] -= tmp;cc[i ^ 1] += tmp;
            flow += tmp;
        }
    }
    return flow;
}
int dinic() {
    int res = 0,tmp;
    while(bfs()) while(tmp = dfs(S,INF)) res += tmp;
    return res;
}
int fa[N];
int find(int x) {
    if(fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}
void merge(int x, int y) {
    int fax = find(x),fay = find(y);
    if(fax != fay) fa[fax] = fay;
}
void output(int u) {
    cout<<u<<' ';
    for(int i = head[u]; ~i; i = nxt[i]) {
        int v = to[i];
        if(!cc[i] && v > n) output(v - n);
    }
}
void solve() {
    memset(head,-1,sizeof head);
    cin>>n>>m;
    S = 0,T = 2 * n + 1;
    for(int i = 1; i <= m; i++) {
        int u,v;
        cin>>u>>v;
        addedge(u,v + n,1);
    }
    for(int i = 1; i <= n; i++) {
        addedge(S,i,1);
        addedge(i + n,T,1);
    }
    int res = dinic();
    for(int i = 1; i <= n; i++) fa[i] = i;
    for(int i = 0; i < tot; i += 2) {
        int u = to[i ^ 1],v = to[i];
        if(!cc[i] && u <= n && v > n) merge(v - n,u); //注意合并方向
    }
    for(int i = 1; i <= n; i++) {
        if(fa[i] == i) output(i),cout<<'\n';
    }
    cout<<n - res<<'\n';
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
    TT = 1;
    while(TT--) solve();
    #ifdef ASHDR
    LOG("Time: %dms\n", int ((clock()
            -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
    #endif
    return 0;
}