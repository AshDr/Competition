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
#include <functional>
#include <queue>
#include <random>
#include <tuple>
#include <utility>
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
const int M = 2e6 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
int dis[N][N],a[N][N];
char s[N];
int n, m;
const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};
vector<pii> G[M];
void solve() {
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
    	cin >> (s + 1);
    	for(int j = 1; j <= m; j++) a[i][j] = s[j] - '0'; 
    }
    auto check = [&](int x, int y) {
        if(x < 1 || x > n || y < 1 || y > m) return false;
        return true;
    };
    auto gao = [&](int i, int j, int tp) {
        int id = (i - 1) * m + j;
        if(tp == 1) id += n * m;
        return id;
    };
    auto rev = [&](int id, int tp) {
        if(tp == 1) id -= n * m;
        return make_pair((id - 1) / m + 1, (id - 1) % m + 1);
    };
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            for(int k = 0; k < 4; k++) {
                int xx = dx[k] + i,yy = dy[k] + j;
                if(!check(xx, yy)) continue;
                int u0 = gao(i ,j, 0),u1 = gao(i, j, 1),v0 = gao(xx, yy, 0),v1 = gao(xx, yy, 1);
                // cout << i << " " << j << " " << xx << " " <<  yy << "\n";
                if(a[xx][yy] == 0) {
                    G[u1].push_back({v0, 1});
                    G[u0].push_back({v1, 2});
                }else {
                    G[u0].push_back({v1, 1});
                    G[u1].push_back({v0, 2});
                }
            }
        }
    }
    priority_queue<tuple<int,int,int>,vector<tuple<int,int,int>>,greater<tuple<int,int,int>>> heap;
    memset(dis,0x3f,sizeof dis);
    dis[1][1] = 0;
    heap.push({0, gao(1, 1, a[1][1]), a[1][1]});
    while(!heap.empty()) {
        auto [d, id, tp] = heap.top();heap.pop();
        // cout << d << " " <<  id  << " " << tp << " " << "\n";
        pii t = rev(id, tp);
        // cout << t.first << " " << t.second << "\n";
        if(d > dis[t.first][t.second]) continue;
        for(auto [v, w]: G[id]) {
            // cout << v << "\n";
            pii tmp;
            int type = 0;
            if(v > n * m) type = 1;
            tmp = rev(v, type);
            if(dis[tmp.first][tmp.second] > d + w) {
                dis[tmp.first][tmp.second] = d + w;
                heap.push({d + w, v, type});
            }
        }
    }
    cout << dis[n][m] << "\n";
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