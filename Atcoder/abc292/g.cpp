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
typedef unsigned int ui;
typedef unsigned long long ull;
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

const int N = 40 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 998244353;
int TT = 1;
int n,m;
ll dp[N][N][N][N];//dp[d][l][r][val] 考虑d~m位,当前在d位,,l~r的所有串满足第一段的第d位都相同,且值至少为val 且 l~r满足<关系的方案数
char s[N][N];
ll dfs(int d, int l, int r, int val) {
	if(val>9) {
		return 0;
	}
	if(d==m+1) {
		return dp[d][l][r][val]=(l<r?0:1);
	}
	if(dp[d][l][r][val]!=-1) return dp[d][l][r][val];
	dp[d][l][r][val]=0;
	dp[d][l][r][val]+=dfs(d,l,r,val+1)%MOD;
	for(int i=l; i<=r; i++) {
		if(s[i][d]!='?'&&s[i][d]!='0'+val) break;
		dp[d][l][r][val]+=dfs(d+1,l,i,0)*(i==r?1:dfs(d,i+1,r,val+1));
		dp[d][l][r][val]%=MOD;
	}
	return dp[d][l][r][val];
}
void solve() {
    cin>>n>>m;
    for(int i=1; i<=n; i++) {
    	cin>>(s[i]+1);
    }
    memset(dp,-1,sizeof(dp));
    cout<<dfs(1,1,n,0)<<"\n";
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