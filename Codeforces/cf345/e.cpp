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
int ID(int r, int c) {return (r - 1) * m + c;}
struct DSU {
    std::vector<int> f, siz;
    DSU(int n) : f(n), siz(n, 1) { std::iota(f.begin(), f.end(), 0); }
    int leader(int x) {
        while (x != f[x]) x = f[x] = f[f[x]];
        return x;
    }
    bool same(int x, int y) { return leader(x) == leader(y); }
    bool merge(int x, int y) {
        x = leader(x);
        y = leader(y);
        if (x == y) return false;
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    int size(int x) { return siz[leader(x)]; }
};
void solve() {
    cin >> n >> m;
    DSU dsu(n * m + 1);
    vector<vector<int>> G(n * m + 1);
    vector<vector<pii>> R(n + 1),C(m + 1);
    vector<int> indeg(n * m + 1),ans(n * m + 1);
    for(int i = 1; i <= n; i++) {
    	for(int j = 1; j <= m; j++) {
    		int val;
    		cin >> val;
    		R[i].push_back({val, ID(i, j)});
    		C[j].push_back({val, ID(i, j)});
    	}
    }
    for(int i = 1; i <= n; i++) {
    	sort(R[i].begin(),R[i].end());
    	for(int j = 0; j < m - 1; j++) {
    		if(R[i][j].first == R[i][j + 1].first) dsu.merge(R[i][j].second, R[i][j + 1].second);
    	}
    }
    for(int i = 1; i <= m; i++) {
    	sort(C[i].begin(),C[i].end());
    	for(int j = 0; j < n - 1; j++) {
    		if(C[i][j].first == C[i][j + 1].first) dsu.merge(C[i][j].second, C[i][j + 1].second);
    	}
    }
    for(int i = 1; i <= n * m; i++) {
    	if(dsu.leader(i) == i) {
    		G[0].push_back(i);
    		indeg[i]++;
    	}
    }
    for(int i = 1; i <= n; i++) {
    	for(int j = 0; j < m - 1; j++) {
    		int u = dsu.leader(R[i][j].second),v = dsu.leader(R[i][j + 1].second);
    		if(u != v) {
    			G[u].push_back(v);
    			indeg[v]++;
    		}
    	}
    }
    for(int i = 1; i <= m; i++) {
    	for(int j = 0; j < n - 1; j++) {
    		int u = dsu.leader(C[i][j].second),v = dsu.leader(C[i][j + 1].second);
    		if(u != v) {
    			G[u].push_back(v);
    			indeg[v]++;
    		}
    	}
    }
    queue<int> q;
    q.push(0);
    while(!q.empty()) {
    	int u = q.front();q.pop();
    	for(auto v: G[u]) {
    		indeg[v]--;
    		if(indeg[v] == 0) q.push(v);
    		ans[v] = max(ans[v],ans[u] + 1);
    	}
    }
    for(int i = 1; i <= n; i++) {
    	for(int j = 1; j <= m; j++) {
    		cout << ans[dsu.leader(ID(i,j))] << " \n"[j == m];
    	}
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