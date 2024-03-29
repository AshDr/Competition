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
const int MAXN = 1e9 + 10;
struct node {
    int ls,rs;
    LL num,sum;
}tr[N * 40];
int n,m,tot,root;
void push_up(int idx) {
    tr[idx].num = tr[tr[idx].ls].num + tr[tr[idx].rs].num;
    tr[idx].sum = tr[tr[idx].ls].sum + tr[tr[idx].rs].sum;
}
void modify(int &idx,int val, int num, int L, int R) {
    if(!idx) {
        idx = ++tot;
    }
    if(L == R) {
        tr[idx].num += num;
        tr[idx].sum += 1ll * num * val;
        return ;
    }
    int mid =  (L + R) >> 1;
    if(val <= mid) modify(tr[idx].ls, val, num, L, mid);
    else modify(tr[idx].rs, val, num, mid + 1, R);
    push_up(idx);
}
LL query(int idx, int k, int L, int R) {
    if(!idx) return 0;
    if(L == R) return 1ll*k*L; //!
    LL res = 0;
    int mid = (L + R) >> 1;
    if(tr[tr[idx].rs].num >= k) res = query(tr[idx].rs, k, mid + 1, R);
    else {
        res = query(tr[idx].ls, k - tr[tr[idx].rs].num, L, mid) + tr[tr[idx].rs].sum;
    }
    return res;
}
int a[N],b[N];
void solve() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        int x,y;
        cin >> x >> y;
        a[i] = x;b[i] = y;
        modify(root, x, y, 0, MAXN);
    }
    cin >> m;
    for(int i = 1; i <= m; i++) {
        int op;
        cin >> op;
        if(op == 1) {
            int x,y;
            cin >> x >> y;
            modify(root, a[x], -b[x], 0, MAXN);
            a[x] = y;
            modify(root, a[x], b[x], 0, MAXN);
        }
        else if(op == 2) {
            int x,y;
            cin >> x >> y;
            modify(root, a[x], -b[x], 0, MAXN);
            b[x] = y;
            modify(root, a[x], b[x], 0, MAXN);
        }
        else {
            int x;
            cin >> x;
            if(tr[root].num < x) cout << -1 << "\n";
            else cout << query(root, x, 0, MAXN) << "\n";
        }
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
    //cin>>TT;
    while(TT--) solve();
    #ifdef ASHDR
    LOG("Time: %dms\n", int ((clock()
            -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
    #endif
    return 0;
}