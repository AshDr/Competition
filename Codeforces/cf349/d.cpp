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

const int N = 3e3 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
int n, m;
int dis[N][N],mx1[N][3], mx2[N][3];
vector<int> G[N];
void solve() {
	cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
    }
    memset(dis, -1, sizeof dis);
    auto bfs = [&](int st) {
        queue<int> q;
        q.push(st);
        dis[st][st] = 0;
        while(!q.empty()) {
            int u = q.front();q.pop();
            for(auto v: G[u]) {
                if(dis[st][v] != -1) continue;
                dis[st][v] = dis[st][u] + 1;
                q.push(v);
            }    
        }
    };
    for(int i = 1; i <= n; i++) bfs(i);
    for(int i = 1; i <= n; i++) {
        vector<int> tmp(n);
        iota(tmp.begin(), tmp.end(), 1);
        sort(tmp.begin(), tmp.end(), [&](int x, int y) {
            return dis[i][x] > dis[i][y];
        });
        for(int j = 0; j < 3; j++) mx1[i][j] = tmp[j];// i->x top 3 big
        sort(tmp.begin(), tmp.end(), [&](int x, int y) {
            return dis[x][i] > dis[y][i]; 
        });
        // y->x top 3 big
        for(int j = 0; j < 3; j++) mx2[i][j] = tmp[j];
    }
    int ans = 0;
    vector<int> res;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            int a = 0, d = 0;
            if(i == j || dis[i][j] == -1) continue;
            for(int k = 0; k < 3; k++) {
                if(dis[mx2[i][k]][i] != -1 && mx2[i][k] != j && mx2[i][k] != i) {
                    a = mx2[i][k];
                    break;
                }
            }
            for(int k = 0; k < 3; k++) {
                if(dis[j][mx1[j][k]] != -1 && mx1[j][k] != a && mx1[j][k] != i && mx1[j][k] != j) {
                    d = mx1[j][k];
                    break;
                }
            }
            if(dis[a][i] + dis[i][j] + dis[j][d] > ans) {
                ans = dis[a][i] + dis[i][j] + dis[j][d];
                res.clear();
                res.push_back(a);
                res.push_back(i);
                res.push_back(j);
                res.push_back(d);
            }
            a = 0;d = 0;
            for(int k = 0; k < 3; k++) {
                if(dis[j][mx1[j][k]] != -1 && mx1[j][k] != i && mx1[j][k] != j) {
                    d = mx1[j][k];
                    break;
                }
            }
            for(int k = 0; k < 3; k++) {
                if(dis[mx2[i][k]][i] != -1 && mx2[i][k] != j && mx2[i][k] != d && mx2[i][k] != i) {
                    a = mx2[i][k];
                    break;
                }
            }
            if(dis[a][i] + dis[i][j] + dis[j][d] > ans) {
                ans = dis[a][i] + dis[i][j] + dis[j][d];
                res.clear();
                res.push_back(a);
                res.push_back(i);
                res.push_back(j);
                res.push_back(d);
            }
        }
    }
    cout << res << "\n";
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