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

const int N = 2e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
int dis[N],revdis[N];
int n,m;
void solve() {
    cin>>n>>m;
    map<pii,int> vis,revvis; 
    for(int i=1; i<=n; i++) {
    	string s;
    	cin>>s;
    	for(int j=0; j<m; j++) {
    		if(s[j]=='1') {
                vis[{i,i+j+1}]=1;
                revvis[{i+j+1,i}]=1;    
            }
    	}
    }
    queue<int> q;
    fill(dis,dis+1+n,-1);
    fill(revdis,revdis+1+n,-1);
    q.push(1);
    dis[1]=0;
    while(!q.empty()) {
    	int u=q.front();q.pop();
    	for(int j=1; j<=m; j++) {
    		int v=u+j;
    		if(v>n) continue;
    		if(dis[v]==-1&&vis[{u,v}]) {
    			dis[v]=dis[u]+1;
    			q.push(v);
    		}
    	}
    }
    if(dis[n]==-1||m==1) {
    	for(int i=2; i<=n-1; i++) cout<<-1<<" \n"[i==n-1]; 
    }else {
    	q.push(n);
    	revdis[n]=0;
    	while (!q.empty()) {
    		int u=q.front();q.pop();
    		for(int j=1; j<=m; j++) {
    			int v=u-j;
    			if(v<1) continue;
    			if(revdis[v]==-1&&revvis[{u,v}]) {
    				revdis[v]=revdis[u]+1;
    				q.push(v);
    			}
    		}
    	}
    	// for(int i=1; i<=n; i++) cout<<dis[i]<<s" " << revdis[i]<<"\n";
        vector<int> ans(n+1,-1);
        for(int u=1; u<=n; u++) {
            for(int j=1; j<=m; j++) {
                int v=u+j;
                if(v>n) continue;
                if(dis[u]!=-1&&revdis[v]!=-1&&vis[{u,v}]) {
                    int res=dis[u]+revdis[v]+1;
                    for(int k=u+1; k<v; k++) {
                        if(ans[k]>res||ans[k]==-1) {
                            ans[k]=res;
                        }
                    }
                }
            }
        }
        for(int i=2; i<=n-1; i++) cout<<ans[i]<<" \n"[i==n-1];
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