#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
struct Splay {
	int son[2],fa,val;
	int sum,rev;
}tree[N];
int n,m;
int stk[N];
void pushrev(int u) {
	swap(tree[u].son[0],tree[u].son[1]);
	tree[u].rev ^= 1;
}
void push_up(int u) {
	tree[u].sum = tree[tree[u].son[0]].sum  ^ tree[u].val ^ tree[tree[u].son[1]].sum;
} 
void push_down(int u) {
	if(tree[u].rev) {
		pushrev(tree[u].son[0]);pushrev(tree[u].son[1]);
		tree[u].rev = 0;
	}
}
bool isroot(int x) {
	if(tree[tree[x].fa].son[0] != x && tree[tree[x].fa].son[1] != x) return true;
	return false;
}//判断 splay 的根
void update(int u) {
	int top = 0;
	stk[++top] = u;
	while(!isroot(u)) {
	    stk[++top] = u = tree[u].fa;
	}//!!!
	while(top) push_down(stk[top--]);
}
void rotate(int x) {
	int y = tree[x].fa,z = tree[y].fa;
	int k = tree[y].son[1] == x;
	if(!isroot(y)) tree[z].son[tree[z].son[1] == y] = x; //!!!
	tree[x].fa = z;
	tree[y].son[k] = tree[x].son[k ^ 1];tree[tree[x].son[k ^ 1]].fa = y;
	tree[x].son[k ^ 1] = y;tree[y].fa = x;
	push_up(y);push_up(x);
}
void splay(int x) {
	update(x);
	while(!isroot(x)) {
		int y = tree[x].fa,z = tree[y].fa;
		if(!isroot(y)) {
			if((tree[z].son[1] == y) ^ (tree[y].son[1] == x)) rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
}
void access(int x) {
	int z = x;
	for(int p = 0 ;x; p = x,x = tree[x].fa) {
		splay(x);tree[x].son[1] = p;push_up(x);
	}
	splay(z);
}
void makeroot(int x) {
	access(x);
	pushrev(x);
}//原树的根
int findroot(int x) {
	access(x);
	while(tree[x].son[0]) push_down(x),x = tree[x].son[0];
	splay(x); // 把根转回去 做到了把x放在x根的右子树中
	return x; 
}//原树的根
void split(int x, int y) {
	makeroot(x);
	access(y);
	splay(y);
}
void link(int x, int y) {
	makeroot(x);
	if(findroot(y) != x) tree[x].fa = y; 
}
void cut(int x, int y) {
	makeroot(x);
	if(findroot(y) == x && tree[y].fa == x && !tree[y].son[0]) {//findroot的时候有门道 
		tree[x].son[1] = tree[y].fa = 0;
		push_up(x);
	}
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i = 1; i <= n; i++) scanf("%d",&tree[i].val);
	while(m--) {
		int op,x,y;
		scanf("%d%d%d",&op,&x,&y);
		if(op == 0) {
			split(x,y);
			printf("%d\n",tree[y].sum);
		}
		else if(op == 1) link(x,y);
		else if(op == 2) cut(x,y); 
		else {
			splay(x);
			tree[x].val = y;
			push_up(x);
		}
	}
	return 0;
}	