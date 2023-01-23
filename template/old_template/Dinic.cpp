#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e4 + 10;
const int M = 2e5 + 10;
const int INF = 1e9;
int n,m,S,T;
int head[N],to[M],nxt[M],wei[M],tot;//wei is the rest of flow
int d[N],skip[N],q[N];
void addedge(int x, int y, int z) {
	to[tot] = y;wei[tot] = z;nxt[tot] = head[x];head[x] = tot++;
}
bool bfs() {
	memset(d,-1,sizeof d);
	int hh = 0 , tt = 0;
	q[0] = S;d[S] = 0;skip[S] = head[S];
	while(hh <= tt) {
		int u = q[hh++];
		for(int i = head[u]; ~i;  i = nxt[i]) {
			int v = to[i];
			if(d[v] == -1 && wei[i] > 0) {
				d[v] = d[u] + 1;
				skip[v] = head[v];
				if(v == T) return true;
				q[++tt] = v;
			}
		}
	}
	return false;
}
int find(int u, int limit) {
	if(u == T) return limit;
	int flow = 0;
	for(int i = skip[u]; ~i && flow < limit; i = nxt[i]) {
		skip[u] = i;
		int v = to[i];
		if(d[v] == d[u] + 1 && wei[i] > 0) {
			int tmp = find(v,min(wei[i],limit - flow));//从v向后走且总流量不超过limit限制的最大流量
			if(!tmp) d[v] = -1;
			wei[i] -= tmp,wei[i ^ 1] += tmp,flow += tmp;
		}
	}
	return flow;
}
LL Dinic() {
	int res = 0,tmp;
	while(bfs()) while(tmp = find(S,INF)) res += tmp;
	return res;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin>>n>>m>>S>>T;
	memset(head,-1,sizeof head);
	for(int i = 1; i <= m; i++) {
		int x,y,z;		
		cin>>x>>y>>z;
		addedge(x,y,z);
		addedge(y,x,0);
	}
	cout<<Dinic()<<endl;
	return 0;
}