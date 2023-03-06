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
#include <set>
#include <utility>
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
struct node {
    int x,t,id;
}a[N];
int n,m;
ll mx[N<<2],ans[N];
int cnt[N];
#define lt idx<<1
#define rt idx<<1|1
void push_up(int idx) {
    mx[idx]=max(mx[lt],mx[rt]);
}
void modify(int idx, int pos, ll val, int L, int R){
    if(L==R){
        mx[idx]=val;
        return;
    }
    int mid=(L+R)>>1;
    if(pos<=mid) modify(lt, pos, val, L, mid);
    else modify(rt, pos, val, mid+1, R);
    push_up(idx);
}
int query(int idx, ll val, int L, int R) {
    if(mx[idx]<val) return-1;
    if(L==R){
        return L;
    }
    int mid=(L+R)>>1;
    int res=-1;
    if(mx[lt]>=val) res=query(lt, val, L, mid); 
    else res=query(rt, val, mid+1, R);
    return res;
}
multiset<pii> mult;
void solve() {
    cin>>n>>m;
    for(int i = 1; i <= n; i++) {
        cin>>a[i].x>>a[i].t;
        a[i].id=i;
    }    
    sort(a+1,a+1+n,[&](node x,node y){
        return x.x<y.x;
    });
    for(int i = 1; i <= n; i++) {
        modify(1, i, a[i].x+a[i].t, 1, n);
    }
    for(int i = 1; i <= m; i++) {
        ll p,b;
        cin>>p>>b;
        int eat=query(1, p, 1, n);
        if(eat==-1||a[eat].x>p) {
            mult.insert({p,b});
        }
        else{
            cnt[a[eat].id]++;
            a[eat].t+=b;
            while(!mult.empty()) {
                auto it=mult.lower_bound(make_pair(a[eat].x,-1e9));
                if(it==mult.end()) break;
                if(a[eat].x+a[eat].t>=(*it).first) {
                    a[eat].t += (*it).second;
                    cnt[a[eat].id]++;
                    mult.erase(it);
                }
                else break;
            }
            modify(1, eat, a[eat].x+a[eat].t, 1, n);
        }
    }
    for(int i = 1; i <= n; i++) ans[a[i].id]=a[i].t;
    for(int i = 1; i <= n; i++) cout << cnt[i] << " " <<ans[i] << "\n";
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