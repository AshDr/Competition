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

const int N = 1e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
vector<int> NewG[N * 6];
int m, n, T;
#define lt idx<<1
#define rt idx<<1|1
//[0~n-1] [n~2*n -1] [2*n+1~6*n]
void build(int idx, int L, int R) {
	if(L == R) {
		NewG[T + idx].push_back(L + n); //to false (real point)
		return ;
	}
	int mid = (L + R) >> 1;
	NewG[T + idx].push_back(T + (lt));
	NewG[T + idx].push_back(T + (rt));
	build(lt, L, mid);
	build(rt, mid + 1, R);
}
void add_edge(int idx, int L, int R, int l, int r, int u) {
	if(l <= L && r >= R) {
		NewG[u].push_back(T + idx); //间接连向 false
		return ;
	}
	int mid = (L + R) >> 1;
	if(l <= mid) add_edge(lt, L, mid, l, r, u);
	if(r > mid) add_edge(rt, mid + 1, R, l, r, u);
}
void solve() {
    cin >> n >> m;
    T = 2 * n;
    vector<pii> edges;
    for(int i = 0; i < m; i++) {
    	int u, v;
    	cin >> u >> v;
    	--u;--v;
    	edges.push_back({u, v});
    }
    vector<int> stk;
    vector<int> low(6 * n + 5),dfn(6 * n + 5),belong(6 * n + 5),instk(6 * n + 5);
    int scc_cnt = 0, dfn_cnt = 0;
    auto Tarjan = [&](auto self, int u)->void {
    	dfn[u] = low[u] = ++dfn_cnt;
    	stk.push_back(u);
    	instk[u] = 1;
    	for(auto v: NewG[u]) {
    		if(!dfn[v]) {
    			self(self, v);
    			low[u] = min(low[u], low[v]);
    		}else if(instk[v]) {
    			low[u] = min(low[u], dfn[v]);
    		}
    	}
    	if(low[u] == dfn[u]) {
    		int x;
    		++scc_cnt;
    		do{
    			x = stk.back();stk.pop_back();
    			belong[x] = scc_cnt;
    			instk[x] = 0;
    		}while(x != u);
    	}
    };
    auto check =[&](int len)->bool {
    	scc_cnt = 0, dfn_cnt = 0;
    	stk.clear();
    	for(int i = 0; i < 6 * n + 5; i++) {
    		NewG[i].clear();
    		instk[i] = low[i] = dfn[i] = belong[i] = 0;
    	}
    	for(auto [u ,v]: edges) {
    		NewG[u + n].push_back(v);
    		NewG[v + n].push_back(u);
    	}
    	build(1, 0, n - 1);
    	for(int i = 0; i < n; i++) {
    		if(i > 0)  add_edge(1, 0, n - 1, max(0, i - len + 1), i - 1, i);
    		if(i < n - 1) add_edge(1, 0, n - 1, i + 1, min(i + len - 1, n - 1), i);
    	}
    	for(int i = 0; i < 6 * n + 5; i++) {
    		if(!dfn[i]) Tarjan(Tarjan, i);
    	}
    	for(int i = 0; i < n; i++) {
    		if(belong[i] == belong[i + n]) return false;
    	}
    	return true;
    };
    int l = 1, r = n;
    while(l < r) {
    	int mid = (l + r + 1) >> 1;
    	if(check(mid)) l = mid;
    	else r = mid - 1;
    }
    cout << l << "\n";

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