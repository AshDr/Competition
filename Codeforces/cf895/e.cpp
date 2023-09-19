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
int n, m, a[N];
char s[N];
#define lt idx<<1
#define rt idx<<1|1
struct node {
	int val[2];
	int lz;
}tr[N << 2];
int tmp0,tmp1;
void push_up(int idx) {
	tr[idx].val[0] = tr[lt].val[0] ^ tr[rt].val[0];
	tr[idx].val[1] = tr[lt].val[1] ^ tr[rt].val[1];
}
void push_down(int idx) {
	tr[lt].lz ^= 1;
	swap(tr[lt].val[0], tr[lt].val[1]);
	tr[rt].lz ^= 1;
	swap(tr[rt].val[0], tr[rt].val[1]);
	tr[idx].lz = 0;
}
void build(int idx, int L, int R) {
	tr[idx].val[0] = tr[idx].val[1] = 0;
	tr[idx].lz = 0;
	if(L == R) {
		tr[idx].val[s[L] != '0'] = a[L]; 
		return ;
	}
	int mid = (L + R) >> 1;
	build(lt, L, mid);
	build(rt, mid + 1, R);
	push_up(idx);
}
void modify(int idx, int L, int R, int l, int r) {
	if(l <= L && r >= R) {
		tmp0 ^= tr[idx].val[0];
		tmp1 ^= tr[idx].val[1];
		tr[idx].lz ^= 1;
		return ;
	}
	int mid = (L + R) >>1;
	push_down(idx);
	if(l <= mid) modify(lt, L, mid, l, r);
	if(r > mid) modify(rt, mid + 1, R, l, r);
	push_down(idx);
}
void solve() {
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    cin >> (s + 1);
	vector<int> ans(2);
	for(int i = 1; i <= n; i++) ans[s[i] != '0'] ^= a[i];
	build(1, 1, n);
	cin >> m;
	for(int i = 1; i <= m; i++) {
		int op, x, y;
		cin >> op;
		if(op == 1) {
			tmp0 = tmp1 = 0;
			cin >> x >> y;
			modify(1, 1, n, x, y);
			ans[0] ^= (tmp0 ^ tmp1);
			ans[1] ^= (tmp0 ^ tmp1);
			// cout << tmp0 << " " << tmp1 << "?\n";
		}else {
			cin >> x;
			cout << ans[x] << " ";
		}
	}
	cout << "\n";
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