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
int n,m,p,b;
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
    cin >> n >> m >> p >> b;
	set<int> tokens,bonuses;
	vector<vector<int>> G(n + 1,vector<int>());
	for(int i = 0; i < p; i++) {
		int x;
		cin >> x;
		tokens.insert(x);
	}    
	for(int i = 0; i < b; i++) {
		int x;
		cin >> x;
		bonuses.insert(x);
	}
	DSU dsu(n + 1);
    for(int i = 0; i < m; i++) {
    	int u,v;
    	cin >> u >> v;
    	G[u].push_back(v);
    	G[v].push_back(u);
		if(bonuses.count(u) && bonuses.count(v)) {
			dsu.merge(u, v);
		}    	
    }
    set<int> s1,s2;
    for(auto x: bonuses) {
        if(dsu.size(x) >= 2) {
            for(auto v: G[x]) {
                if(tokens.count(v)) s2.insert(v);
            }
        }else {
            for(auto v: G[x]) {
                if(tokens.count(v)) s1.insert(v);
            }
        }
    }
    for(auto x: s2) s1.erase(x);
    LL sum = (int)(1e9)*1ll*sz(s2)+sz(s1);
    vector<int> dis(n + 1,1e9);
    queue<int> q;
    q.push(1);
    dis[1] = 0;
    while(!q.empty()) {
    	int u = q.front();q.pop();
    	if(u != 1 && !bonuses.count(u)) continue;
    	for(auto v: G[u]) {
    		if(dis[v] > dis[u] + 1) {
    			dis[v] = dis[u] + 1;
    			q.push(v);
    		}
    	}
    }
    for(auto x: tokens) {
        if(dis[x] == (int)1e9) continue;
        if(dis[x] <= 1) {
            cout << "YES\n";
            return ;
        }
        int t;
    	if(s1.count(x)) sum -= 1,t = 1;
    	else if(s2.count(x)) sum -= (int)1e9,t = (int)1e9;
        
        if(dis[x] <= sum + 1) {
    		cout << "YES\n";
    		return ;
    	}
        sum += t;
    }
	cout << "NO\n";
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