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
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
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
LL gcd(LL x, LL y) {return y == 0 ? x : gcd(y, x % y);}
LL qpow(LL base, LL x, LL mod) {
    LL res = 1;
    base %= mod;
    while(x) {
       if(x & 1) res = (res * base) % mod;
       base = (base * base) % mod;
       x >>= 1;
    } 
    return res;
}
LL exgcd(LL a,LL b,LL &x,LL &y) {
    if(b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    LL d = exgcd(b,a % b,y,x);
    y -= a / b * x;
    return d;
}// (get inv) gcd(a,p) = 1 

const int N = 5e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const LL MOD = 1e9 + 7;
int TT = 1;
char s[N];
int n;
LL dp[N][2][2];
int nxta[N],nxtc[N];
LL calc() {
    nxta[n + 1] = n + 1;
    nxtc[n + 1] = n + 1;
    for(int i = n; i >= 1; i--) {
        nxta[i] = nxta[i + 1];
        nxtc[i] = nxtc[i + 1];
        if(s[i] == 'a') nxta[i] = i;
        if(s[i] == 'c') nxtc[i] = i;
    }
    LL res = 0;
    for(int i = 1; i <= n; i++) {
        res += (nxtc[nxta[i]] - i);
    }
    return res;
}
void solve() {
    cin >> (s + 1);
    n = strlen(s + 1);
    LL ans = 0;
    for(int i = 1; i <= n; i++) {
        if(s[i] == 'a') {
            dp[i][1][0]++;
            dp[i][1][0] += dp[i - 1][0][0];
            dp[i][1][1] += dp[i - 1][0][1];
            dp[i][0][0] += dp[i - 1][1][0];
            dp[i][0][1] += dp[i - 1][1][1];
        }  	
        else if(s[i] == 'c') {
            dp[i][0][0]++;
            dp[i][0][0] += dp[i - 1][0][0];
            dp[i][0][1] += dp[i - 1][0][1];
            dp[i][1][0] += dp[i - 1][1][1];
            dp[i][1][1] += dp[i - 1][1][0];
        }
        else {
            dp[i][0][0]++;
            for(int j = 0; j < 2; j++) {
                for(int k = 0; k < 2; k++) {
                    dp[i][j][k] += dp[i - 1][j][k];
                }
            }
        }
        ans += dp[i][0][0] + dp[i][1][0];
    }   
    cout << ans - calc() << '\n';
}
int main() {
    #ifdef ASHDR
    freopen("data.in","r",stdin);
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