#include<bits/stdc++.h>
//#define cerr cout<<"#case:"
#define LOG(FMT...) fprintf(stderr, FMT)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
const int N = 2e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const LL MOD = 1e9 + 7;
int TT,n,m;
template <class T>
istream& operator>>(istream& is, vector<T>& v) {
  for (T& x : v)
    is >> x;
  return is;
}
template <class T>
ostream& operator<<(ostream& os, const vector<T>& v) {
  if (!v.empty()) {
    os << v.front();
    for (int i = 1; i < (int)v.size(); ++i)
    os << ' ' << v[i];
  }
  return os;
}
void dbg_out() { cerr << "\b\b )" << endl; }
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T){cerr << H << ", ";dbg_out(T...);}
#define debug(...) cerr << "( " << #__VA_ARGS__ << " ) = ( ", dbg_out(__VA_ARGS__)
//LL fac[N],inv[N];
LL gcd(LL x, LL y) {return y == 0 ? x : gcd(y, x % y);}
LL qpow(LL base, LL x) {
    LL res = 1;
    while(x) {
       if(x & 1) res = (res * base) % MOD;
       base = (base * base) % MOD;
       x >>= 1;
    } 
    return res;
}
LL a[N];
struct dragon {
    LL x,y;
}b[N];
LL tot,x,y;
LL calc(int pos) {
    LL res1 = max(x - a[pos],0ll),res2 = max(y - (tot  - a[pos]),0ll);
    return res1 + res2;
}
int totnum;
void solve() {
    cin>>n;
    for(int i = 1; i <= n; i++) cin>>a[i],tot += a[i];
    sort(a + 1,a + 1 + n);
    totnum = unique(a + 1,a + 1 + n) - a - 1;
    cin>>m;
    for(int i = 1; i <= m; i++) cin>>b[i].x>>b[i].y;
    for(int i = 1; i <= m; i++) {
        x = b[i].x,y = b[i].y;
        int l = 1,r = totnum;
        LL lans = 1e18,rans = 1e18;
        while(l < r) {
            int lmid = l + (r - l) / 3; // l + 1/3区间大小
            int rmid = r - (r - l) / 3;  // r - 1/3区间大小
            lans = calc(lmid),rans = calc(rmid); 
            //debug(i,lmid,lans);
            //debug(i,rmid,rans);
         // 求凹函数的极小值
            if(lans <= rans) r = rmid - 1;
            else l = lmid + 1;
            // 求凸函数的极大值
            //if(lasn >= rans) l = lmid + 1;
            //else r = rmid - 1;
        }
        cout<<min(lans,rans)<<'\n';
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
    //cin>>TT;
    TT = 1;
    while(TT--) solve();
    #ifdef ASHDR
    LOG("Time: %dms\n", int ((clock()
            -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
    #endif
    return 0;
}