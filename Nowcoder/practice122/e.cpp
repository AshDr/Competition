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
#include <functional>
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
struct OP{
	int tp, info1, info2, info3, w, id;
	OP(int _tp, int _info1, int _info2, int _info3, int _w, int _id): tp(_tp), info1(_info1),info2(_info2),info3(_info3),
	w(_w),id(_id){};
};
template<typename T>
struct Fenwick{
    int n;
    std::vector<T> tr;

    Fenwick(int n) : n(n), tr(n + 1, 0){}

    int lowbit(int x){
        return x & -x;
    }

    void modify(int x, T c){
        for(int i = x; i <= n; i += lowbit(i)) tr[i] += c;
    }

    void modify(int l, int r, T c){
        modify(l, c);
        if (r + 1 <= n) modify(r + 1, -c);
    }

    T query(int x){
        T res = T();
        for(int i = x; i; i -= lowbit(i)) res += tr[i];
        return res;
    }

    T query(int l, int r) {
        return query(r) - query(l - 1);
    }

    int find_first(T sum){
        int ans = 0; T val = 0;
        for(int i = __lg(n); i >= 0; i--){
            if ((ans | (1 << i)) <= n && val + tr[ans | (1 << i)] < sum){
                ans |= 1 << i;
                val += tr[ans];
            }
        }
        return ans + 1;
    }

    int find_last(T sum){
        int ans = 0; T val = 0;
        for(int i = __lg(n); i >= 0; i--){
            if ((ans | (1 << i)) <= n && val + tr[ans | (1 << i)] <= sum){
                ans |= 1 << i;
                val += tr[ans];
            }
        }
        return ans;
    }
    int find_kth(int k) {
        int ans = 0,cnt = 0;
        for (int i = 1 << __lg(n);i >= 0;i--)  //这里的20适当的取值，与MAX_VAL有关，一般取lg(MAX_VAL)
        {
            ans += (1 << i);
            if (ans >= n || cnt + tr[ans] >= k)
                ans -= (1 << i);
            else
                cnt += tr[ans];
        }
        return ans + 1;
    }//注意k不能太大

};
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> G(n + 1);
    for(int i = 1; i <= n - 1; i++) {
    	int u, v;
    	cin >> u >> v;
    	G[u].push_back(v);
    	G[v].push_back(u);
    }
    vector<set<int>> s(n + 1);
    vector<int> prv(n + 1), nxt(n + 1,n + 1);
    function<void(int, int)> dfs = [&](int u, int p) {
    	for(auto v: G[u]) {
    		if(v == p) continue;
    		dfs(v, u);
    		if(sz(s[v]) > sz(s[u])) s[u].swap(s[v]);
    		for(auto val: s[v]) {
    			s[u].insert(val);
    		}
    		s[v].clear();
    	}
    	auto it = s[u].insert(u).first;
    	if(it != s[u].begin()) prv[u] = *prev(it);
    	if(next(it) != s[u].end()) nxt[u] = *next(it);
    };
    dfs(1, 0);
    vector<OP> ops;
    vector<int> ans(m);
    for(int i = 0; i < m; i++) {
    	int ql, qr;
    	cin >> ql >> qr;
    	if(ql == qr) {
    		ans[i] = 0;
    		continue;
    	}
    	if(ql != 1) ops.emplace_back(1, ql - 1, ql, qr, -1, i);
    	ops.emplace_back(1, qr, ql, qr, 1, i); 
    }
    for(int i = 1; i <= n; i++) {
    	ops.emplace_back(0, i, prv[i], nxt[i], 1, 0);
    }
    // for(int i = 1; i <= n; i++) {
    // 	cout << i << " " << prv[i] << " " << nxt[i] << "\n";
    // }
    // return ;
    sort(ops.begin(), ops.end(), [&](const OP& lhs, const OP& rhs){
    	if(lhs.info1 == rhs.info1) return lhs.tp < rhs.tp;
    	return lhs.info1 < rhs.info1;
    });
    for(int i = 0; i < sz(ops); i++) {
    	ops[i].info1 = i;
    }
    int tot = sz(ops);
    Fenwick<int> fw(n + 3);
    function<void(int, int)> cdq = [&](int l, int r) {
    	if(l == r) return ;
    	int mid = (l + r) >> 1;
    	cdq(l, mid);
    	cdq(mid + 1, r);
    	sort(ops.begin() + l, ops.begin() + r + 1, [&](const OP& lhs, const OP& rhs){
    		if(lhs.info2 == rhs.info2) return lhs.tp > rhs.tp; // query should before modify
    		return lhs.info2 < rhs.info2;
    	});
    	vector<int> stk;
    	for(int i = l; i <= r; i++) {
    		if(ops[i].tp == 0 && ops[i].info1 <= mid) {
				fw.modify(ops[i].info3, 1);
				stk.push_back(ops[i].info3);
    		}
			if(ops[i].tp == 1 && ops[i].info1 > mid) {
				int id = ops[i].id, qr = ops[i].info3;
				ans[id] += ops[i].w * fw.query(qr + 1, n + 1);
			}
    		
    	}
    	while(!stk.empty()) {
    		int u = stk.back();stk.pop_back();
    		fw.modify(u, -1);
    	}
    };
	cdq(0, tot - 1);
	for(auto val: ans) cout << val << "\n";

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