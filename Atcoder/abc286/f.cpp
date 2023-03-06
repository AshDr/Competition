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
#include <numeric>
#define LOG(FMT...) fprintf(stderr, FMT)
#define sz(x) (int)x.size()
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
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
int a[N],b[N];
void solve() {
	//解一个同余方程组
	vector<int> use = {4,5,7,9,11,13,17,19,23};//
    int len = accumulate(use.begin(),use.end(),0);
    int cnt = 1;
    ll M = 1;
    for(int i = 0; i < sz(use); i++) {
        int pre = cnt;
        for(int j = 1; j < use[i]; j++) {
            a[cnt] = cnt + 1;
            ++cnt;
        }    
        a[cnt] = pre;
        ++cnt;
        M *= use[i];
    }
    cout << len << endl;
    for(int i = 1; i <= len; i++) cout << a[i] << " ";
    cout << endl;
    for(int i = 1; i <= len; i++) {
        cin >> b[i];
    }
    int idx = 0;
    vector<int> aa;
    for(int i = 1; i <= len;) {
        for(int j = 1; j <= use[idx]; j++) {
            if(b[i] == a[i+j-1]) {
                aa.push_back(j%use[idx]);
                break;
            } 
        }
        i += use[idx++];
    }
    ll res = 0;
    for(int i = 0; i < sz(aa); i++) {
        ll x,y;
        exgcd(M/use[i],use[i],x,y);
        ll inv = (x%use[i]+use[i])%use[i];
        res += 1ll*M/use[i]*aa[i]%M*inv%M;
        res %= M;
    }
    cout << (res%M+M)%M << endl;
}
/*
2 3 4 1 6 7 8 9 5 11 12 13 14 15 16 10 18 19 20 21 22 23 24 25 17 27 28 29 30 31 32 33 34 35 36 26 38 39 40 41 42 43 44 45 46 47 48 49 37 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 50 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 67 87 88 89 90 91 92 93 94 95 96 97 98 99 100 101 102 103 104 105 106 107 108 86
*/

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