#include<bits/stdc++.h>
//#define cerr cout<<"#case:"
#define LOG(FMT...) fprintf(stderr, FMT)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
const int N = 1e2 + 10;
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
int lcm(int x, int y){
    return x * y / gcd(x,y);
}
int a[N][N],aa[N][N];
int ans[N];
vector<pii> b;
int Gauss() {
    int nwline = 1;
    b.clear();
    for(int i = 1; i <= n; i++) {
        int pos = nwline;
        for(int j = nwline; j <= n; j++) if(abs(a[j][i]) > abs(a[pos][i])) pos = j;
        if(a[pos][i] == 0) continue;
        if(pos != nwline) swap(a[pos],a[nwline]);
        for(int j = 1; j <= n; j++) {
            if(j != nwline && a[j][i] != 0) {
                int LCM = lcm(abs(a[j][i]),abs(a[nwline][i]));
                int tmp1 = LCM / abs(a[j][i]),tmp2 = LCM / abs(a[nwline][i]);
                if(a[j][i] * a[nwline][i] < 0) tmp2 = -tmp2;
                for(int k = i + 1; k <= n + 1; k++) a[j][k] = a[j][k] * tmp1 - a[nwline][k] * tmp2;
            }
        }
        ++nwline;
    }
    if(nwline <= n) return 0;
    else {
        for(int i = 1; i <= n; i++) {
            if(a[i][n + 1] % a[i][i] != 0) return 0;
            ans[i] = a[i][n + 1] / a[i][i];
            if(ans[i] <= 0) return 0;
            b.push_back({ans[i],i});
        }   
        //for(auto p:b) cout<<p.first<<' '<<p.second<<endl;
        sort(b.rbegin(),b.rend());
        if(n >= 2 && b[0].first == b[1].first) return 0;
        else return 1;
    }
}
void solve() {
    cin>>n;
    for(int i = 1; i <= n + 1; i++) {
        cin>>m;
        for(int j = 1; j <= m; j++) {
            int t;
            cin>>t;
            aa[i][t]++;
        }
        cin>>aa[i][n + 1];
    }
    int mx = 0,mxid = 0;
    int cnt = 0;
    for(int i = 1; i <= n + 1; i++) {
        int r = 1;

        for(int k = 1; k <= n + 1; k++) {
            if(k == i) continue;
            for(int p = 1; p <= n + 1; p++) {
                a[r][p] = aa[k][p];
            }
            ++r;
        }

        if(Gauss()) {
            if(mx < b[0].first) {
                mx = b[0].first;
                mxid = b[0].second;  
            }
            ++cnt;
        }
    }
    if(cnt == 1) cout<<mxid<<endl;
    else cout<<"illegal"<<endl;
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