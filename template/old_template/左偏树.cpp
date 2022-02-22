#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n;
int l[N],r[N],dist[N],fa[N],tot,val[N];
int find(int x) {
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}
bool cmp(int x, int y) {
	if(val[x] != val[y]) return val[x] < val[y];
	return x < y;
}
int merge(int x, int y) {
	if(!x || !y) return x + y;
	if(cmp(y,x)) swap(x,y);
	r[x] = merge(r[x],y);
	if(dist[r[x]] > dist[l[x]]) swap(l[x],r[x]);
	dist[x] = dist[r[x]] + 1;
	return x;
}
//每个并查集的根 存的就是左偏树的堆顶
int main() {
    val[0] = 2e9;//特殊处理根节点
	scanf("%d",&n);
	for(int i = 1; i <= n; i++) {
		int op,x,y;
		scanf("%d%d",&op,&x);
		if(op == 1) {
			val[++tot] = x;
			dist[tot] = 1;
			fa[tot] = tot;
		}
		else if(op == 2) {
			scanf("%d",&y);
			x = find(x),y = find(y);
			if(x != y) {
				if(cmp(y,x)) swap(x,y);
				fa[y] = x;
				merge(x,y);
			}
		}
		else if(op == 3) printf("%d\n",val[find(x)]);
		else {
			x = find(x);
			if(cmp(r[x],l[x])) swap(l[x],r[x]);
			fa[x] = l[x];fa[l[x]] = l[x];//并查集换根操作
			merge(l[x],r[x]);
		}
	}
	return 0;
}