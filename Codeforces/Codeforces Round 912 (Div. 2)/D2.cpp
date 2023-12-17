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
int bit = 20, LIM = (1 << 20);
void solve() {
	int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    vector<vector<ll>> f(bit, vector<ll>(LIM)),g(bit, vector<ll>(LIM));
    ll sum = 0;
    for(int i = 0; i < n; i++) {
    	cin >> a[i];
    	sum += (1 << 20) - a[i];
    	for(int o = 0; o < bit; o++) {
    		if(!(a[i] >> o & 1)) {
    			f[o][a[i]] += 1;
    			g[o][a[i]] += a[i] % (1 << o);
    		}
    	}
    }
    for(int t = 0; t < bit; t++) {
    	for(int o = 0; o < bit; o++) {
	    	for(int i = LIM - 1; i >= 0; i--) {
	    		if(i >> o & 1) {
	    			f[t][i ^ (1 << o)] += f[t][i];
	    			g[t][i ^ (1 << o)] += g[t][i];
	    		}
	    	}
    	}
    }
    while(q--) {
    	ll k;
    	cin >> k;
    	if(k >= sum) {
    		cout << (k - sum) / n + (1 << 20) << "\n";
    		continue;
    	}
    	ll ans = 0, cnt = 0;
    	for(int o = 19; o >= 0; o--) {
    		ll t = (cnt + f[o][ans]) * (1 << o) - g[o][ans];
    		if(t <= k) {
    			k -= t;
    			cnt += f[o][ans];
    			ans |= (1 << o);
    		}
    	}
    	cout << ans << "\n";
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