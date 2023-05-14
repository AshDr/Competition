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

const int N = 2e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
const double pi=acos(-1);
int TT = 1;
int n;
typedef pair<double,double> pdd;
pdd a[N];
double get_dis(pdd p, pdd q) {
	return (p.first-q.first)*(p.first-q.first)+(p.second-q.second)*(p.second-q.second);
}
void solve() {
    double x,y;
    cin>>n>>x>>y;
    for(int i=0; i<n; i++) {
    	cin>>a[i].first>>a[i].second;
    }
    double rmx=0,rmn=1e18;
    for(int i=0; i<n; i++) {
    	rmn=min(rmn,get_dis({x,y},a[i]));
    	rmx=max(rmx,get_dis({x,y},a[i]));
    }
    for(int i=0; i<n; i++) {
        int pre=((i-1)%n+n)%n;
        pdd pt;
        if(a[pre].first==a[i].first) {
            pt.first=a[i].first;pt.second=y;
        }else if(a[pre].second==a[i].second) {
            pt.first=x;pt.second=a[i].second;
        }else {
            double k1=(a[i].second-a[pre].second)*1.0/(a[i].first-a[pre].first);
            double b1=a[i].second-k1*a[i].first;
            double k2=-1.0/k1;
            double b2=1.0*y-x*k2;
            double x3=(b2-b1)/(k1-k2),y3=k2*x3+b2;
            pt.first=x3;pt.second=y3;
        }
        if(pt.first>=min(a[i].first,a[pre].first)&&pt.first<=max(a[i].first,a[pre].first)&&pt.second>=min(a[i].second,a[pre].second)&&pt.second<=max(a[i].second,a[pre].second)) {
            rmn=min(rmn,get_dis({x,y}, pt));
            rmx=max(rmx,get_dis({x,y}, pt));
        }
    }
    cout<<pi*(rmx-rmn)<<"\n";
}
int main() {
    #ifdef ASHDR
    freopen("data.in","r",stdin);
    freopen("data.out","w",stdout);
    int nol_cl = clock();
    #endif
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout<<fixed<<setprecision(12);
    //cin>>TT;
    while(TT--) solve();
    #ifdef ASHDR
    LOG("Time: %dms\n", int ((clock()
            -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
    #endif
    return 0;
}