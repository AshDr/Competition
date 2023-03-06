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
#define LOG(FMT...) fprintf(stderr, FMT)
#define sz(x) (int)x.size()
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
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

const int N = 5e3 + 10;
const int M = 1e5 + 10;
const ll INF = 1e18;
const ll MOD = 1e9 + 7;
int TT = 1;
int n,m;
int a[N],mn[N][N],b[N],vis[N];
ll dp[N][N][2];//choose j item with k wanted, compress first dimension

void solve() {
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin>>a[i];
    for(int i = 1; i <= n; i++) cin>>b[i];
    for(int i = 1; i <= n; i++) {
        mn[i][i]=b[i];
        for(int j = i + 1; j <= n; j++) {
            mn[i][j]=min(mn[i][j-1],b[j]);
        }
    }
    int lst=0;
   
    for(int i = 1; i <= m; i++) {
        int x;
        cin >> x;
        vis[x]=1;
        lst=max(lst,x);
    }
    //12+3+6
    //21
    int cnt = 0;
    memset(dp,0x3f,sizeof dp);
    dp[0][0][0]=0;
    for(int i = 1; i <= lst; i++) {
        if(vis[i]) {
            ++cnt;
            for(int j = i; j >= cnt; j--) {//枚举选了几个数
                dp[j][cnt][1]=min(dp[j-1][cnt-1][0],dp[j-1][cnt-1][1])+a[i]+mn[i-(j-1)][i];
                // cout <<"type1: "<<i << " " << j <<" " << cnt << " " << dp[j][cnt][1] << "\n";
            }
        }else{
            for(int j = i; j >= cnt; j--) {
                dp[j][cnt][0]=min(dp[j][cnt][0],dp[j][cnt][1]);
                if(j!=0) dp[j][cnt][1]=min(dp[j-1][cnt][0],dp[j-1][cnt][1])+a[i]+mn[i-(j-1)][i];
                //dp[i][j][cnt][1]=min(dp[i-1][j-1][cnt][0],dp[i-1][j-1][cnt][1])+a[i]+
                // cout <<"type2: "<<i << " " << j <<" " << cnt << " " << dp[j][cnt][0] <<" " << dp[j][cnt][1] << "\n";
            }
        }
    }
    ll ans = 1e18;
    for(int i = m; i <= lst; i++) {
        ans = min(ans,dp[i][m][1]);
    }
    cout << ans << "\n";
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