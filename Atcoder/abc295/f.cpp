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
string L,R;
string s,quer;
ll memo[20][20][20][2][2];
int len,digit;
int nxt[20];
void init(string ss) {
    nxt[1]=0;
    int j=0;
    for(int i=2; i<sz(ss); i++) {
        while(j&&ss[j+1]!=ss[i]) j=nxt[j];
        if(ss[j+1]==ss[i]) ++j;
        nxt[i]=j;
    }
}
ll dfs(int cur, int oknum, int matchpos, int f, int g) {
    if(cur>=len) return oknum;
    if(memo[cur][oknum][matchpos][f][g]!=-1) return memo[cur][oknum][matchpos][f][g];
    int limit=9;
    if(f==1) limit=s[cur]-'0';
    ll res=0;
    for(int i=0; i<=limit; i++) {
        int tmp=matchpos,pp=0;
        if(!g||i!=0) {
            while(tmp&&i!=quer[tmp+1]-'0') tmp=nxt[tmp];
            if(quer[tmp+1]-'0'==i) ++tmp;
            if(tmp==sz(quer)-1) {
                tmp=nxt[tmp];
                pp=1;
                // cout<<"?\n";
            }
        }
        res+=dfs(cur+1,oknum+pp,tmp,f&&(i==s[cur]-'0'),g&&(i==0));
    }
    return memo[cur][oknum][matchpos][f][g]=res;
}
ll gao(string x) {
    s=x;
    len=sz(s);
    memset(memo,-1,sizeof memo);
    return dfs(0,0,0,1,1);
}
void solve() {
	cin>>quer>>L>>R;
    int tmp=0;
    auto check = [&](string s) {
       int pos=0,cnt=0;
       while((pos=s.find(quer,pos))!=string::npos) {
            pos++;
            ++cnt;
       }
       return cnt;
    };
	tmp=check(L);
    quer="#"+quer;
    init(quer);
    // cout<<gao(R)<<" "<<gao(L)<<"\n";
    cout<<gao(R)-gao(L)+tmp<<"\n";
    //2 2 x
    //1 2 2
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