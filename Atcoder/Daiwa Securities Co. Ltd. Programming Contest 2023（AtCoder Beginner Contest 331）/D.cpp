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
mt19937_64 myrand(chrono::steady_clock::now().time_since_epoch().count());
ll myRand(ll B) {return (ull)myrand()%B;}
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
	int n, q;
	cin >> n >> q;
	vector<vector<int>> grid(n,vector<int>(n));
	vector<vector<ll>> pre(n, vector<ll>(n));
	for(int i = 0; i < n; i++) {
		string s;
		cin >> s;
		for(int j = 0; j < n; j++) {
			grid[i][j] = (s[j] == 'B');
		}
	}
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			pre[i][j] = grid[i][j];
			if(i - 1 >= 0) pre[i][j] += pre[i - 1][j];
			if(j - 1 >= 0) pre[i][j] += pre[i][j - 1];
			if(i - 1 >=0 && j - 1 >= 0) pre[i][j] -= pre[i - 1][j - 1];
		}
	}
	auto calc = [&](int a, int b, int c, int d) {
		int res = pre[c][d];
		if(b - 1 >= 0) res -= pre[c][b - 1];
		if(a - 1 >= 0) res -= pre[a - 1][d];
		if(a - 1 >= 0 && b - 1 >= 0) res += pre[a - 1][b - 1];
		return res;
	};
	for(int i = 0; i < q; i++) {
		ll a,b,c,d;
		cin >> a >> b >> c >> d;
		ll len1 = c - a + 1, len = d - b + 1;
		ll str = a / n, edr = c / n, stc = b / n, edc = d / n;
		if(stc == edc) {
			if(str == edr) {
				cout << calc(a % n , b % n , c % n , d % n) << " \n";
			}
			else {
				ll num = edr - str - 1;
				cout << calc(a % n, b % n, n - 1, d % n) + calc(0, b % n, c % n, d % n) + num * calc(0, b % n, n - 1, d % n) << " \n";
			}
		}else if(stc + 1 == edc) {
			if(str == edr) {
				cout << calc(a % n, b % n, c % n,n - 1) + calc(a %n, 0, c % n, d % n) << " \n";
			}else {
				ll num = edr - str - 1;
 				ll up = calc(a % n, b % n, n - 1,n - 1) + calc(a % n, 0, n - 1, d % n);
 				ll down = calc(0, b % n, c % n, n - 1) + calc(0, 0, c % n, d % n);
 				ll tmp = calc(0, b % n, n - 1,n - 1) + calc(0,0,n - 1, d % n);
 				cout << up + down + tmp * num << " \n";
			}
		}else {
			ll numc = edc - stc - 1;
			ll numr = edr - str - 1;
			if(str == edr) {
				ll left = calc(a % n, b % n, c % n, n - 1),right = calc(a % n, 0,  c % n, d % n);
				ll tmp = calc(a % n, 0, c % n,n - 1);
				cout << left + right + tmp * numc << " \n";
			}else {
				ll up = calc(a % n, b % n, n - 1, n - 1) + calc(a % n, 0, n - 1, d % n) + numc * calc(a % n, 0, n - 1, n - 1);
				ll down = calc(0, b % n, c % n, n - 1) + calc(0, 0, c % n, d % n) + numc *calc(0, 0, c % n, n - 1);
				ll tmp = calc(0, b % n, n - 1, n - 1) + calc(0,0,n - 1,n - 1)  * numc+ calc(0,0,n - 1, d % n);
				cout << up + down + tmp * numr << " \n";
			}
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