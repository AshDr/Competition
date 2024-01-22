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
#include <random>
#define LOG(FMT...) fprintf(stderr, FMT)
#define sz(x) (int)x.size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
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
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll myRand(ll B) {return (ull)rng()%B;}
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

ll floor(ll x, ll m) {
    ll r = (x % m + m) % m;
    return (x - r) / m;
}// neg floor (-1, 3) = -1
const int N = 2e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
ll memo[20][200][200][2][2];
int len;
string s;
int val;
//15*9=13
ll dfs(int cur,int digsum, int mod, int f, int g) {
	// cerr << cur << " " << digsum << " " << f << " " << g << endl;
	if(digsum > val) return 0;
	if(cur >= len) {
		if(digsum == val) {
			return (mod == 0);
		}else {
			return 0;
		}
	}
	if(memo[cur][digsum][mod][f][g] != -1) return memo[cur][digsum][mod][f][g];
	int lim = 9;
	if(f == 1) lim = s[cur] - '0';
	ll res = 0;
	for(int i = 0; i <= lim; i++) {
		res += dfs(cur + 1, digsum + i, (mod * 10 + i) % val, f && (i == s[cur] - '0'), g && (i == 0));
	}
	return memo[cur][digsum][mod][f][g] = res;
}
void gao(string s) {

}
void solve() {
    //好整数的个数 <= n ,好整数位数不超过14位
    cin >> s;
    memset(memo, -1, sizeof memo);
    len = sz(s);
    int mx = 0;
    for(int i = 0; i < len; i++) {
    	mx += s[i] - '0';
    }
    mx = max(mx, s[0] - '0' - 1 + (len - 1) * 9);
    ll res = 0;
    for(int i = 1; i <= mx; i++) {
    	val = i;
    	res += dfs(0,0,0,1,1);
    	memset(memo, -1, sizeof memo);
    }
    cout << res << "\n";
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