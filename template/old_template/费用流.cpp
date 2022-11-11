
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
int tot,head[N],nxt[M << 1],to[M << 1],cc[M << 1],cost[M << 1];
int q[N],hh,tt;
int path[N],flow[N],vis[N];
LL dis[N];
int p,f,nn,s;
void addedge(int u, int v, int w, int c) {
    to[tot] = v;cc[tot] = w;cost[tot] = c;nxt[tot] = head[u];head[u] = tot++;
    to[tot] = u;cc[tot] = 0;cost[tot] = -c;nxt[tot] = head[v];head[v] = tot++;
}
bool spfa() {
    hh = 0,tt = 1;
    memset(vis,0,sizeof vis);
    memset(dis,0x3f,sizeof dis); //因为要求最小费用流
    memset(flow,0,sizeof flow);
    q[0] = S;flow[S] = INF;dis[S] = 0;
    while(hh != tt) {
        int u = q[hh++];
        //debug(u);
        vis[u] = 0;
        if(hh == N) hh = 0; //循环队列
        for(int i = head[u]; ~i; i = nxt[i]) {
            int v = to[i];
            if(dis[v] > dis[u] + cost[i] && cc[i] > 0) {
                dis[v] = dis[u] + cost[i];
                flow[v] = min(flow[u],cc[i]);
                path[v] = i;
                if(!vis[v]) {
                    vis[v] = 1;
                    q[tt++] = v;
                    if(tt == N) tt = 0;
                }
            }
        }
    }
    return flow[T] > 0; //有增广路
}
LL EK() {
    LL mxflow = 0,mncost = 0;
    while(spfa()) {
        LL t = flow[T];
        //debug(t);
        mxflow += t;
        mncost += t * dis[T];
        for(int i = T; i != S; i = to[path[i] ^ 1]) {
            cc[path[i]] -= t;
            cc[path[i] ^ 1] += t; 
        }
    }
    return mncost;
}
void solve() {
    memset(head,-1,sizeof head);
    cin>>n;
    S = 0,T = 2 * n + 1;
    for(int i = 1; i <= n; i++) {
        int r;
        cin>>r;
        addedge(S,i,r,0); //当天的旧毛巾 视为S提供
        addedge(i + n,T,r,0); // 每天开始点连向汇点 表示提供r[i] 
    }
    cin>>p>>m>>f>>nn>>s;
    for(int i = 1; i <= n; i++) {
        addedge(S,i + n,INF,p); //每天购买新毛巾
        if(i < n) addedge(i,i + 1,INF,0); // 旧毛巾运到第二天旧毛巾
        if(i + m <= n) addedge(i,i + m + n,INF,f); //  快洗后送到每天开始
        if(i + nn <= n) addedge(i,i + nn + n,INF,s);// 慢洗
    }
    cout<<EK()<<'\n';
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