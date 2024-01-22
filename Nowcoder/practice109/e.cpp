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

ll floor(ll x, ll m) {
    ll r = (x % m + m) % m;
    return (x - r) / m;
}// neg floor (-1, 3) = -1
const int N = 2e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
int TT = 1;
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
int n;
int a[N],c[N];
mint pw2[N],invpw2[N],preval[N],prepw[N];
vector<int> b;
mint ans;
namespace CD {
    vector<int> G[N];
    int S=n,rt=0,cnt,mxpart=1e9,siz[N],vis[N],parent[N],belong[N]; //init S and mxpart
    mint sum[N],sumpw[N];
    int d[N];
    vector<int> tmp; 
    void find_rt(int u, int fa) {
        int mx=0;
        for(auto v: G[u]) {
            if(vis[v]||v==fa) continue;
            find_rt(v, u);
            mx=max(mx,siz[v]);
        }
        mx=max(mx,S - siz[u]);
        if(mx < mxpart) mxpart=mx,rt=u;
    }
    void get_siz(int u, int fa) {
        siz[u]=1;
        for(auto v:G[u]) {
            if(vis[v] || v==fa) continue;
            get_siz(v, u);
            siz[u]+=siz[v];
        }
    }
    void get_dis(int rt, int u, int fa, int dis) {
        ans += pw2[n - 1 - dis] * 2 * abs(a[rt] - a[u]);
        d[u] = dis;
        tmp.push_back(u);
        for(auto v: G[u]) {
            if(vis[v]||v==fa) continue;
            belong[v] = belong[u];
            get_dis(rt, v, u, dis+1);
        }
    }
    void calc(int u, int prefa) {
        mxpart=1e9;
        rt=u;
        get_siz(u, 0);
        S = siz[u];
        find_rt(u, 0);
        // cout<<u<<" "<<rt<<endl;
        vis[rt]=1;
        // parent[rt] = prefa; //点分树的父亲
        tmp.clear();
        for(auto v: G[rt]) { //注意从这一下都要写成rt
            if(vis[v]) continue;
            cnt=0;
            belong[v] = v;
            sum[v] = sumpw[v] = 0;
            get_dis(rt, v, rt, 1);
        }
        sort(tmp.begin(), tmp.end(), [&](int x, int y) {
            return a[x] < a[y];
        });
        // cout << rt << "!\n";
        // cout << tmp << "\n";
        int m = sz(tmp);
        mint tot = 0,totpw = 0;
        for(int i = 0; i < m; i++) {
            int x = tmp[i];
            ans += pw2[n - 1 - d[x]] * ((totpw - sumpw[belong[x]]) * a[x] - (tot - sum[belong[x]]));
            sum[belong[x]] += invpw2[d[x]] * a[x];
            sumpw[belong[x]] += invpw2[d[x]];
            tot += invpw2[d[x]] * a[x];
            totpw += invpw2[d[x]];
        }
        tot = totpw = 0;
        for(int i = 0 ; i < m; i++) sum[belong[tmp[i]]] = sumpw[belong[tmp[i]]] = 0;
        for(int i = m - 1; i >= 0; i--) {
            int x = tmp[i];
            ans += pw2[n - 1 - d[x]] * ((tot - sum[belong[x]]) - (totpw - sumpw[belong[x]]) * a[x]);
            sum[belong[x]] += invpw2[d[x]] * a[x];
            sumpw[belong[x]] += invpw2[d[x]];
            tot += invpw2[d[x]] * a[x];
            totpw += invpw2[d[x]];
        }
        int curfa = rt;
        for(auto v:G[rt]) {
            if(!vis[v]) {
                calc(v, curfa);
            }
        }
    }
}
using namespace CD;
void solve() {
    cin >> n;
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        CD::G[u].push_back(v);
        CD::G[v].push_back(u);
    }    
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        b.push_back(a[i]);
    }
    pw2[0] = 1;
    invpw2[0] = 1;
    for(int i = 1; i <= n; i++) {
        pw2[i] = pw2[i - 1] * 2;
        invpw2[i] = pw2[i].inv();
    }
    // sort(b.begin(), b.end());
    // b.erase(unique(b.begin(), b.end()), b.end());
    // for(int i = 1; i <= n; i++) c[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
    CD::calc(1, 0);
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