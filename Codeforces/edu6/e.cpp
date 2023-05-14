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
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef unsigned int ui;
typedef unsigned long long ull;
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

const int N = 4e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
struct node {
	// bool have[61];
	bitset<61> bt;
	bitset<61> lz;
}tr[N<<2];
#define lt idx<<1
#define rt idx<<1|1
int siz[N],dfn[N],id[N];
int a[N];
void push_up(int idx) {
	tr[idx].bt=tr[lt].bt|tr[rt].bt;
}
void push_down(int idx) {
	if(tr[idx].lz.any()) {
		tr[lt].bt = tr[idx].lz;
		tr[lt].lz = tr[idx].lz;
		tr[rt].bt = tr[idx].lz;
		tr[rt].lz = tr[idx].lz;
		tr[idx].lz=0;
	}
}
void build(int idx, int L, int R) {
	if(L==R) {
		tr[idx].bt[a[id[L]]]=1;
		return ;
	}
	int mid=(L+R)>>1;
	build(lt,L,mid);
	build(rt, mid+1, R);
	push_up(idx);
}
void modify(int idx, int l, int r, int L, int R,int val) {
	// cout<<idx<<" "<<l<<" "<<r<<" "<<L<<" "<<R<<"\n";
	if(l<=L&&r>=R) {
		tr[idx].bt=0;
		tr[idx].lz=0;
		tr[idx].bt[val]=1;
		tr[idx].lz[val]=1;
		return ;
	}
	push_down(idx);
	int mid=(L+R)>>1;
	if(l<=mid) modify(lt, l, r, L, mid, val);
	if(r>mid) modify(rt, l, r, mid+1, R, val);
	push_up(idx);
}
bitset<61> query(int idx, int l, int r, int L, int R) {
	if(l<=L&&r>=R) {
		return tr[idx].bt;
	}
	push_down(idx);
	int mid=(L+R)>>1;
	bitset<61>res=0;
	if(l<=mid) res|=query(lt, l, r, L, mid);
	if(r>mid) res|=query(rt, l, r, mid+1, R);
	push_up(idx);
	return res;
}
int n,m,cnt;
vector<int> G[N];
void dfs(int u, int fa) {
	siz[u]=1;
	dfn[u]=++cnt;
	id[cnt]=u;
	for(auto v:G[u]) {
		if(v==fa) continue;
		dfs(v,u);
		siz[u]+=siz[v];
	}
}
void solve() {
    cin>>n>>m;
    for(int i=1; i<=n; i++) cin>>a[i];
    for(int i=1; i<=n-1; i++) {
    	int u,v;
    	cin>>u>>v;
    	G[u].push_back(v);
    	G[v].push_back(u);
    }
    dfs(1,0);
    build(1,1,n);
    for(int i=1; i<=m; i++) {
    	int op,x,c;
    	cin>>op;
    	if(op==1) {
    		cin>>x>>c;
    		modify(1,dfn[x],dfn[x]+siz[x]-1,1,n,c);
    	}else {
    		cin>>x;
    		cout<<query(1,dfn[x],dfn[x]+siz[x]-1,1,n).count()<<"\n";
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