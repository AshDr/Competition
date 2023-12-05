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
int n, m, l;
int a[N];
pii b[N];
void solve() {
    cin >> n >> m >> l;
    for(int i = 1; i <= n; i++) cin >> a[i];
    int mx = 0;
    for(int i = 1; i <= m; i++) {
    	cin >> b[i].first;
    	b[i].second = i;
    	mx = max(b[i].first,mx);
    }
    sort(b + 1, b + 1 + m);
    map<int,int> refl;
    for(int i = 1; i <= m; i++) {
    	refl[b[i].second] = i;
    }
    vector<vector<int>> pos(n + 1);
    for(int i = 1; i <= l; i++) {
    	int x ,y;
    	cin >> x >> y;
    	assert(refl.count(y));
    	y = refl[y];
    	pos[x].push_back(y);
    }

    int ans = 0;
    for(int i = 1; i <= n; i++) {
    	if(pos[i].empty()) {
    		ans = max(ans, a[i] + mx);
    	}else {
    		sort(pos[i].begin(), pos[i].end());
    		if(pos[i].back() != m) {
    			ans = max(ans, a[i] + mx);
    		}else {
    			for(int j = sz(pos[i]) - 1; j >= 0; j--) {
    				if(j > 0) {
    					if(pos[i][j - 1] != pos[i][j] - 1) {
    						ans = max(ans, b[pos[i][j] - 1].first + a[i]);
    						break;
    					}
    				}
    				if(j == 0) {
    					if(pos[i][j] - 1 >= 1) {
    						ans = max(ans, b[pos[i][j] - 1].first + a[i]);
    					}
    				}
    			}
    		}
    	}

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