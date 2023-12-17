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
#include <random>
#define LOG(FMT...) fprintf(stderr, FMT)
#define sz(x) (int)x.size()
#define all(x) (x).begin(),(x).end()
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
const ll MOD = 1e9 + 7;
int TT = 1;
int lg(int x) {
    return static_cast<int>(std::log2(x));
}
template<class Info, class Tag>
struct LazySegmentTree {
    int n;
    std::vector<Info> info;
    std::vector<Tag> tag;
    LazySegmentTree() : n(0) {}
    LazySegmentTree(int n_, Info v_ = Info()) {
        init(n_, v_);
    }
    template<class T>
    LazySegmentTree(std::vector<T> init_) {
        init(init_);
    }
    void init(int n_, Info v_ = Info()) {
        init(std::vector(n_, v_));
    }
    template<class T>
    void init(std::vector<T> init_) {
        n = init_.size();
        info.assign(4 << __lg(n), Info());
        tag.assign(4 << __lg(n), Tag());
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init_[l];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }
    void pull(int p) {
        info[p] = info[2 * p] + info[2 * p + 1];
    }
    void apply(int p, const Tag &v) {
        info[p].apply(v);
        tag[p].apply(v);
    }
    void push(int p) {
        apply(2 * p, tag[p]);
        apply(2 * p + 1, tag[p]);
        tag[p] = Tag();
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        push(p);
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info &v) {
        modify(1, 0, n, p, v);
    }
    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        push(p);
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n, l, r);
    }
    void rangeApply(int p, int l, int r, int x, int y, const Tag &v) {
        if (l >= y || r <= x) {
            return;
        }
        if (l >= x && r <= y) {
            apply(p, v);
            return;
        }
        int m = (l + r) / 2;
        push(p);
        rangeApply(2 * p, l, m, x, y, v);
        rangeApply(2 * p + 1, m, r, x, y, v);
        pull(p);
    }
    void rangeApply(int l, int r, const Tag &v) {
        return rangeApply(1, 0, n, l, r, v);
    }
    template<class F>
    int findFirst(int p, int l, int r, int x, int y, F pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        push(p);
        int res = findFirst(2 * p, l, m, x, y, pred);
        if (res == -1) {
            res = findFirst(2 * p + 1, m, r, x, y, pred);
        }
        return res;
    }
    template<class F>
    int findFirst(int l, int r, F pred) {
        return findFirst(1, 0, n, l, r, pred);
    }
    template<class F>
    int findLast(int p, int l, int r, int x, int y, F pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        push(p);
        int res = findLast(2 * p + 1, m, r, x, y, pred);
        if (res == -1) {
            res = findLast(2 * p, l, m, x, y, pred);
        }
        return res;
    }
    template<class F>
    int findLast(int l, int r, F pred) {
        return findLast(1, 0, n, l, r, pred);
    }
};
 
struct Tag {
    //define tag maybe need contructor to determine init val
    int add;
    Tag() {
        add = 0;
    }
    Tag(int val) {
        add = val;
    }
    void apply(const Tag &t) & {
        //add tag to tag
        add += t.add;
    }
};
 
struct Info {
    //define info maybe need contructor to determine init val
    int dep;
    void apply(const Tag &t) & {
        //add tag to info
        dep += t.add;
    }
};
Info operator+(const Info &a, const Info &b) {
    Info c;
    //merge info
    c.dep = max(a.dep, b.dep);
    return c;
}
vector<int> G[N];
void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> in(n),out(n),nxt(n);
    vector<int> depth(n);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        --u;--v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    int dfn_cnt = 0;
    auto dfs1 = [&](auto self, int u, int p)->void {
        in[u] = dfn_cnt++;
        for(auto v: G[u]) {
            if(v == p) continue;
            depth[v] = depth[u] + 1;
            self(self, v, u);
        }
        out[u] = dfn_cnt;//euler cnt [in,out)
    };
    vector<int> ans(q);
    dfs1(dfs1, 0, -1);
    vector<vector<pair<int,vector<int>>>> Q(n);
    for(int i = 0; i < q; i++) {
        int x, k;
        cin >> x >> k;
        --x;
        vector<int> ask;
        for(int j = 0; j < k; j++) {
            int u;
            cin >> u;
            --u;
            ask.push_back(u);
        }
        Q[x].push_back({i, ask});
    }
    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    sort(p.begin(), p.end(), [&](int i, int j){return in[i] < in[j];});
    vector<Info> init(n);
    for(int i = 0; i < n; i++) init[i].dep = depth[p[i]];
    LazySegmentTree<Info, Tag> seg(init);
    auto calc = [&](auto self, int u, int p)->void {
        for(auto [id, vec]: Q[u]) {
            vector<pii> skip;
            int flag = 0;
            for(auto x: vec) {
                if(x == u) {
                    flag = 1;
                    break;
                }
                if(in[x] <= in[u] && in[u] < out[x]) {
                    skip.push_back({0, in[nxt[x]]}); //[)
                    skip.push_back({out[nxt[x]], n}); //[)
                }//x is u's anc
                else {
                    skip.push_back({in[x], out[x]});
                }
            } 
            if(flag) continue;
            sort(all(skip));
            int pre = 0, res = 0;
            for(auto [l, r]: skip) {
                if(pre < l) {
                    Info tmp = seg.rangeQuery(pre, l);
                    res = max(res, tmp.dep);
                }
                pre = max(pre, r);
            }
            if(pre < n) {
                Info tmp = seg.rangeQuery(pre, n);
                res = max(res, tmp.dep);
            }
            ans[id] = res;
        }
        for(auto v: G[u]) {
            if(v == p) continue;
            seg.rangeApply(in[v], out[v], {-1});
            seg.rangeApply(0, in[v], {1});
            seg.rangeApply(out[v], n, {1});
            nxt[u] = v; // change
            self(self, v, u);
            seg.rangeApply(in[v], out[v], {1});
            seg.rangeApply(0, in[v], {-1});
            seg.rangeApply(out[v], n, {-1});
        }
    };
    calc(calc, 0, -1);
    for(auto val: ans) cout << val << "\n";
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