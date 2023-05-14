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

const int N = 2e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
struct node {
	ll x,y;
	int id;
}a[N];
int n;
void solve() {
    cin>>n;
    for(int i=1; i<=n; i++) {
    	cin>>a[i].x>>a[i].y;
    	a[i].id=i;
    }
    sort(a+1,a+1+n,[&](node p, node q){
    	if(p.x==q.x) return p.y<q.y;
    	return p.x<q.x;
    });
	for(int i=2; i<n; i++) {
		if(a[i].x==a[i+1].x) {
			if(a[i-1].x!=a[i].x){
              cout<<a[i-1].id<<" "<<a[i].id<<" "<<a[i+1].id<<"\n";
              return ;  
            } 
		}
		if(a[i-1].y==a[i].y&&a[i].y==a[i+1].y) continue;
    
		if(a[i].y==a[i+1].y) {
            if(a[i-1].y!=a[i].y) {
                cout<<a[i-1].id<<" "<<a[i].id<<" "<<a[i+1].id<<"\n";
                return ;
            }
        }else {
            double k=1.0*(a[i+1].y-a[i].y)/(1.0*a[i+1].x-a[i].x);
                double b=1.0*a[i].y-1.0*a[i].x*k;
                // cout<<k<<" "<<b<<"\n";
                if(fabs(a[i-1].x*k+b-a[i-1].y)>1e-8) {
                    cout<<a[i-1].id<<" "<<a[i].id<<" "<<a[i+1].id<<"\n";
                    return ;
                }
        }
	}
    // assert(0);
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
    //cin>>TT;
    while(TT--) solve();
    #ifdef ASHDR
    LOG("Time: %dms\n", int ((clock()
            -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
    #endif
    return 0;
}