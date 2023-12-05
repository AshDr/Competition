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
int n, m;
int a[N];
vector<int> G[N],H[N];
int dfn[N],low[N],dfn_cnt;
int scc_cnt,belong[N],is_instk[N],c[N];
ll val[N];
vector<int> stk;
void tarjan(int u) {
	dfn[u] = low[u] = ++dfn_cnt;
	stk.push_back(u);
	is_instk[u] = 1;
	for(auto v: G[u]) {
		if(!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		}else if(is_instk[v]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
	if(low[u] == dfn[u]) {
		++scc_cnt;
		int x;
		do {
			x = stk.back();stk.pop_back();is_instk[x] = 0;
			c[scc_cnt]++;
			val[scc_cnt] += a[x];
			belong[x] = scc_cnt;
		}while(x != u);
	}
}
void solve() {
    cin >> n >> m;
    dfn_cnt = scc_cnt = 0;
    for(int i = 1; i <= n; i++) {
    	val[i] = c[i] = dfn[i] = low[i] = 0;
    	G[i].clear();
    	H[i].clear();
    	cin >> a[i];
    }

    for(int i = 1; i <= m; i++) {
    	int u, v;
    	cin >> u >> v;
    	G[u].push_back(v);
    }
    for(int i = 1; i <= n; i++) if(!dfn[i]) tarjan(i);
    for(int i = 1; i <= n; i++) {
    	for(auto v: G[i]) {
    		if(belong[i] != belong[v]) H[belong[i]].push_back(belong[v]);
    	}
    }
    vector<int> f(scc_cnt + 1);
    vector<ll> g(scc_cnt + 1);
   	int res = 0;
   	ll ans = 1e18;
    for(int i = 1; i <= scc_cnt; i++) {
    	f[i] = c[i];g[i] = val[i];
    	for(auto v: H[i]) {
    		int v1 = f[v] + c[i];
    		ll v2 = g[v] + val[i];
    		if(v1 > f[i] || (v1 == f[i] && v2 < g[i])) {
    			f[i] = v1;
    			g[i] = v2;
    		}
    	}
    	if(f[i] > res || (res == f[i] && g[i] < ans)) {
    		res = f[i];
    		ans = g[i];
    	}
    }
    cout << res << " " << ans << "\n";
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
    cin>>TT;
    while(TT--) solve();
    #ifdef ASHDR
    LOG("Time: %dms\n", int ((clock()
            -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
    #endif
    return 0;
}