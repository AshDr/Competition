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
char s[N],t[N];
int n,m;
int prea[55][26],preb[55][26];
void solve() {
    cin>>(s+1)>>(t+1);
    // memset(prea,0,sizeof(prea));
    // memset(preb,0,sizeof(preb));
    n=strlen(s+1);m=strlen(t+1);
    // for(int i=1; i<=n; i++) {
    // 	for(int j=0; j<26; j++) {
    // 		prea[i][j]=prea[i-1][j];
    // 	}
    // 	prea[i][s[i]-'a']++;
    // }
    // for(int i=1; i<=m; i++) {
    // 	for(int j=0; j<26; j++) {
    // 		preb[i][j]=preb[i-1][j];
    // 	}
    // 	preb[i][t[i]-'a']++;
    // }
    for(int i=1; i<=n; i++) {
    	for(int j=1; j<=m; j++) {
    		if(s[i]==t[j]) {
                if(i==1&&j==1) {
                    cout<<"YES\n";
                    cout<<s[i]<<"*"<<"\n";
                    return;
                }
                if(i==n&&j==m) {
                    cout<<"YES\n";
                    cout<<"*"<<s[i]<<"\n";
                    return;
                }
                if(i+1<=n&&j+1<=m&&s[i+1]==t[j+1]) {
                    cout<<"YES\n";
                    cout<<"*"<<s[i]<<s[i+1]<<"*\n";
                    return ;
                }
    			
    		}
    	}
    }
    cout<<"NO\n";
    //ca
    //ab
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