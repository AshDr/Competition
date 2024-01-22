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
#include <numeric>
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
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;
    if(n == 1) {
        cout << "YES\n";
        cout << "0\n";
        return ;
    }
    vector<int> b = a;
    sort(a.begin(), a.end());
    int val = a[0] + a[n - 1];
    for(int i = 0; i < n; i++) {
        if(a[i] + a[n - i - 1] != val) {
            cout << "NO\n";
            return ;
        }
    }
    vector<pii> ans;
    map<int,set<int>> mp;
    for(int i = 0; i < n; i++) {
        mp[b[i]].insert(i);
    }
    for(auto [i, st]: mp) {
        if(sz(st) != sz(mp[val - i])) {
            cout << "NO\n";
            return ;
        }   
    }
    if(n & 1) {
        int idx1 = *mp[a[n / 2]].begin(),idx2 = n / 2;
        if(a[n / 2] != b[n / 2]) {
            mp[a[n / 2]].erase(idx1);
            mp[a[n / 2]].insert(idx2);
            mp[b[idx2]].erase(idx2);
            mp[b[idx2]].insert(idx1);
            swap(b[idx1], b[idx2]);
            // cout << idx1 << " " << idx2 << "!\n";

            ans.push_back({idx1,idx2});
        }
    }
    for(int i = 0; i < n; i++) {
        mp[b[i]].erase(i);
        if(b[n - i - 1] + b[i] != val) {
            int curx = b[n - i - 1];
            int idx1 = *mp[val - b[i]].begin(),idx2 = n - i - 1;
            // cout << idx1 << " " << idx2 << "!\n";
            mp[val - b[i]].erase(idx1);
            mp[curx].erase(n - i - 1);
            mp[curx].insert(idx1);
            mp[val - b[i]].insert(idx2);
            ans.push_back({idx1, idx2});
            swap(b[idx1],b[idx2]);
        }else {
            if(n - i - 1 != i) mp[val - b[i]].erase(n - i - 1);
        }
    }
    for(int i = 0; i < n; i++) assert(b[i] + b[n - i - 1] == val);
    cout << "YES\n";
    cout << sz(ans) << "\n";
    for(auto [x, y]: ans) {
        cout << x + 1 << " " << y + 1 << "\n";
    }
    
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