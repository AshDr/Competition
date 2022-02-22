// 线段树优化建图
#include<bits/stdc++.h>
//#define cerr cout<<"#case:"
#define lt (i<<1)
#define rt (i<<1|1)
#define LOG(FMT...) fprintf(stderr, FMT)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
const int N = 1e6 + 10;
const int M = 1e5 + 10;
const LL INF = 1e18;
const LL MOD = 1e9 + 7;
int T,n,m;
struct node {
    int l,r;
}tr[N];
vector<pii> g[N];
int leaf[N];
LL dis[N];
const int D = 5e5+10;
void build(int i,int l, int r) {
    tr[i].l = l;tr[i].r = r;
    if(l == r) {
        leaf[l] = i;
        return ;
    }
    int mid = (l + r) >> 1;
    g[i].push_back({lt,0});
    g[i].push_back({rt,0});
    g[lt + D].push_back({i + D,0});
    g[rt + D].push_back({i + D,0});
    build(lt,l,mid);
    build(rt,mid + 1,r);
}
void connect(int i, int l, int r, int ver,int w,int op) {
    if(l <= tr[i].l && r >= tr[i].r) {
        if(op == 2) g[leaf[ver] + D].push_back({i,w});
        else g[i + D].push_back({leaf[ver],w});
        return ;
    }
    if(tr[lt].r >= l) connect(lt,l,r,ver,w,op);
    if(tr[rt].l <= r) connect(rt,l,r,ver,w,op);
}
int s;
void solve() {
    cin>>n>>m>>s;
    build(1,1,n);
    for(int i = 1; i <= m; i++) {
        int op;
        cin>>op;
        if(op == 1) {
            int u,v,w;
            cin>>u>>v>>w;
            g[leaf[u]].push_back({leaf[v],w});
        }
        else {
            int u,l,r,w;
            cin>>u>>l>>r>>w;
            connect(1,l,r,u,w,op);
        }
    }
    for(int i = 1; i <= n; i++) g[leaf[i]].push_back({leaf[i] + D,0}),g[leaf[i] + D].push_back({leaf[i],0});
    fill(dis + 1,dis + N,INF);
    priority_queue<pii,vector<pii>,greater<pii>> pq;
    dis[leaf[s]] = 0;
    pq.push({0,leaf[s]});
    while(!pq.empty()) {
        auto cur = pq.top();pq.pop();
        int u = cur.second;
        for(int i = 0; i < (int)g[u].size(); i++) {
            int v = g[u][i].first,w = g[u][i].second;
            if(dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                pq.push({dis[v],v});
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        if(dis[leaf[i]] == INF) cout<<-1<<' ';
        else cout<<dis[leaf[i]]<<' ';
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
  //cin>>T;
  T = 1;
  while(T--) solve();
  #ifdef ASHDR
    LOG("Time: %dms\n", int ((clock()
          -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
  #endif
  return 0;
}