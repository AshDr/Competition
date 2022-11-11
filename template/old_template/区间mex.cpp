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
LL MOD_sub(LL x,LL y) {
    return ((x - y) % MOD + MOD) %MOD;
}
LL MOD_add(LL x, LL y) {
    return ((x + y) % MOD + MOD) % MOD;
}
#define lt i<<1
#define rt i<<1|1
struct qq {
    int l,r,id;
}q[N];
int a[N],ans[N];
int trval[N << 2];
void push_up(int i) {trval[i] = min(trval[lt],trval[rt]);}
void modify(int i, int L, int R, int pos,int val) {
    //debug(L,R);
    if(L == R) {
        //debug(L,val);
        trval[i] = max(trval[i],val);
        return ;
    }
    int mid = (L + R) >> 1;
    if(pos <= mid) modify(lt,L,mid,pos,val);
    else modify(rt,mid + 1,R,pos,val);
    push_up(i);
}
int query(int i, int L, int R, int l, int r) {
    //debug(L,R);
    if(L == R) return L;
    int mid = (L + R) >> 1;
    if(trval[lt] < l) return query(lt,L,mid,l,r);
    if(trval[rt] < l) return query(rt,mid + 1,R,l,r);
    return 0;
}
void solve() {
    cin>>n>>m;
    for(int i = 1; i <= n; i++) cin>>a[i];
    for(int i = 1; i <= m; i++) cin>>q[i].l>>q[i].r,q[i].id = i;
    sort(q + 1,q + 1 + m,[&](qq x,qq y){return x.r < y.r;});
    int pt = 0;
    for(int i = 1; i <= m; i++) {
        int r = q[i].r,id = q[i].id,l = q[i].l;
        while(pt < r) {
            modify(1,0,200000,a[pt + 1],pt + 1);
            ++pt;
        }
        ans[id] = query(1,0,200000,l,r);
    }
    for(int i = 1; i <= m; i++) cout<<ans[i]<<'\n';
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