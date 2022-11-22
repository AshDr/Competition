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
const int INF = 1e9;
const LL MOD = 1e9 + 7;
int TT = 1;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    int f1 = 0,f2 = 0,x = 0,res = 1;
    int check = -1;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] += a[i] % 10;
        if(a[i] % 10 == 0) {
            f1 = 1;
        }
        if(f1 == 1 && a[i] != a[0]) {
            res = 0;
        }    
        if(a[i] % 10 == 2 || a[i] % 10 == 4 || a[i] % 10 == 8) check = (a[i] / 10) % 2;
        if(a[i] % 10 == 6) check = ((a[i] / 10) % 2 + 1) % 2;
    }    
    
    if(!f1) {
        for(int i = 0; i < n; i++) {
            if(a[i] % 10 == 2 || a[i] % 10 == 4 || a[i] % 10 == 8) {
                if((a[i] / 10) % 2 != check) res = 0; 
            }
            else if(a[i] % 10 == 6) {
                if((a[i] / 10) % 2 != (check + 1) % 2) res = 0;
            }
        }
    }
    if(res) cout << "Yes" << '\n';
    else cout << "No" << '\n';
    //1 2 4 8->mod = 2 4 8 6
    //3 6 7 9->mod = 2 4 7 6
    //0 5->0 5
}
int main() {
    #ifdef ASHDR
    freopen("data.in","r",stdin);
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