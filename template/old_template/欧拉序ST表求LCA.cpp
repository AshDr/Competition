	// O(1) LCA
	#include<bits/stdc++.h>
#define cerr cout<<"#case:"
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
const int N = 2e6 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const LL MOD = 1e9 + 7;
int T,n,m,rt;
int log_2[N];
int head[N],nxt[N << 1],to[N << 1],tot;
int fir[N],id[N],depth[N],dfn;
int st[20][N];
void addedge(int u, int v) {
	to[tot] = v;nxt[tot] = head[u];head[u] = tot++;
} 
void dfs(int u, int dep) {
	fir[u] = ++dfn;
	id[dfn] = u;
	depth[dfn] = dep;
	for(int i = head[u]; ~i; i = nxt[i]) {
		int v = to[i];
		if(fir[v]) continue;
		dfs(v,dep + 1);
		id[++dfn] = u;
		depth[dfn] = dep;
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
  	cin>>n>>m>>rt;
  	
  	int u,v;
  	for(int i = 1; i <= n - 1; i++) {
  		cin>>u>>v;
  		addedge(u,v);
  		addedge(v,u);
  	}
  	dfs(rt,0);  	
  	log_2[1] = 0;
  	for(int i = 2; i <= dfn; i++) log_2[i] = log_2[i / 2] + 1;

  	for(int i = 1; i <= dfn; i++) st[0][i] = i; //st记depth最小的 dfn序号
  	for(int i = 1; i <= log_2[dfn]; i++) {
  		for(int j = 1; j + (1 << i) - 1 <= dfn; j++) {
  			int x = st[i - 1][j],y = st[i - 1][j + (1 <<(i - 1))];
  			if(depth[x] <= depth[y]) st[i][j] = x;
  			else st[i][j] = y;
  		}
  	}
  	for(int i = 1; i <= m ;i++) {
  		int x,y;
  		cin>>x>>y;
  		cout<<LCA(x,y)<<'\n';
  	}
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  //cin>>T;
  T = 1;
  while(T--) solve();
  return 0;
}