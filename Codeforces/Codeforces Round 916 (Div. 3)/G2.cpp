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
#include <functional>
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
const int M = 2e6 + 10;
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
template<ll P>
struct MLong {
    ll x;
    constexpr MLong() : x{} {}
    constexpr MLong(ll x) : x{norm(x % getMod())} {}
    
    static ll Mod;
    constexpr static ll getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(ll Mod_) {
        Mod = Mod_;
    }
    constexpr ll norm(ll x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr ll val() const {
        return x;
    }
    explicit constexpr operator ll() const {
        return x;
    }
    constexpr MLong operator-() const {
        MLong res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MLong inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr MLong &operator*=(MLong rhs) & {
        x = mul(x, rhs.x, getMod());
        return *this;
    }
    constexpr MLong &operator+=(MLong rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MLong &operator-=(MLong rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MLong & operator++() {
        x = norm(x + 1);
        return *this;
    }
    constexpr MLong & operator--() {
        x = norm(x - 1);
        return *this;
    }
    constexpr MLong &operator/=(MLong rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr MLong operator*(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MLong operator+(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MLong operator-(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MLong operator/(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, MLong &a) {
        ll v;
        is >> v;
        a = MLong(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const MLong &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MLong lhs, MLong rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MLong lhs, MLong rhs) {
        return lhs.val() != rhs.val();
    }
};
 
template<>
ll MLong<0LL>::Mod = ll(1E18) + 9;
 
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
 
constexpr int MOD = 998244353;
using mint = MInt<MOD>;
#define lt idx<<1
#define rt idx<<1|1
struct SCC{
    vector<vector<int> > g, scc;
    vector<int> dfn, low, stk, id;
    vector<bool> ins;
    int ts, n;

    SCC(const vector<vector<int> > &g) : g(g){
        n = (int)g.size();
        dfn.assign(n, 0);
        low.assign(n, 0);
        id.assign(n, -1);
        ins.assign(n, false);
        stk.reserve(n);
        ts = 0;
        build();
    }

    void tarjan(int u){
        dfn[u] = low[u] = ++ts;
        stk.push_back(u);
        ins[u] = 1;
        for(auto j : g[u]){
            if (!dfn[j]){
                tarjan(j);
                low[u] = min(low[u], low[j]);
            }
            else if (ins[j]) low[u] = min(low[u], dfn[j]);
        }
        if (dfn[u] == low[u]){
            int scc_cnt = scc.size();
            scc.push_back({});
            int y;
            do{
                y = stk.back();
                stk.pop_back();
                id[y] = scc_cnt;
                ins[y] = 0;
                scc.back().push_back(y);
            }while(y != u);
        }
    }

    void build(){
        for(int i = 0; i < n; i++){
            if (!dfn[i]){
                tarjan(i);
            }
        }
    }
};
void solve() {
	int n;
	cin >> n;
	vector<int> a(2 * n),L(2 * n + 1, -1),R(2 * n + 1, -1);
	cin >> a;
	for(int i = 0; i < 2 * n; i++) {
		if(L[a[i]] == -1) {
			L[a[i]] = i;
		}else R[a[i]] = i;
	}	
	// for(int i = 1; i <= n; i++) cout << i << " " << L[i] << " " << R[i] << "\n";
	vector<vector<int>> adj(10*n);
	function<void(int, int, int)> build = [&](int idx, int L, int R) {
		if(L == R) {
			adj[idx + n].push_back(a[L]);
			return ;
		}
		int mid = (L + R) >> 1;
		adj[idx + n].push_back((lt) + n);
		adj[idx + n].push_back((rt) + n);
		build(lt, L, mid);
		build(rt, mid + 1, R);
	};
	function<void(int, int, int, int, int, int)> add_edge = [&](int idx, int L, int R, int l, int r, int p) {
		if(r < L || l > R) return ;
		if(l <= L && r >= R) {
			adj[p].push_back(idx + n);
			return ;
		}
		int mid = (L + R) >> 1;
		add_edge(lt, L, mid, l, r, p);
		add_edge(rt, mid + 1, R, l, r, p);
	};
	build(1, 0, 2 * n - 1);
	for(int i = 1; i <= n; i++) {
		if(L[i] + 1 <= R[i] - 1) {
			add_edge(1, 0, 2 * n - 1, L[i] + 1, R[i] - 1, i);
			// cerr << i << " " << L[i] + 1 << " " << R[i] - 1 << "?\n";
		}
	}
	SCC scc(adj);
	int m = sz(scc.scc);
	vector<int> c(m),bad(m);
	vector<int> prt;
	for(int i = 0; i < m; i++) {
		int s = 0;
		for(auto v: scc.scc[i]) {
			s += (v <= n && v > 0);
		}
		c[i] = s;
		if(c[i] > 0) prt.push_back(c[i]);
	}
	// cout << prt << "\n";
	int cnt = 0;
	mint sum = 1;
	for(int i = m - 1; i >= 0; i--) {
		if(c[i] > 0 && !bad[i]) {
			cnt++;
			sum *= 2 * c[i];
		}
		bad[i] |= (c[i] > 0);
		for(auto x: scc.scc[i]) {
			for(auto v: adj[x]) {
				if(scc.id[v] != i) {
					bad[scc.id[v]] |= bad[i];
				}
			}
		}
	}
	cout << cnt << " " << sum << "\n";
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