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
int head[N],to[N << 1],id[N << 1],nxt[N << 1],vis[N << 1],tot;
int curpos[N],ans[N];
void add_edge(int u ,int v, int w) {
	to[tot] = v;id[tot] = w;nxt[tot] = head[u];head[u] = tot++;
}
void dfs(int u, int f) {
	for(int i = curpos[u]; ~i; i = nxt[i]) {
		curpos[u] = i;
		if(vis[i]) continue;
		else {
			vis[i] = vis[i ^ 1] = 1;
			int v = to[i], t = id[i];
			ans[t] = f;
			//cout << u << ' ' << v << ' ' << t << ' ' << f << '\n';
			dfs(v,f ^ 1);
			break; // if not break you will get TLE!
		}
	}
}
// 建立二分图染色、链式存信息和当前弧优化
void solve() {
    int m, n;
    cin >> m;
    map<int,int> mp,cnt;
    int num = 0, tot_ver = m;
    memset(head,-1,sizeof head);
    vector<int> restore(m + 1);
    for(int i = 1; i <= m; i++) {
    	cin >> n;
    	restore[i] = n;
    	for(int j = 1; j <= n; j++) {
    		int x;
    		cin >> x;cnt[x]++;
    		if(!mp.count(x)) mp[x] = ++tot_ver;
    		++num;
    		int v = mp[x];
    		add_edge(i, v, num);
    		add_edge(v, i, num);
    	}
    }
    for(auto [x,num]: cnt) {
    	if(num & 1) {
    		cout << "NO" << '\n';
    		return ; 
    	}
    }
    for(int i = 1; i <= tot_ver; i++) curpos[i] = head[i];
    for(int i = 1; i <= tot_ver; i++) dfs(i, 1);
    cout << "YES" << '\n'; 
	int t = 0;
    for(int i = 1; i <= m; i++) {
    	for(int j = 1; j <= restore[i]; j++) {
    		if(ans[++t]) cout << 'L';
    		else cout << 'R';
    	}
    	cout << '\n';
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