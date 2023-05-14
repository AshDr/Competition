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

const int N = 5e2 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
int n,m;
int vis[N][N];
char ans[N];
int have[N];
void solve() {
	cin>>n>>m;
    for(int i=1; i<=m; i++) {
    	int u,v;
    	cin>>u>>v;
    	vis[u][v]=vis[v][u]=1;
    }
    if(n==1) {
    	cout<<"Yes\n";
    	cout<<"a"<<"\n";
    	return;
    }
    for(int i=1; i<=n; i++) {
    	if(!have[i]) {
    		vector<int> gao;
    		int aa=0,cc=0;
    		int aalink=0,cclink=0;
    		int meet=0;
    		for(int j=1; j<=n; j++) {
	    		if(i==j) continue;
	    		if(!vis[i][j]) {
	    			if(have[j]) {
	    				meet=1;
	    				if(ans[j]=='c') aa=1;
	    				else if(ans[j]=='a') cc=1;
	    			}
	    			gao.push_back(j);
	    		}else {
	    			if(have[j]) {
	    				if(ans[j]=='b') continue;
		    			else {
	    					meet=1;
		    				if(ans[j]=='a') aalink=1;
		    				else cclink=1;
		    			}
	    			}
	    		}
	    	}
	    	if(sz(gao)==0) ans[i]='b',have[i]=1;
	    	else {
	    		if(((aa&&cc))) {
	    			cout<<"No\n";
	    			return;
	    		}
	    		if((aalink&&cclink)) {
	    			cout<<"No\n";
	    			return;
	    		}
	    		if(aa&&cclink) {
	    			cout<<"No\n";
	    			return;
	    		}
	    		if(cc&&aalink) {
	    			cout<<"No\n";
	    			return;
	    		}
	    		if(aa) ans[i]='a';
	    		else if(cc) ans[i]='c';
	    		else ans[i]='a'; 
	    		have[i]=1;
	    		for(auto j:gao) {
	    			if(ans[i]=='a') ans[j]='c';
	    			else ans[j]='a';
	    			have[j]=1;
	    		}
	    	}
    	}else {
    		for(int j=1; j<=n; j++) {
    			if(i==j) continue;
    			if(have[j]) {
    				if(vis[i][j]) {
    					if(ans[j]=='b'||ans[i]=='b') continue;
    					else if(ans[i]!=ans[j]) {
    						cout<<"No\n";
    						return;
    					}
    				}
    				else {
    					if(ans[j]=='b'||ans[i]=='b'||ans[i]==ans[j]) {
    						cout<<"No\n";
    						return;
    					}
    				}
    			}else {
    				if(vis[i][j]) {
    					int flag=1;
    					for(int k=1; k<=n; k++) {
    						if(k==j) continue;
    						if(vis[k][j]==0) {
    							flag=0;
    							break;
    						}
    					}
    					if(flag) ans[j]='b';
    					else ans[j]=ans[i];
    				}
    				else {
    					if(ans[i]=='a') ans[j]='c';
    					else ans[j]='a';
    				}
    			}
    		}
    	}
    }
    cout<<"Yes\n";
    for(int i=1; i<=n; i++) cout<<ans[i];
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