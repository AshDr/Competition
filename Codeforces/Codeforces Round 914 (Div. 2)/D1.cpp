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
const ll MOD = 1e9 + 7;
int TT = 1;
vector<int> lg(2);
template <typename T> 
struct STtable {
	vector<T> a;
	vector<vector<T>> st;
	STtable(const vector<T> &b):a(all(b)) {
		int n = a.size(), i, j, k, r;
		while (lg.size() <= n) lg.push_back(lg[lg.size() >> 1] + 1);
		st.assign(lg[n] + 1, vector<T>(n));
		iota(all(st[0]), 0);
		for (j=1; j<=lg[n]; j++)
		{
			r=n-(1<<j);
			k=1<<(j-1);
			for (i=0; i<=r; i++) st[j][i]=a[st[j-1][i]]<a[st[j-1][i+k]]?st[j-1][i+k]:st[j-1][i];
		}
	}
	T rmq(int l,int r) const
	{
		assert(0<=l&&l<=r&&r<a.size());
		int z=lg[r-l+1];
		return max(a[st[z][l]],a[st[z][r-(1<<z)+1]]);
	}
	int rmp(int l,int r) const
	{
		assert(0<=l&&l<=r&&r<a.size()); //[l,r]
		int z=lg[r-l+1];
		return a[st[z][l]]<a[st[z][r-(1<<z)+1]]?st[z][r-(1<<z)+1]:st[z][l];
	}
};
void solve() {
    int n;
    cin >> n;
    vector<int> a(n),b(n);
    for(int i = 0; i < n; i++) {
    	cin >> a[i];
    }
    int f = 1;
	for(int i = 0; i < n; i++) {
		cin >> b[i];
		if(b[i] < a[i]) {
			f = 0;
		}
	}    
	if(!f) {
		cout << "NO\n";
		return ;
	}
	STtable<int> st(a);
	for(int i = 0,j = 0; i < n; i++) {
		while(j < n && (a[j] != b[i] || (j < i && st.rmq(j, i) > b[i]))) ++j;
		if(j >= n || (j >= i && st.rmq(i, j) > b[i])) {
			f = 0;
		}
	}
	cout << (f ? "YES\n" : "NO\n");
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