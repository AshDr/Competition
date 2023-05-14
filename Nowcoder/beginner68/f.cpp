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
#include <algorithm>
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

const int N = 3e2 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
int n,kk;
void solve() {
    cin>>n>>kk;
    vector<int> a(n);
    for(int i=0; i<n; i++) cin>>a[i];
    vector<int> use;
    for(int i=0; i<n; i++) if(abs(a[i]-a[((i-1)+n)%n])>kk) use.push_back(i),use.push_back(((i-1)+n)%n);
    
    sort(use.begin(),use.end());
    use.erase(unique(use.begin(),use.end()),use.end());
    if(sz(use)==0) {
        cout<<0<<"\n";
        return ;
    }
    else {
    	int m=sz(use);
    	if(m>15) {
            cout<<-1<<"\n";
            return ;
        }
        for(int i=0; i<m; i++) {
    		for(int j=0; j<n; j++) if(j!=use[i]){
    			int idx1=use[i],idx2=j;
    			swap(a[idx1],a[idx2]);
    			vector<int> tmp2;
    			for(int k=0; k<n; k++) {
    				if(abs(a[k]-a[((k-1)+n)%n])>kk) tmp2.push_back(k),tmp2.push_back(((k-1)+n)%n);
    			}
    			if(sz(tmp2)==0) {
    				cout<<1<<"\n";
    				cout<<idx1+1<<" "<<idx2+1<<"\n";
    				return ;
    			}
    			else {
                    sort(tmp2.begin(),tmp2.end());
                    tmp2.erase(unique(tmp2.begin(),tmp2.end()),tmp2.end());
                    int M=sz(tmp2);
                    if(M>6) {
                        swap(a[idx1],a[idx2]);
                        continue;
                    }
    				for(int p=0; p<M; p++) {
    					for(int q=0; q<n; q++) if(tmp2[p]!=q) {
    						int f=1;
    						int idx3=tmp2[p],idx4=q;
    						swap(a[idx3],a[idx4]);
    						for(int k=0; k<n; k++) {
			    				if(abs(a[k]-a[((k-1)+n)%n])>kk) {
			    					f=0;
			    					break;
			    				}
			    			}
			    			if(f) {
			    				cout<<2<<"\n";
			    				cout<<idx1+1<<" "<<idx2+1<<"\n";
			    				cout<<idx3+1<<" "<<idx4+1<<"\n";
			    				return ;
			    			}
			    			swap(a[idx3],a[idx4]);
    					}
    				}	
    			}
    			swap(a[idx1],a[idx2]);
    		}
    	}
    }
    cout<<-1<<"\n";
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