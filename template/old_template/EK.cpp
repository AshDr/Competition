#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e3 + 10;
const int M = 1e4 + 10;
int n,m,s,t;
int to[M],nxt[M],wei[M],head[N],tot;
int q[N],pre[N],dis[N],vis[N];
void addedge(int x,int y,int z) {
	to[tot] = y;
	wei[tot] = z;
	nxt[tot] = head[x];
	head[x] = tot++;
}
bool bfs() {
	int hh = 0,tt = 0;
	memset(vis,0,sizeof vis);
	q[0] = s;vis[s] = 1;dis[s] = 1e9;
	while(hh <= tt) {
		int u = q[hh++];
		for(int i = head[u]; ~i;i = nxt[i]) {
			int v = to[i];
			if(!vis[v] && wei[i] > 0) {
				vis[v] = 1;
				dis[v] = min(wei[i],dis[u]);
				pre[v] = i;
				if(v == t) return true;
				q[++tt] = v;
			}
		}
	}
	return false;
}
LL EK() {
	LL res = 0;
	while(bfs()) {
		res += dis[t];
		for(int i = t; i != s; i = to[pre[i] ^ 1]) {
			wei[pre[i]] -= dis[t];
			wei[pre[i] ^ 1] += dis[t];		
		}
	}
	return res;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin>>n>>m>>s>>t;
	memset(head,-1,sizeof head);
	for(int i = 1; i <= m; i++) {
		int x,y,z;
		cin>>x>>y>>z;
		addedge(x,y,z);
		addedge(y,x,0);
	}
	cout<<EK()<<endl;
	return 0;
}