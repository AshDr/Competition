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
#define LOG(FMT...) fprintf(stderr, FMT)
#define sz(x) (int)x.size()
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef unsigned int ui;
typedef unsigned long long ull;
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
mt19937 myrand(chrono::steady_clock::now().time_since_epoch().count());
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

const int N = 5e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
struct node {
	ll tag,mx;	
}tr[N<<2];
int n,b,q;
ll s[N],a[N];
#define lt idx<<1
#define rt idx<<1|1
void push_up(int idx) {
	tr[idx].mx=max(tr[lt].mx,tr[rt].mx);
}
void push_down(int idx) {
	tr[lt].tag+=tr[idx].tag;
	tr[lt].mx+=tr[idx].tag;
	tr[rt].tag+=tr[idx].tag;
	tr[rt].mx+=tr[idx].tag;
	tr[idx].tag=0;
}
void build(int idx, int L, int R) {
	if(L==R) {
		tr[idx].mx=s[L];
		return;
	}
	int mid=(L+R)>>1;
	build(lt, L, mid);
	build(rt, mid+1, R);
	push_up(idx);
}
void modify(int idx, int l, int r, ll val, int L, int R) {
	if(l<=L&&r>=R) {
		tr[idx].tag+=val;
		tr[idx].mx+=val;
		return ;
	}
	push_down(idx);
	int mid=(L+R)>>1;
	if(l<=mid) modify(lt, l, r, val, L, mid);
	if(r>mid) modify(rt, l, r, val, mid+1, R);
	push_up(idx);
}
int search(int idx, int L, int R) {
	if(tr[idx].mx<0) {
		return -1;
	}
	if(L==R) {
		return L;
	}
	push_down(idx);
	int mid=(L+R)>>1;
	int res=search(lt, L, mid);
	if(res==-1) return search(rt, mid+1, R);
	return res;
}
ll query(int idx, int pos, int L, int R) {
	if(L==R) {
		return tr[idx].mx;
	}
	push_down(idx);
	int mid=(L+R)>>1;
	if(pos<=mid) return query(lt, pos, L, mid);
	else return query(rt, pos, mid+1, R);
}
void solve() {
	cin>>n>>b>>q;
	for(int i=1; i<=n; i++) {
		cin>>a[i];
		a[i]-=b;
		s[i]=s[i-1]+a[i];
	}
	build(1, 1, n);
	for(int i=1; i<=q; i++) {
		int c;
		ll x;
		cin>>c>>x;
		x-=b;
		modify(1, c, n, x-a[c], 1, n);
		a[c]=x;
		int p=search(1,1,n);
		if(p==-1) p=n;
		cout<<1.0*query(1, p, 1, n)/p+b<<"\n";
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
    cout<<fixed<<setprecision(10);
    //cin>>TT;
    while(TT--) solve();
    #ifdef ASHDR
    LOG("Time: %dms\n", int ((clock()
            -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
    #endif
    return 0;
}