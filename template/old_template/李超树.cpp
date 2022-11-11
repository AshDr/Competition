//LI chao
#include<bits/stdc++.h>
//#define cerr cout<<"#case:"
#define LOG(FMT...) fprintf(stderr, FMT)
#define lt i<<1
#define rt i<<1|1
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
const int N = 1e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const LL MOD = 1e9 + 7;
int T,n,m;
struct Interval {
     double k, b; //区间最优势线段的k,b
     int l, r, flag; //l,r为区间。flag为该区间已经记录最优势线段标记。
     int id;
     Interval() {}
     Interval(int a, int b, double c, double d, int id) {
         this->l = a, this->r = b, this->k = c, this->b = d,this->id = id;
     }
     double calc(const int pos)const { //返回线段在x处的y值
         return k * pos + b;
     }
     int cross(const Interval &rhs)const { //求两线段交点的横坐标
         return floor((b - rhs.b) / (rhs.k - k));
     }
}tr[N << 2];
int lstans = 0;
int getx(int x) {
    return (x + lstans - 1) % 39989 + 1;
}
int gety(int y) {
    return (y + lstans - 1) % ((int)1e9) + 1;
}
void modify(int i,int L, int R,Interval k) {
    if(k.l <= L && k.r >= R) {
        if(!tr[i].flag) tr[i].flag = 1,tr[i] = k,debug(k.id);
        else if(k.calc(L) - tr[i].calc(L) > 0 && k.calc(R) - tr[i].calc(R) > 0) {
            tr[i] = k;
        }
        else if(k.calc(L) - tr[i].calc(L) > 0 || k.calc(R) - tr[i].calc(R) > 0) {
            int mid = (L + R) >> 1;
            if(k.calc(mid) > tr[i].calc(mid)) {
                swap(k,tr[i]);
            }
            if(k.cross(tr[i]) <= mid) modify(lt,L,mid,k);
            else modify(rt,mid + 1,R,k);  
        }
    }
    else {
        int mid = (L + R) >> 1;
        if(mid >= k.l) modify(lt,L,mid,k);
        if(k.r > mid) modify(rt,mid + 1,R,k);
    }
}
Interval query(int i, int L, int R, int pos) {
    if(L == R) return tr[i];
    int mid = (L + R) >> 1;
    double res = tr[i].calc(pos);
    if(pos <= mid) {
        Interval tmp = query(lt,L,mid,pos);
        if(res < tmp.calc(pos)) return tmp;
        else return tr[i];
    }
    else {
        Interval tmp = query(lt,mid + 1,R,pos);
        if(res < tmp.calc(pos)) return tmp;
        else return tr[i];        
    } 
}
void solve() {
    cin>>n;
    int cnt = 0;
    int xx1,yy1,xx2,yy2;
    for(int i = 1; i <= n; i++) {
        int op;
        cin>>op;
        if(op == 0) {
            cin>>xx1;
            xx1 = getx(xx1);
            lstans = query(1,1,40000,xx1).id;
            cout<<lstans<<'\n';
        }
        else {
            cin>>xx1>>yy1>>xx2>>yy2;
            xx1 = getx(xx1);xx2 = getx(xx2);
            yy1 = gety(yy1);yy2 = gety(yy2);
            if(xx1 == xx2) continue;
            if(xx1 > xx2) swap(xx1,xx2),swap(yy1,yy2);
            double k = 1.0*(yy2 - yy1) / (xx2 - xx1);
            double b = 1.0*yy1-1.0*xx1*k;
            ++cnt;
            Interval tmp(xx1,xx2,k,b,cnt); // 如果是直线的话 就把线段区间改为x轴范围即可
            modify(1,1,40000,tmp);
        }
    }
}
int main() {
  #ifdef ASHDR
  freopen("data.in","r",stdin);
  int nol_cl = clock();
  #endif
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  cout<<fixed<<setprecision(8);
  //cin>>T;
  T = 1;
  while(T--) solve();
  #ifdef ASHDR
    LOG("Time: %dms\n", int ((clock()
          -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
  #endif
  return 0;
}