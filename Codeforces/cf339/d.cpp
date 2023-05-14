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
typedef unsigned int ui;
typedef unsigned long long ull;
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
ll A,cf,cm,m;
ll res_mn,ful;
void solve() {
    cin>>n>>A>>cf>>cm>>m;
    vector<pair<ll,int>> a(n);
    vector<pair<ll,int>> res(n);
    for(int i=0; i<n; i++) cin>>a[i].first,a[i].second=i,res[i]=a[i];
    sort(a.begin(),a.end());
    sort(res.begin(),res.end());
    vector<ll> pre(n);
    pre[0]=a[0].first;
    for(int i=1; i<n; i++) pre[i]=pre[i-1]+a[i].first;
    ll mn=a[0].first;
    int r=n-1;
    ll ans=0;
    auto check = [&](ll cur,ll lb) {
    	ll sum=0;
        int lo=0,hi=n-1;
        while(lo<hi) {
            int mid=(lo+hi+1)>>1;
            if(a[mid].first>=lb) hi=mid-1;
            else lo=mid;
        }
        sum=1ll*(lo+1)*lb-pre[lo];
    	return cur>=sum;
    };
    ll curm=m;
    ll lo=mn,hi=A;
    while(lo<hi) {
        ll mid=(lo+hi+1)>>1;
        if(check(curm,mid)) lo=mid;
        else hi=mid-1;
    }
    res_mn=lo;ful=0;
    ans=max(ans,cm*lo);
    //113
    for(int i=1; i<=n; i++) {
    	if(r>=0&&m>=A-a[r].first) {
            m-=(A-a[r].first);
            pre[r]=pre[r]-a[r].first+A;
            a[r--].first=A;
            // cout<<i<<"?\n";
    	}
    	else break;
    	ll curm=m;
    	ll lo=mn,hi=A;
    	while(lo<hi) {
    		ll mid=(lo+hi+1)>>1;
    		if(check(curm,mid)) lo=mid;
    		else hi=mid-1;
    	}
        // cout<<i<<" "<<lo<<"\n";
    	if(i*cf+cm*lo>ans) {
            res_mn=lo;
            ful=i;
            ans=i*cf+cm*lo;
        }
    }//满级个数
    cout<<ans<<"\n";
    for(int i=0; i<n; i++) {
        if(res[i].first<res_mn) res[i].first=res_mn; 
    }
    for(int i=n-1; i>=0; i--) {
        if(ful) {
            res[i].first=A;
            --ful;
        }
        else break;
    } 
    vector<ll> fin(n);
    for(int i=0; i<n; i++) {
        fin[res[i].second]=res[i].first;
    }
    cout<<fin<<"\n";
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