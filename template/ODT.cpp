#include<bits/stdc++.h>
//#define cerr cout<<"#case:"
#define LOG(FMT...) fprintf(stderr, FMT)
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
const int N = 1e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const LL MOD = 1e9 + 7;
int TT = 1;
LL gcd(LL x, LL y) {return y == 0 ? x : gcd(y, x % y);}
LL qpow(LL base, LL x, LL mod) {
    LL res = 1;
    base = base % mod;
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
int norm(int x) { return x >= MOD ? x - MOD : x; }
void add(int& x, int y) {
  if ((x += y) >= MOD)
    x -= MOD;
}

void sub(int& x, int y) {
  if ((x -= y) < 0)
    x += MOD;
}
#define sz(x) (int)x.size()
LL a[N];
struct node {
    int l,r;
    mutable LL val;
    node(int _l,int _r = -1, LL _val = 0):l(_l),r(_r),val(_val){}
    bool operator<(const node& o) const
    {
        return l < o.l;
    }
};
void solve() {
    int n, m;
    LL  seed, vmax;
    cin >> n >> m >> seed >> vmax;
    set<node> s;
    auto rnd = [&]() ->LL {
        LL ret = seed;
        seed = (seed * 7 + 13) % MOD;
        return ret;
    };
    auto split = [&](int pos) {
        auto it = s.lower_bound(node(pos));
        if(it != s.end() && it->l == pos) return it;
        --it;
        int l = it->l,r = it->r;
        LL val = it -> val;
        s.erase(it);
        s.insert(node(l,pos - 1,val));
        return s.insert(node(pos,r,val)).first;        
    };//将一个区间分成两半，[l,pos-1] [pos,r]
    auto assign = [&](int l, int r,LL val) {
        auto itr= split(r + 1),itl = split(l);
        s.erase(itl,itr);
        s.insert(node(l,r,val));
    };//区间赋值
    auto add = [&](int l, int r, LL val) {
        auto it2 = split(r + 1),itl = split(l);
        for(;itl != it2; ++itl) itl->val += val;
    };//区间加
    auto rank = [&](int l, int r, int k )-> LL {
        vector<pair<LL,int>> b;
        auto itr = split(r + 1),itl = split(l);
        for(;itl != itr; ++itl) {
            b.push_back({itl->val,itl->r - itl->l + 1});
        }  
        sort(b.begin(),b.end());
        for(auto p: b) {
            k -= p.second;
            if(k <= 0) return p.first;
        }
        //assert(false);
        return -1ll;
    };
    auto sum = [&](int l, int r, int x,int mod)-> LL {
        auto itr = split(r + 1),itl = split(l);
        LL res = 0;
        for(;itl != itr; ++itl) {
            res = (res + (LL)(itl->r - itl->l + 1) * qpow(itl->val,LL(x),LL(mod))) % mod;
        }
        return res;
    }; 
    for(int i = 1; i <= n; i++) {
        a[i] = (rnd() % vmax) + 1;
        s.insert(node(i,i,a[i]));
    }
    s.insert(node(n + 1,n + 1,0));
    for(int i = 1; i <= m; i++) {
        int op,l,r;
        int x,y;
        op = (rnd() % 4) + 1;
        l = (rnd() % n) + 1;
        r = (rnd() % n) + 1;
//        cout << i << ' ' << op << endl;

        if(l > r) swap(l,r);
        if (op == 3)
            x = int(rnd() % (r-l+1)) + 1;
        else
            x = int(rnd() % vmax) +1;
        if (op == 4)
            y = int(rnd() % vmax) + 1;

        if(op == 1) {
            add(l,r,LL(x));
        }
        else if(op == 2) {
            assign(l,r,LL(x));
        }
        else if(op == 3) {
            cout << rank(l,r,x) << '\n';
        }
        else if(op == 4) {
            cout << sum(l,r,x,y) << '\n';
        }
        else assert(false);
    }
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