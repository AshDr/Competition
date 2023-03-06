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
#include <tuple>
#include <utility>
#define LOG(FMT...) fprintf(stderr, FMT)
#define sz(x) (int)x.size()
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
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

const int N = 2e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
int n,m,k;
ll s;
int a[N],b[N];
pii c[N];
vector<pii> ans;
bool check(int day) {
	if(day==n+1) return false;
	int mn1=1e9,mn2=1e9,pos1=1,pos2=1;
	for(int i = 1; i <= day; i++) {
		if(mn1>a[i]) {
            mn1=a[i];
            pos1=i;
        }
        if(mn2>b[i]) {
            mn2=b[i];
            pos2=i;
        }
	}
	vector<tuple<ll,int,int>> tmp;
	for(int i = 1; i <= m; i++) {
		if(c[i].first==1){
			tmp.push_back({1ll*mn1*c[i].second,1,i});
		}else{
			tmp.push_back({1ll*mn2*c[i].second,2,i});
		}
	}
	sort(tmp.begin(),tmp.end());
	ll tot=0;
    for(int i = 0; i < k; i++) tot += get<0>(tmp[i]);
    if(tot <= s) {
        ans.clear();
        for(int i = 0; i < k; i++) {
            if(get<1>(tmp[i]) == 1) ans.push_back({get<2>(tmp[i]),pos1});
            else ans.push_back({get<2>(tmp[i]),pos2});
            
        }
        return true;
    } 
	return false;
}
void solve() {
    cin >> n >> m >> k >> s;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) cin >> b[i];
    for(int i = 1; i <= m; i++) {
    	cin >> c[i].first >> c[i].second;
    }

    int l=1,r=n+1;
    while(l<r) {
    	int mid = (l+r)>>1;
    	if(check(mid)) r=mid;
    	else l=mid+1;
    }
    if(l==n+1)cout<<-1<<"\n";
    else {
        cout<<l<<"\n";
        check(l);
        for(auto p: ans) cout << p.first <<" " << p.second << "\n"; 
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