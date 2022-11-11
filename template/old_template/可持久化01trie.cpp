#include <bits/stdc++.h>
using namespace std;
#define maxn 600009
int rt[maxn],cnt[maxn*28];
int ch[maxn*28][2];
int qz[maxn];
int tt=1;
int n,m;
void ins(int a,int b,int t,int x) {
    if(t<0) return;
    int i=(x>>t)&1;
    ch[a][!i]=ch[b][!i];
    ch[a][i]=tt++;
    cnt[ch[a][i]]=cnt[ch[b][i]]+1;
    ins(ch[a][i],ch[b][i],t-1,x);
}
int qu(int a,int b,int t,int x) {
    if(t<0) return 0;
    int i=(x>>t)&1;
    if(cnt[ch[b][!i]]>cnt[ch[a][!i]]) {
        return (1<<t)+qu(ch[a][!i],ch[b][!i],t-1,x);
    }
    else {
        return qu(ch[a][i],ch[b][i],t-1,x);
    }
}
int main(){
    scanf("%d%d",&n,&m);
    int a,b,c,i,j;
    char s[5];
    rt[0]=tt++;
    ins(rt[0],0,25,0);
    for(a=1;a<=n;a++) {
        scanf("%d",&b);
        qz[a]=qz[a-1]^b;
        rt[a]=tt++;
        ins(rt[a],rt[a-1],25,qz[a]);
    }
    for(a=1;a<=m;a++) {
        scanf("%s",s);
        if(s[0]=='A') {
            scanf("%d",&b);
            n++;
            qz[n]=qz[n-1]^b;
            rt[n]=tt++;
            ins(rt[n],rt[n-1],25,qz[n]);
        }
        else {
            scanf("%d%d%d",&i,&j,&b);
            i--;j--;
            if(i==0) printf("%d\n",qu(0,rt[j],25,b^qz[n]));
            else printf("%d\n",qu(rt[i-1],rt[j],25,b^qz[n]));
        }
    }
    return 0;
}