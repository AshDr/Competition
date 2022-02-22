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
LL lx[N],ly[N];
int matchy[N];
LL d;
bool dfs(int u) {
    vx[u] = 1;// !
    for(int i = 1; i <= n; i++) {
        if(!vy[i]) {
            if(lx[u] + ly[i] == G[u][i]) {
                vy[i] = 1;
                if(!matchy[i] || dfs(matchy[i])) {
                    matchy[i] = u;
                    return true;
                }
            }
            else d = min(d,lx[u] + ly[i] - G[u][i]);
        }
       
    }
    return false;
}
void KM() {
    fill(lx + 1,lx + 1 + n,-INF); // negiative W

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            lx[i] = max(G[i][j],lx[i]);
        }
    }
    for(int i = 1; i <= n; i++) {      
        while(1) {
            memset(vx,0,sizeof vx);
            memset(vy,0,sizeof vy);
            d = 2e9;
            if(dfs(i)) break;
            for(int j = 1; j <= n; j++) {
                if(vx[j]) lx[j] -= d;
                if(vy[j]) ly[j] += d;
            }
        }
    }  
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
        G[u][v] = max(G[u][v],w);
    }
    KM();
    LL res = 0;
    for(int i = 1; i <= n; i++) if(matchy[i]) res += G[matchy[i]][i];
    cout<<res<<'\n';
    for(int i = 1; i <= n; i++) if(matchy[i]) cout<<matchy[i]<<' ';
}
