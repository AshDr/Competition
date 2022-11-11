// 二分栈
#include<bits/stdc++.h>
//#define cerr cout<<"#case:"
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
const int N = 5e5 + 711;
const int M = 1e5 + 10;
const int INF = 2147483647;
const LL MOD = 1e9 + 7;
int T,n,m;
int a[N],chose[N];
double res1[N],res2[N],sq[2 * N];
int top;
struct tup {
    int j,lb,rb;
    tup(): j(0),lb(0),rb(0) {};
    tup(int _j, int _lb, int _rb): j(_j),lb(_lb),rb(_rb) {};
}stk[N];
double get(int i ,int j) {return a[j] + sqrt(i - j);}// j是函数参数 i是函数自变量
int get_bound(int x, int y) { // x是此刻栈顶三元组决策
    int l = 0,r = n + 1;
    while(l < r) {
        int mid = (l + r + 1) >> 1;
        if(get(mid,x) < get(mid,y)) {
            r = mid - 1;
        }
        else l = mid;
    }
    return l;
}
void work(double *res) {
    top = 0;
    res[1] = 0;
    stk[++top] = tup(1,2,n);
    for(int i = 2; i <= n; i++) {
        int l = 1,r = top;
        int pos = top;
        //debug(i);
        while(l <= r) {
            int mid = (l + r) >> 1;
            tup tmp = stk[mid];
            if(tmp.lb <= i && tmp.rb >= i) {
                pos = mid;
                break;
            }
            else if(tmp.lb > i) r = mid - 1;
            else l = mid + 1;
        }// 二分栈 来找到那个三元组
        tup tmp = stk[pos]; 
        //debug(i,tmp.j);
        res[i] = get(i,tmp.j) - a[i];
        int x;
        while(top && (x = get_bound(stk[top].j,i)) <= n) {
            //debug(x);
            if(x <= stk[top].lb) {
                if(top == 1) {
                    stk[top] = tup(i,1,n);
                    break;
                }
                else stk[--top].rb = n; // 有 Trick
            }   
            else {
                stk[top].rb = x - 1;
                stk[++top] = tup(i,x,n);
                break;
            }
        }//更新栈中三元组

    }
}
void solve() {
    cin>>n;
    for(int i = 1; i <= n; i++) cin>>a[i];
    work(res1);
    //cout<<endl;
    reverse(a + 1,a + 1 + n);
    work(res2);
    reverse(res2 + 1, res2 + 1 + n);
    for(int i = 1; i <= n; i++) cout<<(int)max({ceil(res1[i]),ceil(res2[i]),0.0})<<endl;
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  cout<<fixed<<setprecision(8);
  //cin>>T;
  T = 1;
  while(T--) solve();
  return 0;
}