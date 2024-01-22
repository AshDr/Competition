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
#include <ostream>
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

ll floor(ll x, ll m) {
    ll r = (x % m + m) % m;
    return (x - r) / m;
}// neg floor (-1, 3) = -1
const int N = 2e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
const ll M1 = 998244353;
const ll M2 = 1e9 + 7;
struct hsh{
    ll w1,w2;
    hsh operator * (const int w){
        return {1ll*w1*w%M1,1ll*w2*w%M2};
    }
    hsh operator * (const hsh w){
        return {1ll*w1*w.w1%M1,1ll*w2*w.w2%M2};
    }
    hsh operator + (const hsh w){
        return {(w1+w.w1)%M1,(w2+w.w2)%M2};
    }
    hsh operator - (const hsh w){
        return {(w1+M1-w.w1)%M1,(w2+M2-w.w2)%M2};
    }
    bool operator == (const hsh w){
        return (w1==w.w1)&&(w2==w.w2);
    }
    ll wt(){
        return M2*w1+w2;
    }
    friend ostream operator << (ostream &os, hsh& x) {
    	os << x.w1 << " " << x.w2;
    }
}pw[N+50],inv[N+50],h[N+50],h2[N+50];
int n;
void init(int n) {
	ll b1 = myRand(M1) + 1, b2 = myRand(M2) + 1;
	pw[0] = inv[0] = {1, 1};
	pw[1] = {b1, b2};
	inv[1] = {qpow(b1, M1 - 2, M1), qpow(b2, M2 - 2, M2)};
	for(int i = 2; i <= n; i++) {
		pw[i] = pw[i - 1] * pw[1];
		inv[i] = inv[i - 1] * inv[1];
 	}
}
/*
h[i]=h[i-1]+pw[i]*s[i];
h2[i]=h2[i-1]+pw[i]*s[n+1-i];
*/
hsh get(int l,int r){
    return (h[r]-h[l-1])*inv[l-1];
}
hsh get2(int l,int r){
    swap(l,r);
    l=n+1-l; r=n+1-r;
    return (h2[r]-h2[l-1])*inv[l-1];
}
void solve() {
    
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