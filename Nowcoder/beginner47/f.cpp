#include<bits/stdc++.h>
#define LOG(FMT...) fprintf(stderr, FMT)
#define sz(x) (int)x.size()
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
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
LL gcd(LL x, LL y) {return y == 0 ? x : gcd(y, x % y);}
LL qpow(LL base, LL x, LL mod) {
    LL res = 1;
    base %= mod;
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

const int N = 2e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const LL MOD = 1e9 + 7;
int TT = 1;
void solve() {
    int n, m, k;
    cin >> n;
    vector<int> in_set(n + 1,0),depth(n + 1,0),log_2(n + 1,0) ,siz(n + 1,0);
    vector<vector<int>> G(n + 1,vector<int>()), anc(n + 1,vector<int>(25,0));
    for(int i = 0 ; i < n - 1; i++){
    	int u,v;
    	cin >> u >> v;
    	G[u].push_back(v);
    }
    cin >> m >> k;
    for(int i = 0; i < m; i++) {
    	int x;
    	cin >> x;
    	in_set[x] = 1;
    }
    for(int i = 2; i <= n; i++) log_2[i] = log_2[i / 2] + 1;
    function<void(int, int)> dfs1 = [&](int u, int fa) {
    	for(int i = 1; i < 25; i++) anc[u][i] = anc[anc[u][i - 1]][i - 1];
    	siz[u] = (in_set[u] == 1);
    	for(auto v: G[u]) {
    		depth[v] = depth[u] + 1;
    		anc[v][0] = u;
    		siz[u] += siz[v];
    		dfs1(v, u);
    	}
    };
    vector<int> in_subtree;
    function<void(int, int)> dfs2 = [&](int u, int fa) {
    	if(in_set[u] == 1) {
    		in_subtree.push_back(depth[u] - depth[k]);
    		in_set[u]++;
    	}
    	for(auto v: G[u]) {
    		dfs2(v, u);
    	}
    };
    dfs1(1, 0);
    dfs2(k, 0);
    if(sz(in_subtree) == m) {
		LL mx = 0;
		for(int i = 1; i <= n; i++) {
			if(in_set[i] > 0 && i != k) {
				mx = max(mx, 1ll * siz[i] * (depth[i] - depth[k] - 1));
			}
		}    	
		cout << accumulate(in_subtree.begin(), in_subtree.end(), 0ll) - mx << '\n';
    	return ;
    }
    auto get_lca = [&](int x, int y) {
    	if(depth[x] > depth[y]) swap(x, y);
    	while(depth[x] < depth[y]) y = anc[y][log_2[depth[y] - depth[x]]];
    	if(x == y) return x;
    	for(int i = 24; i >= 0; i--) {
    		if(anc[x][i] == anc[y][i]) continue;
    		else {
    			x = anc[x][i];
    			y = anc[y][i];
    		}
    	}
    	return anc[y][0];
    };
    int lca = 0;
    for(int i = 1; i <= n; i++) {
    	if(in_set[i] == 1) {
    		if(!lca) lca = i;
    		else lca = get_lca(lca, i);
    	}
    }
    LL ans = 0;
    for(int i = 1; i <= n; i++) {
    	if(in_set[i] == 1) ans += depth[i] - depth[lca] + 1; 
    }
    cout << ans + accumulate(in_subtree.begin(), in_subtree.end(), 0ll) << '\n';
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
    while(TT--) solve();
    #ifdef ASHDR
    LOG("Time: %dms\n", int ((clock()
            -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
    #endif
    return 0;
}