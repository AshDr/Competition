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

const int N = 1e6 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
int a[N],vis[N],ans[N];
int n,cnt;
vector<int> G[N];
vector<vector<int>> circle[N];
vector<int> tmp;
void dfs(int u) {
    vis[u]=1;
    ++cnt;
    tmp.push_back(u);
    for(auto v:G[u]) {
        if(!vis[v]) dfs(v);
    }
}
void solve() {
	cin>>n;
    for(int i=1; i<=n; i++) cin>>a[i];
    for(int i=1; i<=n; i++) {
        G[i].push_back(a[i]);
    }

    for(int i=1; i<=n; i++) {
        cnt=0;
        tmp.clear();
        if(!vis[i]) {
            dfs(i);
            circle[cnt].push_back(tmp);
        }
    }
    for(int i=1; i<=n; i++) {
        if(i%2==0 && sz(circle[i])&1) {
            cout<<-1<<"\n";
            return ;
        }
    } 
    for(int d=1; d<=n; d++) {
        if(d&1) {
            for(auto vec:circle[d]) {
                for(int i=0; i<d; i++) {
                    int x=vec[i];
                    int y=vec[(i+1+d/2)%d];
                    ans[x]=y;
                }
            }
        }
        else {
            for(int i=0; i<sz(circle[d]); i+=2) {
                auto vec1=circle[d][i],vec2=circle[d][i+1];
                for(int j=0; j<d; j++) {
                    int x=vec1[j],y=vec2[j];
                    ans[x]=y;
                    ans[y]=vec1[(j+1)%d];
                }
            }
        }
    }
    for(int i=1; i<=n; i++) cout<<ans[i]<<" \n"[i==n];
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