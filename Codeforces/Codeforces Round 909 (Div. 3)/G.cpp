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
int n, m;
int p[N],dfn[N],siz[N],dfn_cnt;
vector<int> G[N];
int len;
template <typename T>
struct Fenwick {
    const int n;
    std::vector<T> a;
    Fenwick(int n) : n(n), a(n) {}
    void add(int x, T v) {
        for (int i = x; i < n; i += i & -i) {
            a[i] += v;
        }
    }
    T sum(int x) {
        T ans = 0;
        if(x <= 0) return ans;
        for (int i = x; i > 0; i -= i & -i) {
            ans += a[i];
        }
        return ans;
    }
    T rangeSum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
    int find_kth(int k) {
        int ans = 0,cnt = 0;
        for (int i = 1 << __lg(n);i >= 0;i--)  //这里的20适当的取值，与MAX_VAL有关，一般取lg(MAX_VAL)
        {
            ans += (1 << i);
            if (ans >= n || cnt + a[ans] >= k)
                ans -= (1 << i);
            else
                cnt += a[ans];
        }
        return ans + 1;
    }//注意k不能太大
};
int get(int x) {return x / len;} 
struct Q {
    int l,r,x,id;
    friend bool operator < (const Q& x,const Q& y) {
        int l1 = get(x.l),l2 = get(y.l);
        return (l1 == l2) ? (x.r < y.r) : (l1 < l2);
    }
}q[N];
int ans[N];
void dfs(int u, int p) {
	dfn[u] = ++dfn_cnt;siz[u] = 1;
	for(auto v: G[u]) {
		if(v == p) continue;
		dfs(v, u);
		siz[u] += siz[v];
	}
}

void solve() {
    cin >> n >> m;
	int L = 0, R = 0;
    dfn_cnt = 0;
    len = sqrt(n);
    Fenwick<int> fw(n + 1);
    for(int i = 1; i <= n - 1; i++) {
    	int u, v;
    	cin >> u >> v;
    	G[u].push_back(v);
    	G[v].push_back(u);
    }
    for(int i = 1; i <= n; i++) cin >> p[i];
    for(int i = 1; i <= m; i++) {
    	int l, r, x;
    	cin >> l >> r >> x;
    	q[i].l = l;q[i].r = r;q[i].x = x;
    	q[i].id = i;
    }

    dfs(1, 0);
    sort(q + 1, q + 1 + m);
	auto update = [&](int idx, int sign) {
		// assert(pval != 0);
		if(idx == 0) return;
		// cerr << p[idx] <<" "<<dfn[p[idx]]<< " " << sign << "!"<<endl;
		fw.add(dfn[p[idx]],sign);
	};
	auto query = [&](int l, int r, int x) {
		if(l == r) {
		}
		while(L<l) update(L++, -1);
		while(L>l) update(--L, 1);
		while(R<r) update(++R, 1);
		while(R>r) update(R--, -1);
		// cerr << l << " " << r << " " << x << " " << p[x] << " " << dfn[p[x]] <<"done----"<< endl;
		return fw.rangeSum(dfn[x], dfn[x] + siz[x] - 1) > 0;
	};
    for(int i = 1; i <= m; i++) {
    	ans[q[i].id] = query(q[i].l, q[i].r, q[i].x);
    }
    for(int i = 1; i <= m; i++) {
    	cout << (ans[i] ? "YES\n":"NO\n");
    }
    cout << "\n";
    for(int i = 1; i <= n; i++) G[i].clear();
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