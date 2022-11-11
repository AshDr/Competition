// 长链剖分
#include <bits/stdc++.h>
#define debug printf("Running %s on line %d...\n",__FUNCTION__,__LINE__)
#define in inline
#define re register
using namespace std;
typedef long long ll;
typedef double db;
in int read()
{
    int ans=0,f=1;char c=getchar();
    for (;!isdigit(c);c=getchar()) if (c=='-') f=-1;
    for (;isdigit(c);c=getchar()) ans=(ans<<3)+(ans<<1)+(c^48);
    return ans*f;
}
in int cmin(int &a,int b) {return a=min(a,b);}
in int cmax(int &a,int b) {return a=max(a,b);}
int n;
int buf[1000005];
int *f[1000005],*g[1000005],*now=buf;
int nex[2000005],head[1000005],tail[2000005],tot;
int ans[1000005];
void addedge(int u,int v)
{
    nex[++tot]=head[u];
    head[u]=tot;
    tail[tot]=v;
}
int dep[1000005],son[1000005];
void dfs1(int u,int fa) // 长链剖分
{
    for (int e=head[u];e;e=nex[e])
    {
        int v=tail[e];
        if (v==fa) continue;
        dfs1(v,u);
        if (dep[v]>dep[son[u]]) son[u]=v;
    }
    dep[u]=dep[son[u]]+1;
}
void dfs2(int u,int fa) //做dp
{
    f[u][0]=1;
    if (son[u])
    {
        f[son[u]]=f[u]+1; // 共享内存
        dfs2(son[u],u);
        ans[u]=ans[son[u]]+1; //从长孩子节点继承答案
    }
    for (int e=head[u];e;e=nex[e])
    {
        int v=tail[e];
        if (v==son[u] || v==fa) continue;
        f[v]=now;now+=dep[v]; // 分配内存
        dfs2(v,u);
        for (int i=1;i<=dep[v];i++)
        {
            f[u][i]+=f[v][i-1]; //暴力合并
            if (f[u][i]>f[u][ans[u]] || (f[u][i]==f[u][ans[u]] && i<ans[u])) ans[u]=i; //更新答案
        }
    }
    if (f[u][ans[u]]==1) ans[u]=0;
}
int main()
{
    n=read();
    for (int i=1;i<n;i++)
    {
        int u=read(),v=read();
        addedge(u,v);
        addedge(v,u);
    }
    dfs1(1,0); // 长链剖分
    f[1]=now;now+=dep[1]; // 为根节点的答案分配内存
    dfs2(1,0);
    for (int i=1;i<=n;i++) cout<<ans[i]<<endl;
    return 0;
}