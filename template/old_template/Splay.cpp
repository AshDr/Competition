#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
struct Splay {
    int son[2];
    int sz,val,flag,fa;
    void init(int _val,int _fa) {
        val = _val;fa=_fa;
        sz = 1;
    } 
}tree[N];
int n,m,root,idx;
void push_up(int i) {
    tree[i].sz = tree[tree[i].son[0]].sz + tree[tree[i].son[1]].sz + 1;
} 
void push_down(int i) {
    if(tree[i].flag) {
        swap(tree[i].son[0],tree[i].son[1]);     
        tree[tree[i].son[0]].flag ^= 1;
        tree[tree[i].son[1]].flag ^= 1;
        tree[i].flag = 0;
    }
}
void rotate(int x) {
    int y = tree[x].fa,z = tree[y].fa;
    int k = tree[y].son[1] == x;
    tree[x].fa = z;tree[z].son[tree[z].son[1] == y] = x;
    tree[y].son[k] = tree[x].son[k ^ 1];tree[tree[x].son[k ^ 1]].fa = y;
    tree[x].son[k ^ 1] = y;tree[y].fa = x;
    push_up(y);
    push_up(x);
}
void splay(int x, int k) {
    while(tree[x].fa != k) {
        int y = tree[x].fa,z = tree[y].fa;
        if(z != k) {
            if((tree[y].son[1] == x) ^ (tree[z].son[1] == y)) rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
    if(!k) root = x;
}//把x旋转到k的下方   
void insert(int val) {
    int u = root,fa = 0;
    while(u) fa = u,u = tree[u].son[val > tree[u].val];
    u = ++idx;
    if(fa) tree[fa].son[val > tree[fa].val] = u;
    tree[u].init(val,fa);
    splay(u,0);
}
void print(int u) {
    push_down(u);
    if(tree[u].son[0]) print(tree[u].son[0]);
    if(tree[u].val >= 1 && tree[u].val <= n) printf("%d ",tree[u].val);
    if(tree[u].son[1]) print(tree[u].son[1]);
}
int get_k(int k) {
    int u = root;
    while(true) {
        push_down(u);
        if(tree[tree[u].son[0]].sz >= k) u = tree[u].son[0];
        else if(tree[tree[u].son[0]].sz + 1 == k) return u;
        else k -= tree[tree[u].son[0]].sz + 1,u = tree[u].son[1];
    }
    return -1;
}
int main() {
    scanf("%d%d",&n,&m);
    for(int i = 0; i <= n + 1; i++) insert(i);
    for(int i = 1; i <= m; i++) {
        int l,r;
        scanf("%d%d",&l,&r);
        l = get_k(l),r = get_k(r + 2);
        splay(l,0);splay(r,l);
        tree[tree[r].son[0]].flag ^= 1;
    }
    print(root);
    return 0;
}