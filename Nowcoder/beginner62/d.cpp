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
LL qpow(LL base, LL x) {
    LL res = 1;
    while(x) {
       if(x & 1) res = (res * base) ;
       base = (base * base);
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
LL n,k;
int m;
void solve() {
    cin >> n >> k >> m;
    //0~n-1
    for(int i = 1; i <= m; i++) {
        LL x;
        cin >> x;
        if(k == 1) {
            cout << n - x << '\n';
            continue;
        }
        else {
            LL lv = 1,lmost = x,rmost = x;
            int f = 0;
            while(1) {
                if(lmost * k + 1 > n - 1) {
                    f = 1;
                    break;
                }//leaf
                else if(rmost * k + k > n - 1) {
                    ++lv;
                    f = 2;
                    break;
                }
                else {
                    ++lv;
                }
                lmost = lmost * k + 1;
                rmost = rmost * k + k;
            }
            // cout << lv << ' ' << f << '\n';
            if(f == 1) {
                cout << (qpow(k,lv) - 1) / (k - 1) << '\n'; 
            }
            else {
                cout << (qpow(k,lv - 1) - 1) / (k - 1) + n - (lmost * k + 1) << '\n'; 
            }
        }

    }
}
/*
 <= x <= k^l - 1
0
1 2 3
456 789 101112

1 + k + k^2

level: 1,2...

（1 - k^{level}) / (1 - k)
=(k^{level} - 1) / (k - 1)


*/
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