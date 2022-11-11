// 圆方树
#include<bits/stdc++.h>
//#define cerr cout<<"#case:"
#define LOG(FMT...) fprintf(stderr, FMT)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
const int N = 1e3 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const LL MOD = 1e9 + 7;
int T,n,m;
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
    for (int i = 1; i < v.size(); ++i)
      os << ' ' << v[i];
  }
  return os;
}
void dbg_out() { cerr << "\b\b )" << endl; }
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T){cerr << H << ", ";dbg_out(T...);}
#define debug(...) cerr << "( " << #__VA_ARGS__ << " ) = ( ", dbg_out(__VA_ARGS__)
//LL fac[N],inv[N];
LL gcd(LL x, LL y) {return y == 0 ? x : gcd(y, x % y);}
LL qpow(LL base, LL x) {
  LL res = 1;
  while(x) {
    if(x & 1) res = (res * base) % MOD;
    base = (base * base) % MOD;
    x >>= 1;
  }
  return res;
}
LL MOD_sub(LL x,LL y) {
    return ((x - y) % MOD + MOD) %MOD;
}
LL MOD_add(LL x, LL y) {
    return ((x + y) % MOD + MOD) % MOD;
}
int counter = 0,cnt;
int fa[N],instk[N];
int dfn[N],low[N],dfn_num;
int deg[N];
int rt;
vector<int> adj[N],adjs[N];
stack<int> stk;
void Tarjan(int u) {
    dfn[u] = low[u] = ++dfn_num;
    stk.push(u);instk[u] = 1;
    for(auto v : adj[u]) {
        if(!dfn[v]) {
            fa[v] = u;
            Tarjan(v);
            low[u] = min(low[u],low[v]);
            if(dfn[u] <= low[v]) {
                ++cnt; // 方点标号
                while(1) {
                    int x = stk.top();stk.pop();
                    instk[x] = 0;
                    adjs[cnt].push_back(x);
                    adjs[x].push_back(cnt); // 方点与圆点连边
                    deg[x]++;deg[cnt]++; // 度数>1的圆点就是割点
                    if(x == v) break; // Warn 不能把u pop掉
                }// 建圆方树,就不用特判rt了 因为如果rt有>1个数量的子树，那么就会向多个对应的方点连边，自动就变成了一个割点
                adjs[u].push_back(cnt);
                adjs[cnt].push_back(u);
                deg[u]++;deg[cnt]++;
            }
        }
        else if(v != fa[u]) low[u] = min(low[u],dfn[v]); 
    }
}
void init() {
    dfn_num = 0;
    while(!stk.empty()) stk.pop();
    memset(instk,0,sizeof instk);
    memset(low,0,sizeof low);
    memset(dfn,0,sizeof dfn);
    memset(deg,0,sizeof deg);
    for(int i = 1; i < N; i++) adj[i].clear();
    for(int i = 1; i < N; i++) adjs[i].clear();
}
void solve() {
   ++counter;
   if(!m) return ;
   init();
   set<int> s;
   for(int i = 1; i <= m; i++) {
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        s.insert(u);
        s.insert(v);
   }
   LL ans1 = 0,ans2 = 1;
   n = cnt = s.size();
   for(int i = 1; i <= n; i++) if(!dfn[i]) rt = i,Tarjan(i);
   //debug(cnt - n);
   for(int i = n + 1; i <= cnt; i++) {
        int cpnum = 0;
        for(auto v: adjs[i]) if(deg[v] > 1) ++cpnum; 
        int sz = adjs[i].size();
        if(cpnum == 0) {
            ans1 += 2;
            ans2 *= (sz - 1) * sz / 2;
        }
        else if(cpnum == 1) {
            ans1 += 1;
            ans2 *= (sz - 1);
        }
   }
    cout<<"Case "<<counter<<": "<<ans1<<" "<<ans2<<endl;
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
  while(1) {
    cin>>m;
    solve();
    if(m == 0) break;
  }
  #ifdef ASHDR
    LOG("Time: %dms\n", int ((clock()
          -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
  #endif
  return 0;
}