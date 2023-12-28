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

const int N = 2e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
int vis[N],parent[N];
int n;
namespace CD {
	vector<pii> G[N];
	int S=n,rt=0,cnt,mxpart=1e9,siz[N]; //init S and mxpart
	void find_rt(int u, int fa) {
	    int mx=0;
	    for(auto [v,w]: G[u]) {
	        if(vis[v]||v==fa) continue;
	        find_rt(v, u);
	        mx=max(mx,siz[v]);
	    }
	    mx=max(mx,S - siz[u]);
	    if(mx < mxpart) mxpart=mx,rt=u;
	}
	void get_siz(int u, int fa) {
	    siz[u]=1;
	    for(auto [v,w]:G[u]) {
	        if(vis[v] || v==fa) continue;
	        get_siz(v, u);
	    	siz[u]+=siz[v];
	    }
	}
	
	void calc(int u, int prefa) {
	    mxpart=1e9;
	    rt=u;
	    get_siz(u, 0);
	    S = siz[u];
	    find_rt(u, 0);
	    // cout<<u<<" "<<rt<<endl;
        parent[rt] = prefa;
	    vis[rt]=1;
	    int curfa = rt;
	    for(auto [v,w]:G[rt]) {
	        if(!vis[v]) {
	            calc(v, curfa);
	        }
	    }
	}
}
using namespace CD;
void solve() {
    cin >> n;
    for(int i = 1; i <= n; i++) parent[i] = -1;
    for(int i = 1; i < n; i++) {
    	int u, v;
    	cin >> u >> v;
    	G[u].push_back({v, 0});
    	G[v].push_back({u, 0});
    }
    calc(1, -1);
    for(int i = 1; i <= n; i++) cout << parent[i] << " \n"[i == n];
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