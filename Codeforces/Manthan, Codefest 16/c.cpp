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
#include <cctype>
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

const int N = 1e5 + 10;
const int M = 1e6 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
int n,m;
string t,s[N];
namespace AC_automation {
    int trie[M][30],val[M],fail[M],tot;
    void init() {
        memset(val,-1,sizeof val);
    }
    void build_trie(string s,int id) {
        int len = s.size();
        int now = 0;
        for(int i = 0 ; i < len ; i++) {
            int t = s[i] - 'a';
            if(!trie[now][t]) trie[now][t] = ++tot;
            now = trie[now][t]; 
        }
        val[now]=id;
    }
    void get_fail() {
        queue<int> q;
        for(int i  = 0 ; i < 26; i++) if(trie[0][i]) fail[trie[0][i]] = 0,q.push(trie[0][i]);
        while(!q.empty()) {
            int now = q.front();q.pop();
            for(int i = 0 ; i < 26; i++) {
                if(trie[now][i]) fail[trie[now][i]] = trie[fail[now]][i],q.push(trie[now][i]);
                else trie[now][i] = trie[fail[now]][i]; 
            }
        }
    }  
    int AC_query(string ss) {
        int len = ss.size();
        int res = 0,now = 0;
        for(int i = 0 ; i < len; i++) {
            now = trie[now][ss[i] - 'a'];
            for(int  j = now; j && ~val[j]; j = fail[j]) {
                res += val[j];
                val[j] = -1;
            } 
        }
        return res;
    }
}
using namespace AC_automation;
int dp[N];
void solve() {
    cin>>n;
    cin>>t;
    cin>>m;
    init();
    for(int i=1; i<=m; i++) {
    	cin>>s[i];
    	string tt=s[i];
    	transform(tt.begin(),tt.end(),tt.begin(),::tolower);
    	build_trie(tt, i);
    }
    get_fail();
    int cur=0;
    reverse(t.begin(), t.end());
    t="#"+t;
    dp[0]=1;
    for(int i=1; i<=n; i++) {
        cur=trie[cur][t[i]-'a'];
        for(int j=cur; j; j=fail[j]) {
            int id=val[j];
            if(id>0&&dp[i-sz(s[id])]) {
                dp[i]=val[j];
            }
        }
    }
    assert(dp[n]>0);
    vector<string> res;
    for(int i=n; i>=1; i-=sz(s[dp[i]])) {
        // cout<<i<<" "<<dp[i]<<"\n";
        res.push_back(s[dp[i]]);
    }
    cout<<res<<"\n";
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