#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,m;
int x[100005],y[100005],p[100005];
int x1_[100005],y1_[100005];
int x2_[100005],y2_[100005];
int h[300005];
unordered_map<int,ll> tr[300005];  
int len1,len2;
inline int read() {
    int f = 1;char ch = getchar();
    int sum = 0;
    while(ch > '9' || ch < '0') {if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9')  sum = sum * 10 + ch - '0',ch = getchar();
    return f * sum;
}
inline int lowbit(int x) {return x&-x;}
void add(int posx,int posy,int p)
{
    for(int i = posx;i<=len1; i+=lowbit(i)) {
        for(int j = posy ; j<=len2; j+=lowbit(j)) tr[i][j] += p;
    }
}
ll ask(int posx, int posy) {
    ll res = 0;
    for(int i = posx; i; i-=lowbit(i)) {
        for(int j = posy;j;j-=lowbit(j)) res += tr[i][j];
    }
    return res;   
}
int main()
{
    int i,n,m,cnt=0;
    //scanf("%d%d",&n,&m);
    n = read();m = read();
    for(i=1;i<=n;i++) x[i] = read(),y[i] = read(),p[i] = read();
        //scanf("%d%d%d",&x[i],&y[i],&p[i]);
    for(i=1;i<=m;i++) x1_[i] = read(),y1_[i] = read(),x2_[i] = read(),y2_[i] = read();
        //scanf("%d%d%d%d",&x1_[i],&y1_[i],&x2_[i],&y2_[i]);
    for(i=1;i<=n;i++)
        h[++cnt]=x[i];
    for(i=1;i<=m;i++)
        h[++cnt]=x1_[i],h[++cnt]=x2_[i];
    sort(h+1,h+1+cnt);
    len1=unique(h+1,h+1+cnt)-h;
    for(i=1;i<=n;i++)
        x[i]=lower_bound(h+1,h+len1,x[i])-h;
    for(i=1;i<=m;i++)
    {
        x1_[i]=lower_bound(h+1,h+len1,x1_[i])-h;
        x2_[i]=lower_bound(h+1,h+len1,x2_[i])-h;
    }
    cnt=0;
    for(i=1;i<=n;i++)
        h[++cnt]=y[i];
    for(i=1;i<=m;i++)
        h[++cnt]=y1_[i],h[++cnt]=y2_[i];
    sort(h+1,h+1+ cnt);
    len2=unique(h+1,h+1+cnt)-h;
    for(i=1;i<=n;i++)
        y[i]=lower_bound(h+1,h+len2,y[i])-h;
    for(i=1;i<=m;i++)
    {
        y1_[i]=lower_bound(h+1,h+len2,y1_[i])-h;
        y2_[i]=lower_bound(h+1,h+len2,y2_[i])-h;
    }
    //离散化
    for(i=1;i<=n;i++) add(x[i],y[i],p[i]);
    for(i=1;i<=m;i++) printf("%lld\n",ask(x2_[i],y2_[i])+ask(x1_[i]-1,y1_[i]-1)-ask(x1_[i]-1,y2_[i])-ask(x2_[i],y1_[i]-1));
    return 0;
}