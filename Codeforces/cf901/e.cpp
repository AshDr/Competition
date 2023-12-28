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
const int M = 4e5 + 10;
const int INF = 1e9;
const ll MOD = 1e9 + 7;
int TT = 1;

void solve() {
	int n;
	cin >> n;
	vector<int> pw5(9),dis(M, INF);
	pw5[0] = 1;
	for(int i = 1; i <= 8; i++) pw5[i] = pw5[i - 1] * 5; 
	auto f = [&](int x, int y, int z) {
		return (x << 2) + (y << 1) + z;
	};
	auto g = [&](int x, int y) {
		return (x << 1) + y;
	};
	auto get = [&](int mask, int idx) {
		return (mask / pw5[idx]) % 5;
	};
	auto bfs = [&]() {
		int st = 0;
		for(int a = 0; a <= 1; a++) {
			for(int b = 0; b <= 1; b++) {
				for(int m = 0; m <= 1; m++) {
					st += pw5[f(a, b, m)] * g(a, b);
				}
			}
		}
		auto extend = [&](int mask, int opt) {
			int ans = 0;
			for(int a = 0; a <= 1; a++) {
				for(int b = 0; b <= 1; b++) {
					for(int m = 0; m <= 1; m++) { //用二进制枚举每一位
						int dat = get(mask, f(a, b, m));
						int c = (dat >> 1), d = dat & 1;
						if(opt == 0) {
							c = c & d;
						}else if(opt == 1) {
							c = c | d;
						}else if(opt == 2) {
							d = c ^ d;
						}else {
							d = d ^ m;
						}
						ans += pw5[f(a, b, m)] * g(c, d);
					}
				}
			}
			return ans;
		};
		queue<int> q;
		q.push(st);
		dis[st] = 0;
		while(!q.empty()) {
			int u = q.front();q.pop();
			for(int i = 0; i < 4; i++) {
				int v = extend(u, i);
				if(dis[v] == INF) {
					dis[v] = dis[u] + 1;
					q.push(v);
				}
			}
		}
		for(int mask = 0; mask < M; mask++) {
			for(int i = 0; i < 8; i++) {
				if(get(mask, i) == 4) {
					for(int j = 1; j <= 4; j++) dis[mask] = min(dis[mask], dis[mask - pw5[i] * j]);
				}
			}
		}
	};
	bfs();
	for(int i = 0; i < n; i++) {
		int A, B, C, D, M;
		cin >> A >> B >> C >> D >> M;
		int mask = pw5[8] - 1;
		int flag = 0;
		for(int o = 0; o < 30; o++) {
			int a = (A >> o) & 1, b = (B >> o) & 1, c = (C >> o) & 1, d = (D >> o) & 1, m = (M >> o) & 1;
			if(get(mask, f(a, b, m)) == 4) {
				mask -= (4 - g(c, d)) * pw5[f(a, b, m)];
			}else if(get(mask, f(a, b, m)) != g(c, d)) {
				cout << -1 << "\n";
				flag = 1;
				break;
			}
		}
		if(!flag) cout << (dis[mask] == INF ? -1: dis[mask]) << "\n";
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
    // cin>>TT;
    while(TT--) solve();
    #ifdef ASHDR
    LOG("Time: %dms\n", int ((clock()
            -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
    #endif
    return 0;
}