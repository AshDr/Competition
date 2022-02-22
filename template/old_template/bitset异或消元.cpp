#include<bits/stdc++.h>
//#define cerr cout<<"#case:"
#define LOG(FMT...) fprintf(stderr, FMT)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
const int N = 1e5 + 10;
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
mt19937 myrand(chrono::steady_clock::now().time_since_epoch().count());
//LL fac[N],inv[N];
LL gcd(LL x, LL y) {return y == 0 ? x : gcd(y, x % y);}
LL qpow(LL base, LL x, LL mod = MOD) {
    LL res = 1;
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
unordered_map<LL,LL> hsh; // warn map 放外面更快?
int bsgs(LL a,LL b,LL p) {
    a%=p;b%=p;
    if(1 % p == b % p) return 0;
    int k = sqrt(p) + 1;
    hsh.clear();
    LL tmp = b % p;
    for(int i = 0; i < k; i++) {
        hsh[tmp] = i;
        tmp = (tmp * a) % p;
    }
    LL ak = qpow(a,k,p);
    tmp = ak;
    for(int i = 1; i <= k; i++) {
        if(hsh.count(tmp)) return k *1ll* i - hsh[tmp];
        tmp = tmp * ak % p;
    }
    return -INF;
}// gcd(a,p) == 1
int exbsgs(LL a,LL b,LL p) {
    b = (b % p + p) % p;
    if(1 % p == b % p) return 0;
    LL x,y;
    int d = exgcd(a,p,x,y);
    if(d > 1) {
        if(b % d) return -INF;
        exgcd(a/d,p/d,x,y);
        return exbsgs(a,b / d *1ll* x % (p / d),p / d) + 1;
    }
    return bsgs(a,b,p);
}
#define endl '\n'
int get(int i, int j) {return (i - 1) * m + j;}
bitset<1610> a[1610];
int ans[N];
const int dx[] = {-1,1,0,0};
const int dy[] = {0,0,1,-1};
bool check(int x, int y) {
    if(x < 1 || x > n || y < 1 || y > m) return false;
    return true;
}
void xor_gauss() {
    int nwline = 1;
    for(int i = 1; i <= n * m; i++) {
        int pos = nwline;
        for(int j = nwline; j <= n * m; j++) {
            if(a[j][i]) {
                pos = j;
                break;
            }
        }
        if(!a[pos][i]) continue;
        if(pos != nwline) swap(a[pos],a[nwline]);
        for(int j = nwline + 1; j <= n * m; j++) {
            if(a[j][i]) a[j] ^= a[nwline];
        }
        ++nwline;
    }
    for(int i = n * m; i >= 1; i--) {
        if(a[i][i] == 0) {ans[i] = 1;continue;}
        for(int j = a[i]._Find_next(i); j <= n * m; j = a[i]._Find_next(j)) {
            ans[i] ^= ans[j];
        }
    }
}
void solve() {
    cin>>n>>m;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            int id = get(i,j);
            a[id][id] = 1;
            for(int k = 0 ; k < 4; k++) {
                int xx = i + dx[k],yy = j + dy[k];
                if(!check(xx,yy)) continue;
                int t = get(xx,yy);
                a[id][t] = 1;
            }
        }
    }
    xor_gauss();
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cout<<ans[get(i,j)]<<' ';
        }
        cout<<endl;
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