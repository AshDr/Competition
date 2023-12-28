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

const int N = 2e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
int TT = 1;
/*
圆点方点相间
原图中u->v必经点=u->v上圆点的数量=树上距离/2 + 1 
度数为1的圆点都对应唯一一个方点
每条边对应唯一一个方点
圆方树是无根树
*/
using ll = long long;
template<class T>
constexpr T power(T a, ll b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
 
constexpr ll mul(ll a, ll b, ll p) {
    ll res = a * b - ll(1.L * a * b / p) * p;
    res %= p;
    if (res < 0) {
        res += p;
    }
    return res;
}
template<ll P>
struct MLong {
    ll x;
    constexpr MLong() : x{} {}
    constexpr MLong(ll x) : x{norm(x % getMod())} {}
    
    static ll Mod;
    constexpr static ll getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(ll Mod_) {
        Mod = Mod_;
    }
    constexpr ll norm(ll x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr ll val() const {
        return x;
    }
    explicit constexpr operator ll() const {
        return x;
    }
    constexpr MLong operator-() const {
        MLong res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MLong inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr MLong &operator*=(MLong rhs) & {
        x = mul(x, rhs.x, getMod());
        return *this;
    }
    constexpr MLong &operator+=(MLong rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MLong &operator-=(MLong rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MLong & operator++() {
        x = norm(x + 1);
        return *this;
    }
    constexpr MLong & operator--() {
        x = norm(x - 1);
        return *this;
    }
    constexpr MLong &operator/=(MLong rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr MLong operator*(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MLong operator+(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MLong operator-(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MLong operator/(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, MLong &a) {
        ll v;
        is >> v;
        a = MLong(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const MLong &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MLong lhs, MLong rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MLong lhs, MLong rhs) {
        return lhs.val() != rhs.val();
    }
};
 
template<>
ll MLong<0LL>::Mod = ll(1E18) + 9;
 
template<int P>
struct MInt {
    int x;
    constexpr MInt() : x{} {}
    constexpr MInt(ll x) : x{norm(x % getMod())} {}
    
    static int Mod;
    constexpr static int getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(int Mod_) {
        Mod = Mod_;
    }
    constexpr int norm(int x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr int val() const {
        return x;
    }
    explicit constexpr operator int() const {
        return x;
    }
    constexpr MInt operator-() const {
        MInt res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MInt inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr MInt &operator*=(MInt rhs) & {
        x = 1LL * x * rhs.x % getMod();
        return *this;
    }
    constexpr MInt &operator+=(MInt rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MInt &operator-=(MInt rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MInt & operator++() {
        x = norm(x + 1);
        return *this;
    }
    constexpr MInt & operator--() {
        x = norm(x - 1);
        return *this;
    }
    constexpr MInt &operator/=(MInt rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr MInt operator*(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MInt operator+(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MInt operator-(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MInt operator/(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, MInt &a) {
        ll v;
        is >> v;
        a = MInt(v);
        return is;
    }
    bool sqrt(MInt &res) const {
        if (P == 2 || x == 0) {
          res = *this;
          return true;
        }
        if (pow(*this, (P - 1) / 2) != 1) return false;
        if (P % 4 == 3) {
          res = pow(*this, (P + 1) / 4);
          return true;
        }
        int pw = (P - 1) / 2;
        int K = 30;
        while((1 << K) > pw) K--;
        while(true) {
          MInt t = (ull)rng() % P;
          MInt a = 0, b = 0, c = 1;
          for (int k = K; k >= 0; k--) {
            a = b * b;
            b = b * c * 2;
            c = c * c + a * *this;
            if (((pw >> k) & 1) == 0) continue;
            a = b;
            b = b * t + c;
            c = c * t + a * *this;
          }
          if (b == 0) continue;
          c -= 1;
          c *= MInt() - b.inv();
          if (c * c == *this) {
            res = c;
            return true;
          }
        }
        assert(false);
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const MInt &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MInt lhs, MInt rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MInt lhs, MInt rhs) {
        return lhs.val() != rhs.val();
    }
};
template<>
int MInt<0>::Mod = 998244353;
 
template<int V, int P>
constexpr MInt<P> CInv = MInt<P>(V).inv();
 
constexpr int MOD = 998244353;
using mint = MInt<MOD>;
template<class T>
struct BlockCutTree{ //只适用于连通无向简单图
    int n;
    vector<vector<T> > g, ng;//原图 与 新图(树)
    vector<int> dfn, low, stk;
    vector<bool> cut;
    int root, ts, cnt;
    int conn;

    BlockCutTree(const vector<vector<T> > &g) : n(int(g.size())), g(g) {
        cut.assign(n, false);
        dfn.assign(n, 0);
        low.assign(n, 0);
        ng.assign(n, {});
        ts = 0; cnt = n; //0~n-1 n~...
        conn = 0;
        // 不用特判根是不是割点
        for(root = 0; root < n; root++){
            if (dfn[root] == 0){
                conn += 1;
                stk.clear(); //注意清空 每次对于一个子图 栈里会剩一个点
                tarjan(root, -1);
            }
        }
    }
    void tarjan(int u, int p){
        dfn[u] = low[u] = ++ts;
        stk.push_back(u);
        for(auto &v : g[u]){
            if (!dfn[v]){
                tarjan(v, u);                
                low[u] = min(low[u], low[v]);
                if (low[v] >= dfn[u]){
                    ng.push_back({});
                    int x;
                    do{
                        x = stk.back();
                        stk.pop_back();
                        ng[x].push_back(cnt);
                        ng[cnt].push_back(x);
                    }while(x != v); // 不弹u
                    ng[u].push_back(cnt);
                    ng[cnt].push_back(u);
                    cnt++;//新建方点
                }
            }
            else if(v != p){
                low[u] = min(low[u], dfn[v]);
            }
        }
    }
};
struct DSU {
    std::vector<int> f, siz;
    DSU(int n) : f(n), siz(n, 1) { std::iota(f.begin(), f.end(), 0); }
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
        return true;
    }
    int size(int x) { return siz[leader(x)]; }
};
const int dx[] = {1,-1,0,0};
const int dy[] = {0,0,1,-1};

void solve() {
    int h, w;
    cin >> h >> w;
    vector<vector<char>> a(h, vector<char>(w));
    for(int i = 0; i < h; i++) {
        cin >> a[i];
    }
    auto get_id = [&](int i, int j) {
        return i * w + j;
    };
    auto check = [&](int i, int j) {
        if(i < 0 || i >= h || j < 0 || j >= w) return false;
        return true;
    };
    DSU dsu(h * w);
    vector<vector<int>> G(h*w); 
    mint greencnt = 0;
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            if(a[i][j] == '#') {
                greencnt += 1;
                for(int k = 0; k < 4; k++) {
                    int xx = i + dx[k],yy = j + dy[k];
                    if(check(xx, yy) && a[xx][yy] == '#') {
                        if(dsu.leader(get_id(xx, yy)) != dsu.leader(get_id(i, j))) {
                            dsu.merge(get_id(xx, yy), get_id(i, j));
                        }
                        G[get_id(i, j)].push_back(get_id(xx, yy));
                        G[get_id(xx, yy)].push_back(get_id(i, j));
                    }
                }
            }
        }
    }
    int tot = 0;
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            if(a[i][j] == '#' && dsu.leader(get_id(i, j)) == get_id(i, j)) {
                ++tot;
            }
        }
    }
    BlockCutTree<int> bctree(G);
    mint ans = 0;
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            if(a[i][j] == '#') {
                ans += tot + sz(bctree.ng[get_id(i, j)]) - 1;
            }
        }
    }
    cout << ans/greencnt << "\n";
}
int main() {
    #ifdef ASHDR
    freopen("data.dfn","r",stdin);
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