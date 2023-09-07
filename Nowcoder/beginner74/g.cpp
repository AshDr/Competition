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
#include <functional>
#include <queue>
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

const int N = 2e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
int n, m;
ll a[N], pre[N], L[N], R[N];
bool vis[N];
void solve() {
    cin >> n >> m;
    vector<int> stk;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 2; i <= n; i++)  pre[i] = pre[i - 1] + abs(a[i] - a[i - 1]);
    for(int i = n; i >= 1; i--) {
        while(!stk.empty() && a[stk.back()] <= a[i]) L[stk.back()] = i,stk.pop_back();   
        stk.push_back(i);
    }   
    set<int> st; 
    map<int,int> mp;
    for(int i = 1; i <= n; i++) {
        if(L[i] == 0) {
            if(!sz(st)) L[i] = i;
            else {
                auto it = st.lower_bound(a[i]);
                --it;
                L[i] = mp[*it];
            }
        }
        mp[a[i]] = i;
        st.insert(a[i]);
    }
    // while(!stk.empty()) L[stk.back()] = ,stk.pop_back();
    for(int i = 1; i <= n; i++) {
        R[L[i]] = i;
    } 
    for(int i = 1; i <= n; i++) if(!R[i]) R[i] = i;
    // for(int i = 1; i <= n; i++) cout << L[i] << "\n";
    // for(int i = 1; i <= n; i++) cout << R[i] << "\n";
    priority_queue<pair<ll,int>> heap;
    for(int i = 1; i <= n;) {
        ll val = pre[R[i]] - pre[i],t = abs(a[R[i]] - a[i]);
        assert(val >= t);
        if(i != R[i]) heap.push({val - t,i});
        if(i == R[i]) i++;
        else i = R[i];
    }
    while(!heap.empty() && m) {
        ll val = heap.top().first,idx = heap.top().second;heap.pop();
        vis[idx] = 1;
        --m;
    }
    ll ans = 0;
    for(int i = 1; i < n;) {
        // cout << i << " " <<  ans <<"\n";
        if(vis[i]) {
            ans += abs(a[R[i]] - a[i]);
            i = R[i];
        }
        else {
            ans += abs(a[i + 1] - a[i]);
            i++;
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
    //cin>>TT;
    while(TT--) solve();
    #ifdef ASHDR
    LOG("Time: %dms\n", int ((clock()
            -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
    #endif
    return 0;
}