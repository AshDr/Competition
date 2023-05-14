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
const double eps=1e-8;
typedef pair<double,double> pdd;
int TT = 1;
int n;
pii a[N];
// bool check(pii pt1, pii pt2, pii pt3) {
// 	if(pt1.first==pt2.first) {
// 		if((pt1.second+pt2.second)%2==0 && pt3.second==(pt1.second+pt2.second)/2) {
//             return true;
//         }
//         return false;
//     }
// 	if(pt1.second==pt2.second) {
// 		if((pt1.first+pt2.first)%2==0 && pt3.first==(pt1.first+pt2.first)/2) {
//             return true;
//         }
// 	    return false;
//     }
// 	pdd pt4={1.0*(pt1.first+pt2.first)/2,1.0*(pt1.second+pt2.second)/2};
// 	double k=1.0*(pt2.second-pt1.second)/(pt2.first-pt1.first),b=pt1.second-k*pt1.first;
// 	double k_=-1.0/k,b_=pt4.second-k_*pt4.first;
// 	if(fabs(pt3.first*k_+b_-pt3.second)<eps) return true;
// 	return false;
// }
int get_dis(pii x, pii y) {
    return (x.first-y.first)*(x.first-y.first)+(x.second-y.second)*(x.second-y.second);
}
bool check(pii pt1, pii pt2, pii pt3) {
    if(pt1.first==pt2.first&&pt2.first==pt3.first) return false;
    if(pt1.second==pt2.second&&pt2.second==pt3.second) return false;
    double k=1.0*(pt2.second-pt1.second)/(pt2.first-pt1.first),b=pt1.second-k*pt1.first;
    if(fabs(pt3.first*k+b-pt3.second)<eps) return false;
    
    if(get_dis(pt1, pt2)==get_dis(pt1, pt3)) return true;
    if(get_dis(pt2, pt1)==get_dis(pt2, pt3)) return true;
    if(get_dis(pt3, pt1)==get_dis(pt3, pt2)) return true;
    return false;
}
void solve() {
	cin>>n;
	int ans=0;
    for(int i=1; i<=n; i++) cin>>a[i].first>>a[i].second;
    for(int i=1; i<=n; i++) {
    	for(int j=i+1; j<=n; j++) {
    		for(int k=j+1; k<=n; k++) {
    			if(check(a[i],a[j],a[k])) ++ans;
    		}
    	}
    }
    cout<<ans<<"\n";
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