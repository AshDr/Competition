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
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
#include <random>
#define LOG(FMT...) fprintf(stderr, FMT)
#define sz(x) (int)x.size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
using namespace std;
// using namespace __gnu_pbds;
// typedef tree<int,null_type,less<>,rb_tree_tag,tree_order_statistics_node_update> Bst;
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

ll floor(ll x, ll m) {
    ll r = (x % m + m) % m;
    return (x - r) / m;
}// neg floor (-1, 3) = -1
const int N = 2e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
int vis[61][61][61][61];
struct State{
	int x1,y1,x2,y2;
	int step;
};
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0,0,-1,1};
void solve() {
	int n;
	cin >> n;
	vector<string> grid(n);
	int sx1 = -1, sx2 = -1, sy1 = -1, sy2 = -1;
	for(int i = 0; i < n; i++) {
		cin >> grid[i];
		for(int j = 0; j < n; j++) {
			if(grid[i][j] == 'P') {
				if(sx1 == -1) {
					sx1 = i;
					sy1 = j;
				}else {
					sx2 = i;
					sy2 = j;
				}
			}
		}
	}
	queue<State> q;
	q.push({sx1,sy1,sx2,sy2, 0});
	auto check = [&](int x, int y) {
		if(x < 0 || x >= n || y < 0 || y >= n) return false;
		return true;
	};
	vis[sx1][sy1][sx2][sy2] = 1;
	while(!q.empty()) {
		auto [x1, y1, x2, y2, step] = q.front();q.pop();
		if(x1 == x2 && y1 == y2) {
			cout << step << "\n";
			return ;
		}
		for(int i = 0; i < 4; i++) {
			int xx1 = x1 + dx[i],yy1 = y1 + dy[i];
			int xx2 = x2 + dx[i],yy2 = y2 + dy[i];
			if(check(xx1, yy1)) {
				if(grid[xx1][yy1] == '#') xx1 = x1,yy1 = y1;
			}else {
				if(xx1 < 0) xx1 = 0;
				if(xx1 >= n) xx1 = n - 1;
				if(yy1 < 0) yy1 = 0;
				if(yy1 >= n) yy1 = n - 1;
			}

			if(check(xx2, yy2)) {
				if(grid[xx2][yy2] == '#') xx2 = x2,yy2 = y2;
			}else {
				if(xx2 < 0) xx2 = 0;
				if(xx2 >= n) xx2 = n - 1;
				if(yy2 < 0) yy2 = 0;
				if(yy2 >= n) yy2 = n - 1;
			}
			if(!vis[xx1][yy1][xx2][yy2]) {
				vis[xx1][yy1][xx2][yy2] = 1;
				q.push({xx1,yy1,xx2,yy2,step+1});
			}
		}
	}
	cout << "-1\n";
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