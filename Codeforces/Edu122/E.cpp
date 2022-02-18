#include<bits/stdc++.h>
#define LOG(FMT...) fprintf(stderr, FMT)
#define sz(x) (int)x.size()
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
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
LL gcd(LL x, LL y) {return y == 0 ? x : gcd(y, x % y);}
LL qpow(LL base, LL x, LL mod) {
    LL res = 1;
    base %= mod;
    while(x) {
       if(x & 1) res = (res * base) % mod;
       base = (base * base) % mod;
       x >>= 1;
    } 
    return res;
}
LL exgcd(LL a,LL b,LL &x,LL &y) {
    if(b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    LL d = exgcd(b,a % b,y,x);
    y -= a / b * x;
    return d;
}// (get inv) gcd(a,p) = 1 

const int N = 2e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const LL MOD = 1e9 + 7;
int TT = 1;
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
void solve() {
    int n, m, q;
    cin >> n >> m;
    vector<array<int,3>> E(m);
    for(int i = 0; i < m; i++) {
        int u,v,w;
        cin >> u >> v >> w;
        u--;v--;
        E[i] = {w,u,v};
    }
    LL a, b, c, p;
    cin >> p >> q >> a >> b >> c;
    vector<int> Q(q);
    for(int i = 0; i < p; i++) {
        cin >> Q[i];
    }
    for(int i = p; i < q; i++) {
        Q[i] = (1ll * Q[i - 1] * a + b) % c; 
    }
    sort(Q.begin(),Q.end());
    sort(E.begin(),E.end());
    vector<int> e{0};
    for(int i = 0; i < m; i++) {
        for(int j = i; j < m; j++) {
            e.push_back((E[i][0] + E[j][0] + 1) / 2);
        }
    }
    sort(e.begin(),e.end());
    e.erase(unique(e.begin(),e.end()),e.end());
    vector<pair<LL,int>> info;
    auto kruskal = [&](int x) {
        sort(E.begin(),E.end(),[&](array<int,3> a,array<int,3> b) {
            int tx = abs(a[0] - x);
            int ty = abs(b[0] - x);
            if(tx == ty) {
                return a[0] > b[0];
            } else {
                return tx < ty;
            }
        });
        DSU dsu(n);
        int cnt = 0;
        LL res = 0;
        for(int i = 0; i < m; i++) {
            int u = E[i][1],v = E[i][2],w = abs(E[i][0] - x);
            if(!dsu.same(u,v)) {
                res += w;
                cnt += E[i][0] <= x;
                dsu.merge(u,v);
            }
        }
        return make_pair(res,cnt);
    };
    for(int i = 0; i < sz(e); i++) {
        info.push_back(kruskal(e[i]));
    }

    LL ans = 0;
    for(int i = 0; i < q; i++) {
        int pos = upper_bound(e.begin(),e.end(),Q[i]) - e.begin();
        --pos;
        LL res = (info[pos].first + (1ll*info[pos].second) * (Q[i] - e[pos]) - 1ll * (n - 1 - info[pos].second) * (Q[i] - e[pos]));
        ans ^= res;
    }
    cout << ans << '\n';

}

int main() {
    #ifdef ASHDR
    freopen("data.in","r",stdin);
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