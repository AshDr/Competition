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
#include <unordered_map>
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
struct node {
	int op,info1,info2,info3;
}a[N],memo[N];
bool cmp(node &x, node &y) {
	if(x.info2 == y.info2) return x.op < y.op;
	return x.info2 < y.info2;
}
int n;
int ans[N],tong[N];
void CDQ(int l, int r) {
	if(l == r) return ;
	int mid = (l + r) >> 1;
	CDQ(l, mid);CDQ(mid + 1,r);
	merge(a + l, a + mid + 1,a + mid + 1, a + r + 1, memo + l, cmp);
	for(int i = l; i <= r; i++) a[i] = memo[i];
	for(int i = l; i <= r; i++) {
		if(a[i]. op == 1 && a[i].info1 <= mid) {
			tong[a[i].info3]++;
		}else if(a[i].op == 2 && a[i].info1 <= mid) {
			tong[a[i].info3]--;
		}else if(a[i].op == 3 && a[i].info1 > mid) {
			if(ans[a[i].info1] == 0x3f3f3f3f) ans[a[i].info1] = 0;
			ans[a[i].info1] += tong[a[i].info3];
		}
	} 
	for(int i = l; i <= r; i++) {
		if(a[i]. op == 1 && a[i].info1 <= mid) {
			tong[a[i].info3]--;
		}else if(a[i].op == 2 && a[i].info1 <= mid) {
			tong[a[i].info3]++;
		}
	} 
}
void solve() {
	cin >> n;
	vector<int> b;
	for(int i = 1; i <= n; i++) {
		a[i].info1 = i;
		cin >> a[i].op >> a[i].info2 >> a[i].info3;
		b.push_back(a[i].info3);
	} 
	sort(b.begin(), b.end());
	b.erase(unique(b.begin(), b.end()), b.end());
	for(int i = 1; i <= n; i++) {
		a[i].info3 = lower_bound(b.begin(), b.end(), a[i].info3) - b.begin() + 1;
	}
	memset(ans, 0x3f, sizeof ans);
	CDQ(1, n);
	for(int i = 1; i <= n; i++) if(ans[i] != 0x3f3f3f3f) cout << ans[i] << "\n";
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