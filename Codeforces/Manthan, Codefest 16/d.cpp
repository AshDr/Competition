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
#include <random>
#include <set>
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

const int N = 2e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
ll fx[101],fy[101];
int n;
int a[N];
void solve() {
    unordered_map<ll,int> mp;
    cin>>n;
    int ans=0;
    for(int i=1; i<=n; i++) {
        cin>>a[i];
        mp[a[i]]++;
        if(a[i]==0) ++ans; 
    }
    fx[1]=1;fx[2]=0;
    fy[1]=0;fy[2]=1;
    for(int i=3; i<=100; i++) {
        fx[i]=fx[i-1]+fx[i-2];
    	fy[i]=fy[i-1]+fy[i-2];
    }
    
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            if(i==j) continue;
            if(a[i]==0&&a[j]==0) continue;
            // if(ans>0&&!mp[fx[ans]*a[i]+fy[ans]*a[j]]) continue;
            queue<ll> q;
            q.push(a[i]);
            q.push(a[j]);
            mp[a[i]]--;
            mp[a[j]]--;
            for(int k=3; k<=n+1; k++) {
                if(k==n+1) {
                    cout<<n<<"\n";
                    return ;
                }
                ll x=fx[k]*a[i]+fy[k]*a[j];
                if(mp[x]) {
                    --mp[x];
                    q.push(x);
                }else {
                    ans=max(ans,k-1);
                    break;
                }
            }
            while(!q.empty()) {
                int x=q.front();q.pop();
                mp[x]++;
            }
        }
    }
    cout<<ans<<"\n";
    //1e6*500
    //5e8
    //len<=50

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