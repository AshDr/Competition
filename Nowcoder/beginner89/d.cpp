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
#include <cstdio>
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <unordered_map>
#include <cassert>
#include <functional>
#include <chrono>
#include <cstring>
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
int TT = 1;
using ll = long long;
template<class T>
constexpr T power(T a, ll b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
 
constexpr ll mul(ll a, ll b, ll p) {
    ll res = a * b - ll(1.L * a * b / p) * p;
    res %= p;
    if (res < 0) {
        res += p;
    }
    return res;
} 
template<int P>
struct MInt {
    int x;
    constexpr MInt() : x{} {}
    constexpr MInt(ll x) : x{norm(x % getMod())} {}
    
    static int Mod;
    constexpr static int getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(int Mod_) {
        Mod = Mod_;
    }
    constexpr int norm(int x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr int val() const {
        return x;
    }
    explicit constexpr operator int() const {
        return x;
    }
    constexpr MInt operator-() const {
        MInt res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MInt inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr MInt &operator*=(MInt rhs) & {
        x = 1LL * x * rhs.x % getMod();
        return *this;
    }
    constexpr MInt &operator+=(MInt rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MInt &operator-=(MInt rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MInt & operator++() {
        x = norm(x + 1);
        return *this;
    }
    constexpr MInt & operator--() {
        x = norm(x - 1);
        return *this;
    }
    constexpr MInt &operator/=(MInt rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr MInt operator*(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MInt operator+(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MInt operator-(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MInt operator/(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, MInt &a) {
        ll v;
        is >> v;
        a = MInt(v);
        return is;
    }
    bool sqrt(MInt &res) const {
        if (P == 2 || x == 0) {
          res = *this;
          return true;
        }
        if (pow(*this, (P - 1) / 2) != 1) return false;
        if (P % 4 == 3) {
          res = pow(*this, (P + 1) / 4);
          return true;
        }
        int pw = (P - 1) / 2;
        int K = 30;
        while((1 << K) > pw) K--;
        while(true) {
          MInt t = (ull)rng() % P;
          MInt a = 0, b = 0, c = 1;
          for (int k = K; k >= 0; k--) {
            a = b * b;
            b = b * c * 2;
            c = c * c + a * *this;
            if (((pw >> k) & 1) == 0) continue;
            a = b;
            b = b * t + c;
            c = c * t + a * *this;
          }
          if (b == 0) continue;
          c -= 1;
          c *= MInt() - b.inv();
          if (c * c == *this) {
            res = c;
            return true;
          }
        }
        assert(false);
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const MInt &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MInt lhs, MInt rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MInt lhs, MInt rhs) {
        return lhs.val() != rhs.val();
    }
};
template<>
int MInt<0>::Mod = 998244353;
 
template<int V, int P>
constexpr MInt<P> CInv = MInt<P>(V).inv();
 
constexpr int MOD = 1e9+7;
using mint = MInt<MOD>;
void solve() {
	int n, m, q, x;
	cin >> n >> m >> q >> x;
	vector<vector<int> > G(n + 1);
	for(int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	vector<int> dis(n + 1);
	vector<int> cnt(min(5000,n + 1));
	fill(dis.begin(), dis.end(), -1);
	auto bfs = [&](int st) {
		queue<int> qq;
		qq.push(st);
		dis[st] = 0;
		while(!qq.empty()) {
			int u = qq.front();qq.pop();
			for(auto v: G[u]) {
				if(dis[v] == -1) {
					dis[v] = dis[u] + 1;
					cnt[dis[v]]++;
					qq.push(v);
				}
			}
		}
	};
	bfs(x);
	vector<vector<mint>> dp(min(5000,n) + 1, vector<mint>(min(5000,n) + 1));
	dp[0][0] = 1;
	vector<mint> pref(min(5000, n) + 1);
	pref[0] = 1;
	for(int i = 1; i <= min(5000, n); i++) {
		dp[i][0] = 1;
		if(!cnt[i]) continue;
		for(int j = min(5000, n); j >= 1; j--) {
			dp[i][j] = pref[j - 1] * cnt[i];
			pref[j] += dp[i][j];
			// cout << i << " " << j << " " << dp[i][j] << "\n";
		}
	}
	//dp[i][j] += dp[k][j - 1];
	while(q--) {
		int k;
		cin >> k;
		mint ans = 0;
		for(int i = 1; i <= min(5000, n); i++) {
			if(cnt[i]) ans += dp[i][k];
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