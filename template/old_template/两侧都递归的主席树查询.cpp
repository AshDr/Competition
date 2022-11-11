#include<bits/stdc++.h>
//#define cerr cout<<"#case:"
#define LOG(FMT...) fprintf(stderr, FMT)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
const int N = 5e5 + 10;
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
struct node {
    int ls,rs,sz;
    LL sum;
}tr[1000010 * 30];
int a[N];
int root[N];
int cnt = 0;
void modify(int pre,int &cur, int L, int R,int pos) {
    cur = ++cnt;tr[cur] = tr[pre];tr[cur].sz++;tr[cur].sum += pos;
    if(L == R) return ;
    int mid = (L + R) >> 1;
    if(pos <= mid) modify(tr[pre].ls,tr[cur].ls,L,mid,pos);
    else modify(tr[pre].rs,tr[cur].rs,mid + 1,R,pos);
}
LL query(int pre,int cur, int L, int R,int num,LL k) {// num信息很重要
    if(tr[cur].sz - tr[pre].sz == 0) return 0;
    LL cursz = tr[cur].sz - tr[pre].sz,sum = tr[cur].sum - tr[pre].sum;
    if(R <= k + num + cursz - 1) return (2 * k + 2 * num + cursz - 1) * cursz / 2 - sum;
    if(L >= k + num) return sum - (2 * k + 2 * num + cursz - 1) * cursz / 2;
    int mid = (L + R) >> 1;
    int lsz = tr[tr[cur].ls].sz - tr[tr[pre].ls].sz;
    return query(tr[pre].ls,tr[cur].ls,L,mid,num,k) + query(tr[pre].rs,tr[cur].rs,mid + 1,R,num + lsz,k);
}
void build(int& cur,int L, int R) {
    cur = ++cnt;
    if(L == R) return;
    int mid = (L + R) >> 1;
    build(tr[cur].ls,L,mid);
    build(tr[cur].rs,mid + 1,R);
}
void solve() {
    cin>>n>>m;
    for(int i = 1; i <= n; i++) {
        cin>>a[i];
        modify(root[i - 1],root[i],1,1000000,a[i]);
    }
    for(int i = 1; i <= m; i++) {
        int l,r;
        LL k;
        cin>>l>>r>>k;
        cout<<query(root[l - 1],root[r],1,1000000,0,k)<<'\n';
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