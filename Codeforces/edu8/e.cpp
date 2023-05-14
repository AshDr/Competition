/*
           ▃▆█▇▄▖
       ▟◤▖　　　  ◥█  
   ◢◤ 　  ◢▐　　     ▐▉
 ▗◤　  　   ▂ ▗▖　 ▕ █▎
 ◤　▗▅▖ ◥▄　 ▀▀▀◣　█▊
▐　▕▎  ◥▖◣◤　 　　◢██
█◣　◥▅█▀　     　▐███◤
▐█▙▂　　　      ◢███◤
　◥██◣　　　　 ◢▄◤
　　　▀██▅▇▀▎▇

*/
#include <bits/stdc++.h>
#include <stdexcept>
#define LOG(FMT...) fprintf(stderr, FMT)
#define sz(x) (int)x.size()
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef unsigned int ui;
typedef unsigned long long ull;
typedef pair<double,double> pdd;
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
mt19937 myrand(chrono::steady_clock::now().time_since_epoch().count());
ll gcd(ll x, ll y) {return y == 0 ? x : gcd(y, x % y);}
ll qpow(ll base, ll x, ll mod) {
    ll res = 1;
    base %= mod;
    while(x) {
       if(x & 1) res = (res * base) % mod;
       base = (base * base) % mod;
       x >>= 1;
    } 
    return res;
}
ll exgcd(ll a,ll b,ll &x,ll &y) {
    if(b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll d = exgcd(b,a % b,y,x);
    y -= a / b * x;
    return d;
}// (get inv) gcd(a,p) = 1 

const int N = 3e3 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
int n,m;
int L[N][N],R[N][N],diag[N][N];
int a[N][N];
int fw[N*2][N];
vector<pii> TMP[N];
void add(int id, int pos,int val) {
    for(int i=pos; i<N; i+=i&-i) fw[id][i]+=val;
}
int sum(int id, int pos) {
    int res=0;
    for(int i=pos; i; i-=i&-i) res+=fw[id][i];
    return res;
}
void solve() {
    cin>>n>>m;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=m; j++) {
            char ch;
            cin>>ch;
            if(ch=='z') a[i][j]=1;
        }
    }
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=m; j++) if(a[i][j]) L[i][j]=L[i][j-1]+a[i][j];
        for(int j=m; j>=1; j--) if(a[i][j]) R[i][j]=R[i][j+1]+a[i][j];
    }
    for(int i=n; i>=1; i--) {
        for(int j=1; j<=m; j++) {
            if(a[i][j]) diag[i][j]=diag[i+1][j-1]+a[i][j]; //右上角连多少次
        }
    }
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=m; j++) {
            if(R[i][j]) {
                int col=j+R[i][j]-1;
                TMP[col].push_back({i,j});
            }
        }
    }
    ll ans=0;
    for(int j=m; j>=1; j--) {
        for(auto [x,y]:TMP[j]) add(x+y,y,1);
        for(int i=1; i<=n; i++) {
            int len=min(L[i][j],diag[i][j]);
            if(len==0) continue;
            ans+=sum(i+j,j)-sum(i+j,j-len+1-1);
        }
    }
    cout<<ans<<"\n";
}
// #define ASHDR
int main() {
    #ifdef ASHDR
    freopen("data.in","r",stdin);
    freopen("data.out","w",stdout);
    int nol_cl = clock();
    #endif
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout<<fixed<<setprecision(8);
    //cin>>TT;
    while(TT--) solve();
    #ifdef ASHDR
    LOG("Time: %dms\n", int ((clock()
            -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
    #endif
    return 0;
}
/*
const int N = 3e3 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
int n,m;
int L[N][N],R[N][N],diag[N][N];
int a[N][N],id[N][N];
struct node {
    int val;
    int row,col;
}b[N*N];
struct Q{
    int l,r;
    int val;
}q[N*N];
template <typename T>
struct Fenwick {
    const int n;
    std::vector<T> a;
    Fenwick(int n) : n(n), a(n) {}
    void add(int x, T v) {
        for (int i = x; i < n; i += i & -i) {
            a[i] += v;
        }
    }
    T sum(int x) {
        T ans = 0;
        if(x <= 0) return ans;
        for (int i = x; i > 0; i -= i & -i) {
            ans += a[i];
        }
        return ans;
    }
    T rangeSum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
    int find_kth(int k) {
        int ans = 0,cnt = 0;
        for (int i = 1 << __lg(n);i >= 0;i--)  //这里的20适当的取值，与MAX_VAL有关，一般取lg(MAX_VAL)
        {
            ans += (1 << i);
            if (ans >= n || cnt + a[ans] >= k)
                ans -= (1 << i);
            else
                cnt += a[ans];
        }
        return ans + 1;
    }//注意k不能太大
};
Fenwick<ll> fw(N*N);
void solve() {
    cin>>n>>m;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=m; j++) {
            char ch;
            cin>>ch;
            if(ch=='z') a[i][j]=1;
        }
    }
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=m; j++) if(a[i][j]) L[i][j]=L[i][j-1]+a[i][j];
        for(int j=m; j>=1; j--) if(a[i][j]) R[i][j]=R[i][j+1]+a[i][j];
    }
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=m; j++) {
            if(a[i][j]) diag[i][j]=diag[i-1][j+1]+a[i][j]; //右上角连多少次
        }
    }
    int tot=0,tt=0;
    for(int i=1; i<=m; i++) {
        int row=1,col=i;
        while(row<=n&&col>=1) {
            if(L[row][col]) {
                b[++tot].val=col-L[row][col]+1;
                b[tot].row=row;
                b[tot].col=col;
            }
            id[row][col]=++tt;
            ++row;
            --col;
        }
    }
    for(int i=2; i<=n; i++) {
        int row=i,col=m;
        while(row<=n&&col>=1) {
            if(L[row][col]) {
                b[++tot].val=col-L[row][col]+1;
                b[tot].row=row;
                b[tot].col=col;
            }
            id[row][col]=++tt;
            ++row;
            --col;
        }
    }
    sort(b+1,b+1+tot,[&](node x, node y){
        return x.val<y.val;
    });
    int tot_q=0;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=m; j++) {
            int len=min(R[i][j],diag[i][j]);
            if(len==0) continue;
            q[++tot_q].r=id[i][j];
            q[tot_q].l=id[i-len+1][j+len-1];
            q[tot_q].val=j;
            // cout<<i<<" "<<j<<" "<<id[i][j]<<"\n";
        }
    }
    sort(q+1,q+1+tot_q,[&](Q x, Q y){
        return x.val<y.val;
    } );
    ll ans=0;
    int idx=1;
    for(int i=1; i<=tot_q; i++) {
        while(idx<=tot&&b[idx].val<=q[i].val) {
            fw.add(id[b[idx].row][b[idx].col], 1);
            ++idx;
        }
        ll tmp=fw.rangeSum(q[i].l, q[i].r);
        ans+=tmp;
    }
    cout<<ans<<"\n";
}
// #define ASHDR
int main() {
    #ifdef ASHDR
    freopen("data.in","r",stdin);
    freopen("data.out","w",stdout);
    int nol_cl = clock();
    #endif
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout<<fixed<<setprecision(8);
    //cin>>TT;
    while(TT--) solve();
    #ifdef ASHDR
    LOG("Time: %dms\n", int ((clock()
            -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
    #endif
    return 0;
}
*/
