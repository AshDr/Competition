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
int n;
int dp[N];
ll a[N],pre[N];
template <typename T>
struct Fenwick {
    const int n;
    std::vector<T> a;
    Fenwick(int n) : n(n), a(n,-1e9) {}
    void add(int x, T v) {
        for (int i = x; i < n; i += i & -i) {
            a[i] = max(a[i],v);
        }
    }
    T sum(int x) {
        T ans = -1e9;
        if(x <= 0) return ans;
        for (int i = x; i > 0; i -= i & -i) {
            ans = max(ans,a[i]);
        }
        return ans;
    }
    T rangeSum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
    int find_kth(int k) {
        int ans = 0,cnt = 0;
        for (int i = 1 << __lg(n);i >= 0;i--)  //这里的20适当的取值，与MAX_VAL有关，一般取lg(MAX_VAL)
        {
            ans += (1 << i);
            if (ans >= n || cnt + a[ans] >= k)
                ans -= (1 << i);
            else
                cnt += a[ans];
        }
        return ans + 1;
    }//注意k不能太大
};
void solve() {
    cin>>n;
    Fenwick<int> c(n+2);
    vector<ll> b;
    b.push_back(0);
    for(int i=1;i<=n;i++) cin>>a[i],pre[i]=pre[i-1]+a[i],b.push_back(pre[i]);
   	sort(b.begin(),b.end());
   	b.erase(unique(b.begin(),b.end()),b.end());
   	for(int i=0;i<=n;i++) pre[i]=lower_bound(b.begin(),b.end(),pre[i])-b.begin()+1;
   	dp[0]=0;
   	c.add(pre[0], dp[0]-0);
	for(int i=1; i<=n; i++) {
		int pmx=c.sum(pre[i]);
		dp[i]=dp[i-1];
        dp[i]=max(dp[i],pmx+i);
		c.add(pre[i], dp[i]-i);
	}    	
	cout<<dp[n]<<"\n";
    //dp[i]=max(dp[i],dp[j]+i-j(s[i]>=s[j]));
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