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

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n),b(n);
    for(int i = 0; i < n; i++) {
    	vector<int> row(m);
    	cin >> row;
    	a[i] = row;
    }
    for(int i = 0; i < n; i++) {
    	vector<int> row(m);
    	cin >> row;
    	b[i] = row;
    }
    vector<int> rowid(n);
    iota(rowid.begin(), rowid.end(), 0);
    int ans = -1;
    vector<int> prer(n), prec(m);
    iota(prer.begin(), prer.end(), 0);
    iota(prec.begin(), prec.end(), 0);
    auto calc = [&](vector<int> pre, vector<int> aft)->int {
    	int res = 0;
    	int len = sz(pre);
    	for(int i = 0; i < len - 1; i++) {
    		for(int j = 0; j < len - 1; j++) {
    			if(aft[j] > aft[j + 1]) {
    				swap(aft[j], aft[j + 1]);
    				++res;
    			}
    		}
    	}
    	assert(pre == aft);
    	return res;
    };
    do {
    	vector<int> colid(m);
    	iota(colid.begin(), colid.end(), 0);
    	do {
    		int f = 1;
    		for(int i = 0; i < n; i++) {
    			for(int j = 0; j < m; j++) {
    				int r = rowid[i],c = colid[j];
    				if(a[r][c] != b[i][j]) {
    					f = 0;
    				}
    			}
    		}
    		if(f) {
    			int x = calc(prer, rowid),y = calc(prec, colid);
    			if(ans == -1 || ans > x + y) {
    				ans = x + y;
    			}
    		}
    	}while(next_permutation(colid.begin(), colid.end()));

    }while(next_permutation(rowid.begin(), rowid.end()));
    //120*120
	cout << ans << "\n";
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