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
int s[N],t[N];
char tmp[N];
int n;
void gaol(int x) {
    for(int i=1; i<=n; i++) {
        if(i+x<=n) s[i]^=s[i+x];
    }
}
void gaor(int x) {
    for(int i=n; i>=1; i--) {
        if(i-x>=1) s[i]^=s[i-x];
    }
}
void solve() {
    cin>>n;
    cin>>(tmp+1);
    for(int i=1; i<=n; i++) s[i]=tmp[i]-'0';
    cin>>(tmp+1);
    for(int i=1; i<=n; i++) t[i]=tmp[i]-'0';
    int t1=0,t2=0,f=0;
    for(int i=1; i<=n; i++) {
        if(s[i]!=t[i]) {
            f=1;
        }
        t1+=s[i];
        t2+=t[i];
    }
    if(min(t1,t2)==0&&max(t1,t2)>0) {
        cout<<-1<<"\n";
        return ;
    }
    if(!f) {
        cout<<0<<"\n";
        return;
    }
    int fp1=0,fp2=0;
    for(int i=n; i>=1; i--) {
        if(s[i]==1) fp1=i;
        if(t[i]==1) fp2=i;
    }
    vector<int> ans;
    if(fp1>fp2) {
        ans.push_back(fp1-fp2);
        gaol(fp1-fp2);
        fp1=fp2;
    }
    for(int i=fp1+1; i<=n; i++) {
        if(s[i]!=t[i]) {
            int step=i-fp1;
            ans.push_back(-step);
            gaor(step);
        }
    }
    int lst=0;
    for(int i=1; i<=n; i++) {
        if(s[i]==1) lst=i;
    }
    for(int i=fp1; i>=1; i--) {
        if(s[i]!=t[i]) {
            int step=lst-i;
            ans.push_back(step);
            gaol(step);
        }
    }
    // for(int i=1; i<=n; i++) cout<<s[i];
    // cout<<"\n";
    cout<<sz(ans)<<"\n";
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
    cin>>TT;
    while(TT--) solve();
    #ifdef ASHDR
    LOG("Time: %dms\n", int ((clock()
            -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
    #endif
    return 0;
}