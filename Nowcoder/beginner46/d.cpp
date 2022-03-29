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

const int N = 1e6 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const LL MOD = 1e9 + 7;
int TT = 1;

void solve() {
    int n;
    cin >> n;
    vector<vector<pii>> G(n,vector<pii>());
    vector<vector<int>> num(n,vector<int>(3));
    vector<int> ance(n),anc(n);
    for(int i = 1; i < n; i++) {
    	int v,w;
    	cin >> v >> w;
    	v--;
    	G[v].push_back({i,w});
    	if(w < 3) num[v][w]++;
    	ance[i] = w;
    	anc[i] = v;
    }
    vector<int> ans(n);
    function<void(int ,int)> dfs = [&](int u, int fa) {
    	ans[u] = 1;
    	for(auto p: G[u]) {
    		int v = p.first,w = p.second;
    		if(w == 1) {
    			ans[u] += num[v][1] + 1;
    		}
    		else if(w == 2) ans[u]++;
    		dfs(v,u);
    	}

    	if(u != 0) {
    		if(ance[u] == 1) {
    			ans[u] += 1 + num[anc[u]][1] - 1;
    			if(ance[anc[u]] == 1) {
    				ans[u]++;
    			}
    		}
    		else if(ance[u] == 2) ans[u]++;
    	}
    };
    dfs(0,-1);
    for(auto x: ans) cout << x << '\n';
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