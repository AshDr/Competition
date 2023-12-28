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
#include <array>
#include <bits/stdc++.h>
#include <functional>
#include <queue>
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
struct DSU {
    std::vector<int> f, siz;
    DSU(int n) : f(n), siz(n, 1) { std::iota(f.begin(), f.end(), 0); }
    int leader(int x) {
        while (x != f[x]) x = f[x] = f[f[x]];
        return x;
    }
    bool same(int x, int y) { return leader(x) == leader(y); }
    bool merge(int x, int y) {
        x = leader(x);
        y = leader(y);
        if (x == y) return false;
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    int size(int x) { return siz[leader(x)]; }
};
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(k);
    cin >> a;
    vector<int> cnt(n, 2);
    for(int i = 0; i < k; i++) {
    	a[i]--;
    	cnt[a[i]]--;
    }
    vector<int> use;
    for(int i = 0; i < n; i++) {
    	if(cnt[i] == 1) {
    		use.push_back(i);
    	}
    }
    if(sz(use) <= 1) {
    	cout << 0 << "\n";
    	return ;
    }
    if(sz(use) % 2 == 0) {
    	ll ans = 0;
    	for(int i = 1; i < sz(use); i += 2) {
    		ans += use[i] - use[i - 1];
    	}
    	cout << ans << "\n";
    }else {
    	int m = sz(use);
    	ll res = 0, ans = 1e18;
    	for(int i = 2; i < m; i += 2) res += use[i] - use[i - 1];
    	ans = min(ans, res);
    	res = 0;
   		for(int i = m - 2; i >= 0; i -= 2) res += use[i] - use[i - 1];
   		ans = min(ans, res);
   		vector<ll> pref(m + 1),suf(m + 1);
   		for(int i = 0; i < m; i++) {
   			pref[i + 1] = pref[i];
   			if(i & 1) pref[i + 1] += use[i] - use[i - 1];
   		}
   		for(int i = m - 2; i >= 0; i--) {
   			suf[i] = suf[i + 1];
   			if(i & 1) suf[i] += use[i + 1] - use[i];
   		}
   		for(int i = 1; i < m - 1; i++) {
   			if(i & 1) {
   				ans = min(ans, pref[i] + suf[i + 1] + use[i + 1] - use[i - 1]);
   			}else {
   				ans = min(ans, pref[i] + suf[i + 1]);
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