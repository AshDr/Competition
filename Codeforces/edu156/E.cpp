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
#include <functional>
#include <random>
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
mt19937_64 myrand(chrono::steady_clock::now().time_since_epoch().count());
ll myRand(ll B) {return (ull)myrand()%B;}
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

const int N = 2e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
int n, m;
pii a[N];
int b[N];
int dp[1 << 20];
pii f[21][N];
void solve() {
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> a[i].first,a[i].second = i;
    for(int i = 1; i <= m; i++) cin >> b[i];
    // sort(a + 1, a + 1 + n,greater<pii>());
    sort(a + 1, a + 1 + n);
    memset(f,0x3f,sizeof f);
    memset(dp,0x3f,sizeof dp);
    // for(int i = 1; i <= m; i++) {
    //     for(int r = 1; r <= n; r++) {
    //         int l = r - ((b[i] - 1) / a[r].first + 1) + 1;
    //         if(l >= 1) f[i][l] = min(f[i][l], r);
    //     }
    //     for(int j = n - 1; j >= 1; j--) {
    //         f[i][j] = min(f[i][j], f[i][j + 1]);
    //     }
    // }
    for(int i = 1; i <= m; i++) {
        f[i][n + 1] = {n + 1,n + 1};
        for(int j = n; j >= 1; j--) {
            int r = j + ((b[i] - 1) / a[j].first + 1) - 1;
            f[i][j] = {r, j};
            if(r < j) f[i][j] = {0x3f3f3f3f, 0};
            f[i][j] = min(f[i][j], f[i][j + 1]);
        }
    }
    dp[0] = 0;
    for(int mask = 1; mask < (1 << m); mask++) {
        for(int i = 1; i <= m; i++) {
            if((mask >> (i - 1)) & 1) {
                int t = mask ^ (1 << (i - 1));
                if(dp[t] < n) dp[mask] = min(dp[mask], f[i][dp[t] + 1].first);
            }
        }
    }
    if(dp[(1 << m) - 1] <= n) {
        cout << "YES\n";
        int s = (1 << m) - 1;
        vector<vector<int>> res(m + 1);
        while(s) {
            for(int i = 1; i <= m; i++) {
                if(s >> (i - 1) & 1) {
                    int t = s ^ (1 << (i - 1));
                    if(dp[t] < n && dp[s] == f[i][dp[t] + 1].first) {
                        for(int j = f[i][dp[t] + 1].second; j <= dp[s]; j++) {
                            res[i].push_back(a[j].second);
                        }
                        s = t;
                        break;
                    }
                }
            }
        }
        for(int i = 1; i <= m; i++) {
            cout << sz(res[i]);
            for(auto val: res[i]) {
                cout << " " << val;
            }
            cout << "\n";
        }
    }else {
        cout << "NO\n";
    }
}
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