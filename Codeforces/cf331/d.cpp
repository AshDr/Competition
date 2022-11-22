#include <bits/stdc++.h>
#define LOG(FMT...) fprintf(stderr, FMT)
#define sz(x) (int)x.size()
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
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
LL gcd(LL x, LL y) {return y == 0 ? x : gcd(y, x % y);}
LL qpow(LL base, LL x, LL mod) {
    LL res = 1;
    base %= mod;
    while(x) {
       if(x & 1) res = (res * base) % mod;
       base = (base * base) % mod;
       x >>= 1;
    } 
    return res;
}
LL exgcd(LL a,LL b,LL &x,LL &y) {
    if(b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    LL d = exgcd(b,a % b,y,x);
    y -= a / b * x;
    return d;
}// (get inv) gcd(a,p) = 1 

const int N = 2e3 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const LL MOD = 1e9 + 7;
int TT = 1;
double f[N][N][2][2]; 
int ltrans[N],rtrans[N],a[N];
int n,h;
double p;
double dfs(int l, int r, int optl, int optr) {
    if(l > r) return 0;
    if(f[l][r][optl][optr]) return f[l][r][optl][optr];
    double res = 0;
    //左端点 根据上一次的倒向判断这一次的长度
    res += 0.5 * p * (min(h,a[l] - a[l - 1] - optl * h) + dfs(l + 1,r,0,optr)); //左倒
    if(rtrans[l] >= r) {
        res += 0.5 * (1.0 - p) * (a[r] - a[l] + min(h,a[r + 1] - a[r] - optr * h));
    }
    else {
        res += 0.5 * (1.0 - p) * (a[rtrans[l]] - a[l] + h + dfs(rtrans[l] + 1,r,1,optr));
    }
    //右倒

    //右端点
    res += 0.5 * (1.0 - p) * (min(h, a[r + 1] - a[r] - optr * h) + dfs(l,r - 1,optl,0));
    if(ltrans[r] <= l) {
        res += 0.5 * p * (a[r] - a[l] + min(h,a[l] - a[l - 1] - optl * h));
    }
    else {
        res += 0.5 * p * (a[r] - a[ltrans[r]] + h + dfs(l,ltrans[r] - 1,optl,1));
    }
    return f[l][r][optl][optr] = res;
}
void solve() {
    
    cin >> n >> h >> p;
    for(int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + 1 + n);
    ltrans[1] = 1;
    
    for(int i = 2; i <= n; i++) {
        if(a[i] - a[i - 1] >= h) ltrans[i] = i;
        else ltrans[i] = ltrans[i - 1]; 
    }   
    rtrans[n] = n;
    for(int i = n - 1; i >= 1; i--) {
        if(a[i + 1] - a[i] >= h) rtrans[i] = i;
        else rtrans[i] = rtrans[i + 1];
    } 
    a[0] = -1e9;a[n + 1] = 1e9;  
    cout << dfs(1,n,0,0) << '\n';
    
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
    while(TT--) solve();
    #ifdef ASHDR
    LOG("Time: %dms\n", int ((clock()
            -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
    #endif
    return 0;
}