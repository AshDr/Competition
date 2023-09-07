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
#include <random>
#include <vector>
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

const int N = 1e3 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
int n, m;
ll k, a[N][N], ans[N][N], vis[N][N];
int ID(int i ,int j) {
    return (i - 1) * m + j;
}
pii revID(int id) {
    return {(id - 1) / m + 1 ,(id - 1) % m + 1};
}
struct DSU {
    std::vector<int> f, siz, mn;
    DSU(int n) : f(n), siz(n, 1), mn(n, 0) { std::iota(f.begin(), f.end(), 0); }
    int leader(int x) {
        while (x != f[x]) x = f[x] = f[f[x]];
        return x;
    }
    bool same(int x, int y) { return leader(x) == leader(y); }
    bool merge(int x, int y) {
        x = leader(x);
        y = leader(y);
        if (x == y) return false;
        siz[x] += siz[y];
        f[y] = x;
        mn[x] = min(mn[x], mn[y]);
        return true;
    }
    int size(int x) { return siz[leader(x)]; }
    int get_min(int x) {return mn[leader(x)]; }
};
const int dx[] = {1,-1,0,0};
const int dy[] = {0,0,1,-1};
void solve() {
    cin >> n >> m >> k;
    DSU dsu(n * m + 1);
    vector<ll> b;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
            dsu.mn[ID(i, j)] = a[i][j];
            b.push_back(a[i][j]);
        }
    }
    sort(b.begin(),b.end());
    b.erase(unique(b.begin(),b.end()),b.end());
    vector<vector<pii>> store(sz(b));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            int pos = lower_bound(b.begin(),b.end(),a[i][j]) - b.begin();
            store[pos].push_back({i,j});
        }
    }
    //4 7 8
    //15 / 7 = 2 15 / 4 = 3
    //n / (n / i)
    auto check = [&](int x, int y){
        if(x < 1 || x > n || y < 1 || y > m) return false;
        return true;
    };
    auto expand = [&](int x, int y) {
        
        for(int i = 0; i < 4; i++) {
            int xx = x + dx[i],yy = y + dy[i];
            if(check(xx, yy) && a[xx][yy] >= a[x][y]) {
                dsu.merge(ID(x, y), ID(xx, yy));
            }
        }
    };
    function<void(int ,int, int, ll ,int&)>dfs = [&](int x, int y, int lead, ll val, int& num) {
        if(num == 0) return ;
        ans[x][y] = val;
        vis[x][y] = 1;
        --num;
        for(int i = 0; i < 4; i++) {
            int xx = x + dx[i],yy = y + dy[i];
            if(check(xx, yy) && !vis[xx][yy] && dsu.leader(ID(xx, yy)) == lead) {
                dfs(xx, yy, lead, val, num);
            }
        }
    };
    auto print = [&](int mxsz, int leader, ll val) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                if(dsu.leader(ID(i ,j)) == leader && a[i][j] == val) {
                    dfs(i, j, leader, val, mxsz);
                    break;
                }
            }
        }
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) cout << ans[i][j] << " \n"[j == m];
        }
    };
    for(int i = sz(b) - 1; i >= 0; i--) {
        ll mx = 0, leader = 0;
        for(auto [x,y]: store[i]) {
            expand(x,y);
            if(mx < dsu.size(ID(x, y)) && dsu.get_min(ID(x, y)) == b[i]) {
                mx = dsu.size(ID(x, y));
                leader = dsu.leader(ID(x, y));
            }
        }
        if(b[i] == 0) continue;
        if(k % b[i] == 0 && mx >= k / b[i]) {
            ll val = b[i], num = k / val;
            cout << "YES\n";
            print(num, leader, val);            
            return ;
        }
    }
    cout << "NO\n";
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