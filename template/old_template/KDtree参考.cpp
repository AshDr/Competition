#include<cmath>
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
#define rnt re int
#define lc t[p].ls
#define rc t[p].rs
#define re register
#define LL inline ll
#define I inline int
#define V inline void
#define B inline bool
#define lson lc,L,mid-1
#define rson rc,mid+1,R
#define ll long long int
#define isnum(ch) ('0'<=ch&&ch<='9')
#define FOR(i,a,b) for(rnt i=a;i<=b;i++)
#define ROF(i,a,b) for(rnt i=a;i>=b;i--)
#define gc (_op==_ed&&(_ed=(_op=_buf)+fread(_buf,1,100000,stdin),_op==_ed)?EOF:*_op++)
char _buf[100000],*_op(_buf),*_ed(_buf);
I getint(){
    rnt _s=0;re char _ch=gc;
    while(!isnum(_ch))_ch=gc;
    while(isnum(_ch))_s=_s*10+_ch-48,_ch=gc;
    return _s;
}
I min(const int&x,const int&y){return x<y?x:y;}
I max(const int&x,const int&y){return x>y?x:y;}
const int N=2e5+1,INF=0x7fffffff;
ll ans=1ll<<62;const double alpha=0.75;
int n,m,rt,WD;
struct node{
    int sta[N],top,tot;
    V del(rnt x){if(x)sta[++top]=x;}
    I newnode(){return top?sta[top--]:++tot;}
}T;
LL pw(const int&x){return 1ll*x*x;}
struct poi{
    int x[2];
    V input(){FOR(i,0,1)x[i]=getint();}
    B operator<(const poi&u)const{return x[WD]<u.x[WD];}
    LL operator-(const poi&u)const{
        return pw(x[0]-u.x[0])+pw(x[1]-u.x[1]);
    }
}a[N];
struct mat{
    int x[2][2];
    mat(){FOR(i,0,1)x[i][0]=INF,x[i][1]=-INF;}
};
struct kdt{
    mat pos;poi now;
    int ls,rs,siz;
}t[N];
V init(rnt p){
    t[p].siz=t[lc].siz+t[rc].siz+1;
    FOR(i,0,1)t[p].pos.x[i][0]=min(t[p].now.x[i],min(t[lc].pos.x[i][0],t[rc].pos.x[i][0]));
    FOR(i,0,1)t[p].pos.x[i][1]=max(t[p].now.x[i],max(t[lc].pos.x[i][1],t[rc].pos.x[i][1]));
}
V pia(rnt p){if(p)a[++m]=t[p].now,T.del(p),pia(lc),pia(rc),lc=rc=0;}
V build(int&p,rnt L,rnt R,rnt wd){
    if(L>R)return;rnt mid=L+R>>1;WD=wd;
    nth_element(a+L,a+mid,a+R+1),t[p=T.newnode()].now=a[mid];
    build(lson,wd^1),build(rson,wd^1),init(p);
}
LL dis(const poi&x,const mat&y){
    re ll out=0;
    FOR(i,0,1)out+=pw(max(0,y.x[i][0]-x.x[i])+max(0,x.x[i]-y.x[i][1]));
    return out;
}
V ask(rnt p,const poi&x){
    if(!p)return;
    re ll lval=dis(x,t[lc].pos),rval=dis(x,t[rc].pos),val=x-t[p].now;
    if(val<ans)ans=val;
    if(lval<rval){
        if(lval<ans)ask(lc,x);
        if(rval<ans)ask(rc,x);
    }else{
        if(rval<ans)ask(rc,x);
        if(lval<ans)ask(lc,x);
    }
}
B check(rnt p){return alpha*t[p].siz<max(t[lc].siz,t[rc].siz);}
V ins(int&p,const poi&x,rnt wd){
    if(!p)return t[p=T.newnode()].now=x,init(p);WD=wd;
    if(x<t[p].now)ins(lc,x,wd^1);
    else ins(rc,x,wd^1);init(p);
    if(check(p))pia(p),build(p,1,m,wd),m=0;
}
V work(){
    n=getint();poi tmp;
    while(n--)tmp.input(),ask(rt,tmp),ins(rt,tmp,0);
    printf("%.4lf",(double)sqrt(ans));
}
int main(){
    work();
    return 0;
}