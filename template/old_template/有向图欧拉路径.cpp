#include<bits/stdc++.h>
//#define cerr cout<<"#case:"
#define LOG(FMT...) fprintf(stderr, FMT)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
const int N = 5e2 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const LL MOD = 1e9 + 7;
int TT,n,m;
void dbg_out() { cerr << "\b\b )" << endl; }
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T){cerr << H << ", ";dbg_out(T...);}
#define debug(...) cerr << "( " << #__VA_ARGS__ << " ) = ( ", dbg_out(__VA_ARGS__)
//LL fac[N],inv[N];
LL gcd(LL x, LL y) {return y == 0 ? x : gcd(y, x % y);}
int G[N][N];
int deg[N];
stack<int> stk;
void dfs(int u) {
    for(int i = 1; i <= 500; i++) { //当前弧优化
        if(G[u][i]) {
            G[u][i]--;
            G[i][u]--;
            dfs(i);
        }
    }
    stk.push(u);
}
void solve() {
    cin>>m;
    for(int i = 1; i <= m; i++) {
        int u,v;
        cin>>u>>v;
        G[u][v]++;
        G[v][u]++;
        deg[u]++;deg[v]++;
    }
    int flag = 1;
    int start = 1,cnt = 0;
    for(int i = 500; i >= 1; i--) {
        if(deg[i] & 1) start = i,++cnt;
    }
    if(!flag && !(cnt == 2)) cout<<"No"<<'\n';
    else {
        dfs(start);
        while(!stk.empty()) cout<<stk.top()<<'\n',stk.pop();
    }
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