#include<bits/stdc++.h>
//#define cerr cout<<"case#:"
#define LOG(FMT...) fprintf(stderr, FMT)
using namespace std;
typedef long long LL;
const int N = 3e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const int MOD = 1e9 + 7;
int T,n,m;
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
    for (int i = 1; i < v.size(); ++i)
      os << ' ' << v[i];
  }
  return os;
}
void dbg_out() { cerr << "\b\b )" << endl; }
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T){cerr << H << ", ";dbg_out(T...);}
#define debug(...) cerr << "( " << #__VA_ARGS__ << " ) = ( ", dbg_out(__VA_ARGS__)
LL gcd(LL x, LL y) {return y == 0 ? x : gcd(y, x % y);}
LL qpow(LL base, LL x) {
    LL res = 1;
    while(x) {
        if(x & 1) res *= base;
        base *= base;
        base %= MOD;
        res %= MOD;
        x >>= 1;
    }
    return res;
}
LL qmul(LL a,LL b,LL mod) {
    LL res = 0;
    while(b) {
        if(b & 1) res = (res + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return res;
}//快速乘
void exgcd(LL a, LL b, LL &x, LL &y) {
    if(b == 0) {
        x = 1;y = 0;
        return ;
    }
    exgcd(b,a % b,y,x);
    y -= (a / b) * x;
}//模数无限制
LL getinv(LL x,LL mod) {
    LL x_0,y_0;
    exgcd(x,mod,x_0,y_0);
    return x_0;
}
int len;
int get(int x) {return x / len;} 
struct Q {
    int l,r,id;
    friend bool operator < (const Q& x,const Q& y) {
        int l1 = get(x.l),l2 = get(y.l);
        return (l1 == l2) ? (x.r < y.r) : (l1 < l2);
    }
}q[N];
int a[N],cnt[N],ans[N];
int mxnum;
void add(int x) {
    cnt[x]++;
    if(cnt[mxnum] < cnt[x]) mxnum = x;
}
void solve() {
    cin>>n>>m;
    len = (int)sqrt(n);
    for(int i = 1; i <= n; i++) cin>>a[i];
    for(int i = 1; i <= m; i++) cin>>q[i].l>>q[i].r,q[i].id = i;
    sort(q + 1,q + 1 + m);
    for(int i = 1; i <= m;) {
        int j = i;
        while(get(q[i].l) == get(q[j].l)) ++j;
        int rbound = get(q[i].l) * len + len - 1;
        while(i < j && q[i].r <= rbound) {
            mxnum = 0;
            for(int k = q[i].l; k <= q[i].r; k++) add(a[k]);
            int sz = q[i].r - q[i].l + 1;
            ans[q[i].id] = max(2 * cnt[mxnum] - sz,1);
            for(int k = q[i].l; k <= q[i].r; k++) cnt[a[k]]--;
            ++i;
        }
        int curl = rbound + 1,curr = rbound;
        mxnum = 0;
        while(i < j) {
            while(curr < q[i].r) add(a[++curr]);
            int backup = mxnum;
            while(curl > q[i].l) add(a[--curl]);
            int sz = q[i].r - q[i].l + 1;
            ans[q[i].id] = max(2 * cnt[mxnum] - sz,1);
            while(curl < rbound + 1) cnt[a[curl++]]--;
            mxnum = backup;
            ++i;
        }
        memset(cnt,0,sizeof cnt);
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
    //cin>>T;
    T = 1;
    while(T--) solve();
    #ifdef ASHDR
    LOG("Time: %dms\n", int ((clock()
          -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
    #endif
    return 0;
}