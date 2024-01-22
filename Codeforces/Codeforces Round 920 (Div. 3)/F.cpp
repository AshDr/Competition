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
const int SQRT = 200;
ll a[N];
ll pre[N][SQRT],ppre[N][SQRT];
int cnt[N][SQRT];
void solve() {
    int n, q;
    cin >> n >> q;
    vector<ll> ans(q);
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int d = 1; d < SQRT; d++) {
        for(int i = 1; i <= n; i++) {
            if(i <= d) pre[i][d] = a[i],ppre[i][d] = a[i],cnt[i][d] = 1;
            else {
                pre[i][d] = pre[i - d][d] + a[i];
                cnt[i][d] = cnt[i - d][d] + 1;
                ppre[i][d] = ppre[i - d][d] + a[i] * cnt[i][d];
            }
        }
    }
    vector<vector<tuple<int,int,int>>> Q(n + 1);
    for(int i = 0; i < q; i++) {
    	int s, d, k;
    	cin >> s >> d >> k;
    	Q[d].push_back({i, s, k});
    }
    for(int d = 1; d <= n; d++) {
    	for(auto [id, s, k]: Q[d]) {
            if(d < SQRT) {
                int ed = s + (k - 1) * d;
                ll val = ppre[ed][d] - (s - d >= 0 ? ppre[s - d][d] : 0),tmp = pre[ed][d] - (s - d >= 0 ? pre[s - d][d] : 0);
                ll num = (s - 1) / d;
                val -= tmp * num;
                //k <= (s - 1) / d;
                // cout << s<< " " << ed<< "!\n";
                ans[id] = val; 
            }else {
                ll sum = 0;
                int cnt = 1;
                for(int i = s; i <= n && cnt <= k; i += d,++cnt) {
                    sum += a[i] * cnt;
                }
                ans[id] = sum;
            }
    	}
    }
    cout << ans << "\n";
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