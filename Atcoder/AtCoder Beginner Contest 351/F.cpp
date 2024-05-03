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
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
#include <random>
#define LOG(FMT...) fprintf(stderr, FMT)
#define sz(x) (int)x.size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
using namespace std;
// using namespace __gnu_pbds;
// typedef tree<int,null_type,less<>,rb_tree_tag,tree_order_statistics_node_update> Bst;
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
const int N = 4e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
template<class T>
struct Disc{
    vector<T>d;
    inline void insert(T k){d.push_back(k);}
    inline void init(){
        sort(d.begin(),d.end());
        d.erase(unique(d.begin(),d.end()),d.end());
    }
    inline int size(){return d.size();}
    inline int query(T k){
        return lower_bound(d.begin(),d.end(),k)-d.begin()+1;
    }
    inline void clear(){vector<T>().swap(d);}
};
template<typename T>
struct Fenwick{
    int n;
    std::vector<T> tr;

    Fenwick(int n) : n(n), tr(n + 1, 0){}

    int lowbit(int x){
        return x & -x;
    }

    void modify(int x, T c){
        for(int i = x; i <= n; i += lowbit(i)) tr[i] += c;
    }

    void modify(int l, int r, T c){
        modify(l, c);
        if (r + 1 <= n) modify(r + 1, -c);
    }

    T query(int x){
        T res = T();
        for(int i = x; i; i -= lowbit(i)) res += tr[i];
        return res;
    }

    T query(int l, int r) {
        return query(r) - query(l - 1);
    }

    int find_first(T sum){
        int ans = 0; T val = 0;
        for(int i = __lg(n); i >= 0; i--){
            if ((ans | (1 << i)) <= n && val + tr[ans | (1 << i)] < sum){
                ans |= 1 << i;
                val += tr[ans];
            }
        }
        return ans + 1;
    }

    int find_last(T sum){
        int ans = 0; T val = 0;
        for(int i = __lg(n); i >= 0; i--){
            if ((ans | (1 << i)) <= n && val + tr[ans | (1 << i)] <= sum){
                ans |= 1 << i;
                val += tr[ans];
            }
        }
        return ans;
    }
    int find_kth(int k) {
        int ans = 0,cnt = 0;
        for (int i = 1 << __lg(n);i >= 0;i--)  //这里的20适当的取值，与MAX_VAL有关，一般取lg(MAX_VAL)
        {
            ans += (1 << i);
            if (ans >= n || cnt + tr[ans] >= k)
                ans -= (1 << i);
            else
                cnt += tr[ans];
        }
        return ans + 1;
    }//注意k不能太大

};
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    Disc<int> disc;
    for(int i = 0; i < n; i++) {
    	cin >> a[i];
    	disc.insert(a[i]);
    }
    disc.init();
    Fenwick<ll> fw1(disc.size() + 2), fw2(disc.size() + 2);
    ll ans = 0;
    for(int i = 0; i < n; i++) {
    	if(i > 0) {
    		ll sum = fw1.query(disc.query(a[i]) - 1), num = fw2.query(disc.query(a[i]) - 1);
    		ans += num * a[i] - sum;
    	}
    	fw1.modify(disc.query(a[i]), a[i]);
    	fw2.modify(disc.query(a[i]), 1);
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
    //cin>>TT;
    while(TT--) solve();
    #ifdef ASHDR
    LOG("Time: %dms\n", int ((clock()
            -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
    #endif
    return 0;
}