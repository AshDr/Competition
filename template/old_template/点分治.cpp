#include<bits/stdc++.h>
#define cerr cout<<"#case:"
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
const int N = 1e4 + 10;
const int M = 1e7 + 10;
const int INF = 2147483647;
const LL MOD = 1e9 + 7;
int T,n,m,rt;
int tot,head[N],nxt[N << 1],to[N << 1],wei[N << 1];
int cnt;
int vis[N],d[N],sz[N];
int tong[M],ans[M],cler[N];
int maxpart;
vector<int> q;
void addedege(int u,int v,int w) {
	to[tot] = v;wei[tot] = w;nxt[tot] = head[u];head[u] = tot++;
} 
void find_rt(int u, int fa,int totsz) {
	sz[u] = 1;
	int val = 0;
	for(int i = head[u]; ~i; i = nxt[i]) {
		int v = to[i];
		if(vis[v] || v == fa) continue;
		find_rt(v,u,totsz);
		sz[u] += sz[v]; 
		val = max(val,sz[v]);
	}
	val = max(val,totsz - sz[u]);
	if(val < maxpart) maxpart = val,rt = u;
} 
void get_dis(int u, int fa,int dis) {
	for(int i = head[u]; ~i; i = nxt[i]) {
		int v = to[i],w = wei[i];
		if(vis[v] || v == fa) continue;
		d[++cnt] = dis + w;
		get_dis(v,u,dis + w);
	}
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
void calc(int u) {
	int tt = 0;maxpart = 1e9;rt = 0;
	find_rt(u,0,get_sz(u,0));
	vis[rt] = 1;
	//cout<<rt<<'\n';
	for(int i = head[rt]; ~i; i = nxt[i]) {
		int v = to[i];
		if(vis[v]) continue;
		cnt = 0;d[++cnt] = wei[i];get_dis(v,u,wei[i]);
		for(int j = 0; j < m; j++) {
			int qq = q[j];
			for(int k = 1; k <= cnt; k++) if(qq - d[k] >= 0 && qq - d[k] <= 1e7 && tong[qq - d[k]]) ans[qq] = 1;
		}
		for(int k = 1; k <= cnt; k++) if(d[k] <= 1e7) cler[++tt] = d[k],tong[d[k]] = 1;
	}
	for(int i = 1; i <= tt; i++) tong[cler[i]] = 0;
	for(int i = head[rt]; ~i; i = nxt[i]) if(!vis[to[i]]) calc(to[i]);
}
void solve() {
    cin>>n>>m;
    int u,v,w;
    memset(head,-1,sizeof head);
    for(int i = 1; i <= n - 1;i++) {
    	cin>>u>>v>>w;
    	addedege(u,v,w);
    	addedege(v,u,w);	
    }
    int t;
    for(int i = 1; i <= m; i++) cin>>t,q.push_back(t);
    tong[0] = 1;
    calc(1);
	for(int i = 0; i < m; i++) cout<<(ans[q[i]] == 1 ?"AYE\n":"NAY\n");
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  freopen("data.in","r",stdin);
  freopen("brut.out","w",stdout);
  //cin>>T;
  T = 1;
  while(T--) solve();
  return 0;
}
/*
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 100010, M = N * 2;

int n, m;
int h[N], e[M], w[M], ne[M], idx;
bool st[N];
int p[N], q[N];

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

int get_size(int u, int fa)  // 求子树大小
{
    if (st[u]) return 0;
    int res = 1;
    for (int i = h[u]; ~i; i = ne[i])
        if (e[i] != fa)
            res += get_size(e[i], u);
    return res;
}

int get_wc(int u, int fa, int tot, int& wc)  // 求重心
{
    if (st[u]) return 0;
    int sum = 1, ms = 0;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (j == fa) continue;
        int t = get_wc(j, u, tot, wc);
        ms = max(ms, t);
        sum += t;
    }
    ms = max(ms, tot - sum);
    if (ms <= tot / 2) wc = u;
    return sum;
}

void get_dist(int u, int fa, int dist, int& qt)
{
    if (st[u]) return;
    q[qt ++ ] = dist;
    for (int i = h[u]; ~i; i = ne[i])
        if (e[i] != fa)
            get_dist(e[i], u, dist + w[i], qt);
}

int get(int a[], int k)
{
    sort(a, a + k);
    int res = 0;
    for (int i = k - 1, j = -1; i >= 0; i -- )
    {
        while (j + 1 < i && a[j + 1] + a[i] <= m) j ++ ;
        j = min(j, i - 1);
        res += j + 1;
    }
    return res;
}

int calc(int u)
{
    if (st[u]) return 0;
    int res = 0;
    get_wc(u, -1, get_size(u, -1), u);
    st[u] = true;  // 删除重心

    int pt = 0;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i], qt = 0;
        get_dist(j, -1, w[i], qt);
        res -= get(q, qt);
        for (int k = 0; k < qt; k ++ )
        {
            if (q[k] <= m) res ++ ;
            p[pt ++ ] = q[k];
        }
    }
    res += get(p, pt);

    for (int i = h[u]; ~i; i = ne[i]) res += calc(e[i]);
    return res;
}

int main()
{
    scanf("%d", &n);
    memset(st, 0, sizeof st);
    memset(h, -1, sizeof h);
    idx = 0;
        for (int i = 0; i < n - 1; i ++ )
        {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            add(a, b, c), add(b, a, c);
        }
    scanf("%d",&m);    
        printf("%d\n", calc(1));

    return 0;
}

*/