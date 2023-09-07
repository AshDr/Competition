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

const int N = 3200 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
char ans[N][N];
void print(int x, int y, int level, int type) {
	if(level == 1) {
		for(int i = x; i < x + 3 * (1 << level); i++) {
			for(int j = y; j < y + 3 * (1 << level); j++) {
				if(type == 0) {
					if(i < x + 3 * (1 << (level - 1)) || j < y + 3 * (1 << (level - 1))) ans[i][j] = '*';
					else ans[i][j] = '.';
				}
				else {
					if(i < x + 3 * (1 << (level - 1)) || j < y + 3 * (1 << (level - 1))) ans[i][j] = '.';
					else ans[i][j] = '*';
				}
				
			}		
		}
		
		return ;
	}
    print(x, y, level - 1, type ^ 1);
    print(x + 3 * (1 << (level - 1)), y, level - 1, type ^ 1);
    print(x, y + 3 * (1 << (level - 1)), level - 1, type ^ 1);
    print(x + 3 * (1 << (level - 1)), y + 3 * (1 << (level - 1)), level - 1, type);
    
}
void solve() {
	int n;
	cin >> n;
	print(1, 1, n, 0);
    int len = 3 * (1 << n);
    for(int i = 1; i <= 3 * (1 << n); i++) {
    	for(int j = 1; j <= 3 * (1 << n); j++) {
    		cout << ans[i][j];
    	}
    	cout << "\n";
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