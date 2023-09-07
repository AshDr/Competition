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

const int N = 50 + 10;
const int M = 1e3 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
int dp[N][N][M];
char ans[N][N][M]; //50*50*1000
int n,k,p;
char s[N],res[N];
ll b,P[N];
void init() {
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= k; j++) {
            for(int o = 0; o < p; o++) dp[i][j][o] = 0;
        }
    }
}
void solve() {
    cin >> n >> b >> p >> k;
    cin >> (s + 1);
    init();
    dp[0][0][0] = 1;
    P[0] = 1;
    ll hash = 0;
    for(int i = 1; i <= n; i++) P[i] = P[i - 1] * b % p;
    for(int i = 1; i <= n; i++) hash += (s[i] - 'a' + 1) * 1ll * (P[n - i]) % p,hash %= p;  
    for(int i = 1; i <= n; i++) {
    	for(int j = 0; j <= k; j++) {
    		for(int o = 0; o < p; o++) {
    			for(char ch = 'a'; ch <= 'z'; ch++) {
    				if(ch == s[i] && j == 0) continue;
    				int x = dp[i][j][o];
    				dp[i][j][o] |= dp[i - 1][j - (ch == s[i])][((o - (ch - 'a' + 1) *1ll* P[n - i] % p) % p + p) % p];
    				int y = dp[i][j][o];
                    if(x == 0 && y) ans[i][j][o] = ch;
    			}
    		}
    	}
    }
    
    if(!dp[n][k][hash]) cout << -1 << "\n";
    else {
    	int x = hash, num = k;
    	vector<char> tmp;
        // cout << x << "\n";
    	for(int i = n; i >= 1; i--) {
    		char ch = ans[i][num][x];
            tmp.push_back(ch);
    		x = ((x - (ch - 'a' + 1) * 1ll * P[n - i]) % p + p) % p;
    		num -= (ch == s[i]);
    	}
    	reverse(tmp.begin(), tmp.end());
    	for(auto ch: tmp) cout << ch;
        cout << "\n";
        ll xx = 0;
        for(int i = 0; i < n; i++) {
            xx += ((tmp[i] - 'a' + 1) *1ll* P[n - i - 1])%p;
            xx %=p;
        }
        assert(xx == hash);
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
    cin>>TT;
    while(TT--) solve();
    #ifdef ASHDR
    LOG("Time: %dms\n", int ((clock()
            -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
    #endif
    return 0;
}