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

const int N = 3e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
int n,q;
int use[N],siz[N],belong[N];
vector<pii>G[N];
void solve() {
	cin>>n>>q;
	vector<pii> tmp;
	for(int i=1;i<=n-1;i++) {
		int u,v;
		cin>>u>>v;
		use[u]^=1;
		use[v]^=1;
		tmp.push_back({u,v});
	}
	vector<int> val(n+1,-1);
	for(int i=1;i<=q;i++) {
		int u,v,w;	
		cin>>u>>v>>w;
		G[u].push_back({v,w});
		G[v].push_back({u,w});
	}
	int ans=0;
	for(int i=1;i<=n;i++) {
		if(val[i]!=-1) continue;
		queue<int>q;
		q.push(i);
		val[i]=0;
		while(!q.empty()) {
			int u=q.front();q.pop();
			if(use[u]) {
				siz[i]++;
				ans^=val[u];
			}	
			belong[u]=i;
			for(auto [v,w]:G[u]) {
				if(val[v]==-1) {
					val[v]=val[u]^w;
					q.push(v);
				}else {
					if(val[v]!=(val[u]^w)) {
						cout<<"No\n";
						return ;
					}
				}
			}
		}
	}
	for(int i=1;i<=n;i++) {
		if(siz[i]&1) {
			for(int j=1;j<=n;j++){
				if(belong[j]==i){
					val[j]^=ans;
				}
			}
			break;
		}
	}
	//111 010 = 101    10 01 110
	cout<<"Yes\n";
	for(int i=0;i<n-1;i++){
		int u=tmp[i].first,v=tmp[i].second;
		cout<<(val[u]^val[v])<<" \n"[i==n-2];
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