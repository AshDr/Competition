// 1.调试可能会爆栈
// 2.权值seg开子树大小会优化常数一点
// 3.欧拉序求ST表开二倍
// 4.点分树每个节点开两个权值seg，进行容斥
// 询问距离<=k的val sum      修改单点
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 2e5 + 10;
struct val_seg_tree {
    int ls,rs;
    int sum;
}tr[10000000];

int n,m,tot;
int head[N],nxt[N],to[N];
int a[N];
int S,rt,sz[N],mxpart,vis[N];
int cnt,RT1[N],RT2[N],divfa[N];
int st[20][N],fir[N],depth[N],id[N],log_2[N],dfn_num;// LCA


void dbg_out(){cerr<<"\b\b )"<<endl;}
template <typename Head,typename... Tail>
void dbg_out(Head H,Tail... T) {cerr<<H<<", ";dbg_out(T...);}
#define debug(...) cerr<<"("<<#__VA_ARGS__<<") = (",dbg_out(__VA_ARGS__)

void addedge(int u, int v) {to[tot] = v;nxt[tot] = head[u];head[u] = tot++;}
void update(int &cur, int L, int R,int pos,int val) {
    if(!cur) cur = ++cnt;
    tr[cur].sum += val;
    if(L == R) return ;
    int mid = (L + R) >> 1;
    if(pos <= mid) update(tr[cur].ls,L,mid,pos,val);
    else update(tr[cur].rs,mid + 1,R,pos,val);
}
LL query(int cur, int L,int R,int l,int r) {
    if(!cur) return 0;
    if(l <= L  && r >= R) return tr[cur].sum;
    int mid = (L + R) >> 1;
    LL res = 0;
    if(l <= mid) res += query(tr[cur].ls,L,mid,l,r);
    if(r > mid) res += query(tr[cur].rs,mid + 1,R,l,r);
    return res;
}
void get_rt(int u,int fa) {
    sz[u] = 1;
    int val = 0;
    for(int i = head[u]; ~i; i = nxt[i]) {
        int v = to[i];
        if(vis[v] || v == fa) continue;
        get_rt(v,u);
        sz[u] += sz[v];
        val = max(val,sz[v]);
    }
    val = max(val,S - sz[u]);
    if(val < mxpart) rt = u,mxpart = val; 
}
int get_sz(int u,int fa) {
    int res = 1;
    for(int i = head[u]; ~i; i = nxt[i]) {
        int v = to[i];
        if(vis[v] || v == fa) continue;
        res += get_sz(v,u);
    }
    return res;
}
void dfs1(int u,int dep) {
    fir[u] = ++dfn_num;
    depth[dfn_num] = dep;
    id[dfn_num] = u;
    for(int i = head[u]; ~i; i = nxt[i]) {
        int v = to[i];
        //debug(v);
        if(fir[v]) continue;
        dfs1(v,dep + 1);
        depth[++dfn_num] = dep;
        id[dfn_num] = u;
    }
}
void get_st() {
    log_2[1] = 0;
    for(int i = 2; i <= dfn_num; i++) log_2[i] = log_2[i / 2] + 1;
    for(int i = 1; i <= dfn_num; i++) st[0][i] = i;
    for(int i = 1; i <= log_2[dfn_num]; i++) {
        for(int j = 1; j + (1 << i) <= dfn_num; j++) {
            int x = st[i - 1][j],y = st[i - 1][j + (1 << (i - 1))];
            if(depth[x] <= depth[y]) st[i][j] = x;
            else st[i][j] = y;
        }
    }
}   
int LCA(int x, int y) {
    x = fir[x],y = fir[y];
    if(x > y) swap(x,y);
    int len = log_2[y - x + 1];
    int t1 = st[len][x],t2 = st[len][y - (1 << len) + 1];
    if(depth[t1] <= depth[t2]) return id[t1];
    else return id[t2];
}
int get_dis(int x , int y) {
    int lca = LCA(x,y);
    x = fir[x],y = fir[y],lca = fir[lca];
    return depth[x] + depth[y] - 2 * depth[lca];
}
void build_div_tree(int u,int fa) {
    mxpart = 1e9;rt = 0;
    S = get_sz(u,-1);
    get_rt(u,-1);
    //debug(rt,fa);
    divfa[rt] = fa;
    vis[rt] = 1;
    int tmp = rt; //注意这里要记一下 不然rt会变
    for(int i = head[rt]; ~i; i = nxt[i]) if(!vis[to[i]])  build_div_tree(to[i],tmp);
}
void Modify(int idx,int val) {
    int cur = idx;
    while(cur) {
        //debug(cur);
        int fa = divfa[cur];

        update(RT1[cur],0,n,get_dis(idx,cur),val);
        if(fa) update(RT2[cur],0,n,get_dis(idx,fa),val); //父亲对自己的容斥用自己这里的T2权值segtr记录
        cur = fa;

    }
}   
void init_div_tree() {for(int i = 1; i <= n; i++) Modify(i,a[i]);}
LL Query(int x,int k) {
    int pre = 0,cur = x;LL res = 0;
    while(cur) {
        int dis = get_dis(x,cur);
        if(dis <= k) {
            res += query(RT1[cur],0,n,0,k - get_dis(x,cur));
            if(pre) res -= query(RT2[pre],0,n,0,k - get_dis(x,cur));    //容斥
        }
        pre = cur;
        cur = divfa[cur];
    }
    return res;
}
int main() {
    //freopen("data.in","r",stdin);
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    memset(head,-1,sizeof head);

    cin>>n>>m;
    for(int i = 1; i <= n; i++) cin>>a[i];
    for(int i = 1; i <= n - 1; i++) {
        int u,v;
        cin>>u>>v;
        addedge(u,v);
        addedge(v,u);
    }
    dfs1(1,0);
    
    get_st();

    build_div_tree(1,0);
    
    init_div_tree();
    int lst = 0;
    for(int i = 1; i <= m; i++) {
        int op,x,y;
        cin>>op>>x>>y;
        x ^= lst;y ^= lst;
        if(op == 0) {
            lst = Query(x,y); 
            cout<<lst<<endl;
        }
        else Modify(x,-a[x]),Modify(x,y),a[x] = y;
    }
    return 0;
}   