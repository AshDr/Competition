//对点
//如果是对边的剖分，记得先将权值存到下方节点，再build，且build范围是2~n，同时修改所有线段树的操作范围注意，注意特判n==1
namespace HLD{
	const int N = 2e5 + 10;
	struct node {
		int lztag,mx;
	}tr[N<<2];
	#define lt idx<<1
	#define rt idx<<1|1
	int tot,siz[N],depth[N],son[N],dfn[N],top[N],fa[N],id[N];
	vector<int> G[N];
	void dfs1(int u) {
		siz[u]=1;
		for(auto v: G[u]) {
			if(v==fa[u]) continue;
			depth[v]=depth[u]+1;
			fa[v]=u;
			dfs1(v);
			if(siz[v]>siz[son[u]]) son[u]=v;
			siz[u]+=siz[v];
		}
	}
	void dfs2(int u,int tp){
		dfn[u]=++tot;
		id[tot]=u;
		top[u]=tp;
		if(son[u]) dfs2(son[u],tp);
		for(auto v:G[u]) {
			if(v==son[u]||v==fa[u]) continue;
			dfs2(v,v);
		}
	}

	void push_down(int idx) {
	    if(tr[idx].lztag) {
	    	//TODO
	    }
	}
	void push_up(int idx) {
	    //TODO
	}
	void build(int idx, int L, int R) {
		if(L == R) {
			//TODO
			return;
		}
		int mid=(L+R)>>1;
		build(lt, L, mid);
		build(rt, mid+1, R);
		push_up(idx);
	}
	void modify(int idx, int l, int r, int val, int L, int R) {
		if(l<=L && r>=R) {
			//TODO
			return ;
		}
		push_down(idx);
		int mid = (L+R)>>1;
		if(l<=mid) modify(lt, l, r, val, L, mid);
		if(r>mid) modify(rt, l, r, val, mid+1, R);
		push_up(idx);
	}
	int query(int idx, int l, int r, int L, int R) {
		if(l<=L && r>=R) {
			//TODO
		}
		int res = 0;
		push_down(idx);
		int mid = (L+R)>>1;
		if(l<=mid) res+=query(lt, l, r, L, mid);
		if(r>mid) res+=query(rt, l, r, mid+1, R);
		return res;
	}
	void path_modify(int x, int y, int val) {
		while(top[x]!=top[y]) {
			if(depth[top[x]]<depth[top[y]]) swap(x,y);
			modify(1, dfn[top[x]], dfn[x], val, 1, tot);
			x=fa[top[x]];
		}
		if(depth[x]>depth[y]) swap(x,y);
		modify(1, dfn[x], dfn[y], val, 1, tot);
		//modify(1,dfn[son[x]],dfn[y],val,2,tot);
	}
	int path_query(int x, int y) {
		ll res=0;
		while(top[x]!=top[y]) {
			if(depth[top[x]]<depth[top[y]]) swap(x,y);
			res += query(1, dfn[top[x]], dfn[x], 1, tot);
			x=fa[top[x]];
		}
		if(depth[x]>depth[y]) swap(x,y);
		res += query(1, dfn[x], dfn[y], 1, tot);
		//query(1,dfn[son[x]],dfn[y],val,2,tot);
		return res;
	}
}