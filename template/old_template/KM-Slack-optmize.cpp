
// KM - SLACK -OPTIMZE
#include<bits/stdc++.h>
//#define cerr cout<<"#case:"
#define LOG(FMT...) fprintf(stderr, FMT)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
const int N = 5e2 + 10;
const int M = 1e5 + 10;
const LL INF = 1e18;
const LL MOD = 1e9 + 7;
int T,n,m;
LL G[N][N];
bool vx[N],vy[N];
LL lx[N],ly[N],slack[N];
int matchy[N],matchx[N],pre[N];
int d;
void recall(int x) {
    int t;
    while(x) {
        t = matchx[pre[x]];
        matchx[pre[x]] = x;
        matchy[x] = pre[x];
        x = t; 
    }
}
void bfs(int s) {
    queue<int> q;
    memset(vx,0,sizeof vx);
    memset(vy,0,sizeof vy);
    memset(pre,0,sizeof pre);
    fill(slack + 1,slack + 1 + n,INF);
    q.push(s);
    while(1) {
        while(!q.empty()) {
            int u = q.front();q.pop();
            vx[u] = 1;
            for(int i = 1; i <= n; i++) {
                if(!vy[i]) {
                        if(lx[u] + ly[i] - G[u][i] < slack[i]) {
                            slack[i] = lx[u] + ly[i] - G[u][i];
                            pre[i] = u;
                        if(slack[i] == 0) {
                            vy[i] = 1;
                            if(matchy[i] == 0) {recall(i);return ;}
                            else q.push(matchy[i]);
                        }
                    }
                }
            } 
        }
        LL d = INF;
        for(int i = 1; i <= n; i++) if(!vy[i]) d = min(d,slack[i]);
        for(int i = 1; i <= n; i++) {
            if(vx[i]) lx[i] -= d;
            if(vy[i]) ly[i] += d;else slack[i] -= d;
        }
        for(int i = 1; i <= n; i++) {
            if(!vy[i]) {
                if(slack[i] == 0) {
                    vy[i] = 1;
                    if(matchy[i] == 0) {recall(i);return;}
                    else q.push(matchy[i]); 
                }
            }
        } 
    }
}
void KM() {
    fill(lx + 1,lx + 1 + n,-INF);
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            lx[i] = max(G[i][j],lx[i]);
        }
    }
    for(int i = 1; i <= n; i++) bfs(i);
}
void solve() {
    cin>>n>>m;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            G[i][j] = -INF;
        }
    }
    for(int i = 1; i <= m; i++) {
        LL u,v,w;
        cin>>u>>v>>w;
        G[u][v] = max(G[u][v],w); // 不能建两遍 因为只有左部点入队
    }
    KM();
    LL res = 0;
    for(int i = 1; i <= n; i++) if(matchy[i]) res += G[matchy[i]][i];
    cout<<res<<'\n';
    for(int i = 1; i <= n; i++) if(matchy[i]) cout<<matchy[i]<<' '; 
}
