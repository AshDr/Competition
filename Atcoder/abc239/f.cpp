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
    int n, m;
    cin >> n >> m;
    vector<int> D(n);
    cin >> D;
  	DSU dsu(n);
  	for(int i = 0 ; i < m; i++) {
  		int u,v;
  		cin >> u >> v;
  		u--;v--;
  		D[u]--;D[v]--;
  		dsu.merge(u,v);
  	}	
  	vector<vector<int>> store(n);
  	for(int i = 0; i < n; i++) {
  		if(D[i] < 0) {
  			cout << -1 << '\n';
  			return;
  		}
  		for(int j = 0; j < D[i]; j++) store[dsu.leader(i)].push_back(i); 
  	}
  	vector<vector<int>> c2;
  	vector<int> c1;
  	for(int i = 0; i < n; i++) {
  		if(sz(store[i]) > 1) c2.push_back(store[i]);
  		else if(sz(store[i]) == 1) c1.push_back(store[i][0]);
  	}
  	vector<pii> ans;
  	for(auto vec: c2) {
  		for(int i = 0; i < sz(vec) - 1; i++) {
  			if(c1.empty()) {
  				cout << -1 << '\n';
  				return;
  			}
  			int x = vec[i],y = c1.back();
  			dsu.merge(x,y);
  			ans.push_back({x,y});
  			c1.pop_back();
  		}
  		c1.push_back(vec.back());
  	} // 类似于从叶子往上合并

  	//!!
  	if(sz(c1) != 2) {
  		cout << -1 << '\n';
  		return ;
  	}
  	dsu.merge(c1[0],c1[1]);
  	ans.push_back({c1[0],c1[1]});
  	if(dsu.size(0) != n) cout << -1 << '\n';
  	else {
  		for(auto [x, y]: ans) cout << x + 1 << ' ' << y + 1 << '\n';
  	}

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