#include<bits/stdc++.h>
//#define cerr cout<<"#case:"
#define LOG(FMT...) fprintf(stderr, FMT)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
const int N = 4e5 + 10;
const int M = 5e5 + 10;
const int INF = 2147483647;
const LL MOD = 1e9 + 7;
int TT,n,m;
typedef unsigned long long ull;
ull myRand(ull &k1, ull &k2){
    ull k3 = k1, k4 = k2;
    k1 = k4;
    k3 ^= (k3 <<23);
    k2 = k3 ^ k4 ^ (k3 >>17) ^ (k4 >>26);
    return k2 + k4;
}
pair<int,int>myRanq(ull&k1,ull&k2,int MAXN){
    int x=myRand(k1,k2)%MAXN+1,y=myRand(k1,k2)%MAXN+1;
    if(x>y)return make_pair(y,x);
    else return make_pair(x,y);
}
struct edge {
    int u,v,w;
    friend bool operator < (const edge& x,const edge& y) {
        return x.w < y.w;
    }
}e[N];
int fa[N];
int find(int x) {
    if(x == fa[x]) return x;
    return fa[x] = find(fa[x]);
}
void merge(int x, int y) {
    int fax = find(x),fay = find(y);
    if(fax != fay) fa[fax] = fay;
}
int tot,head[N],nxt[M << 1],to[M << 1],val[N];
int cnt;
int fir[N],id[N],depth[N],dfn_num,log_2[N],st[20][N];
void newnode(int w) {
    val[++cnt] = w;
}
void addedge(int u, int v) {
    to[tot] = v;nxt[tot] = head[u];head[u] = tot++;
} 
void dfs(int u, int dep) {
    fir[u] = ++dfn_num;
    id[dfn_num] = u;
    depth[dfn_num] = dep;
    //debug(u,depth[dfn_num]);
    for(int i = head[u]; ~i; i = nxt[i]) {
        int v = to[i];
        if(fir[v]) continue;
        dfs(v,dep + 1);
        id[++dfn_num] = u;
        depth[dfn_num] = dep;
    }
}
int LCA(int x, int y) {
    int l = fir[x],r = fir[y];
    if(l > r) swap(l,r);
    int tt = log_2[r - l + 1];
    if(depth[st[tt][l]] <= depth[st[tt][r - (1 << tt) + 1]]) return id[st[tt][l]];
    else return id[st[tt][r - (1 << tt) + 1]];
}
void solve() {
    memset(head,-1,sizeof head);
    cin>>n>>m;
    cnt = n;
    for(int i = 1; i <= 2 * n; i++) fa[i] = i; 
    for(int i = 1; i <= m; i++) {
        int u,v,w;
        cin>>u>>v>>w;
        e[i].u = u;e[i].v = v;e[i].w = w;
    }
    sort(e + 1,e + 1 + m);
    for(int i = 1; i <= m; i++) {
        int x = e[i].u,y = e[i].v,w = e[i].w;
        int fax = find(x),fay = find(y);
        if(fax != fay) {
            newnode(w); // 给边建一个结点
            addedge(fax,cnt);
            addedge(fay,cnt);
            addedge(cnt,fax);
            addedge(cnt,fay);
            merge(fax,cnt);merge(fay,cnt); //保证每个并查集的根为边结点
        }
    } 
    dfs(cnt,0); // cnt为根
    log_2[1] = 0;
    for(int i = 2; i <= dfn_num; i++) log_2[i] = log_2[i / 2] + 1; 
    for(int i = 1; i <= dfn_num; i++) st[0][i] = i;
    for(int i = 1; i <= log_2[dfn_num]; i++) {
        for(int j = 1; j + (1 << i) - 1 <= dfn_num; j++) {
            int x = st[i - 1][j],y = st[i - 1][j + (1 << (i - 1))];
            if(depth[x] <= depth[y]) st[i][j] = x;
            else st[i][j] = y;
        }
    }
    int q;
    ull a1,a2;
    cin>>q>>a1>>a2;
    LL res = 0 ;
    for(int i = 1; i <= q; i++) {
        auto tmp = myRanq(a1,a2,n);
        int x = tmp.first,y = tmp.second;
        //debug(x,y,LCA(x,y));
        res ^= val[LCA(x,y)];
    }
    cout<<res<<endl;

}

/*
0 1  0 2 
*/