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

void solve() {
    string s;
    cin >> s;
    int n = sz(s);
    int lpos = 0;
    vector<string> a,b;
    for(int i = 0 ; i < n; i++) {
        if(i == n - 1) {
            if(s[i] == ',' || s[i] == ';') {
                int f = 0;
                if(isdigit(s[lpos]) && !(i - lpos > 1 && s[lpos] == '0')) {
                    for(int j = lpos; j < i; j++) {
                        if(!isdigit(s[j])) {f = 1;break;}  
                    }
                }
                else f = 1;
                if(!f) a.push_back(s.substr(lpos,i - lpos));
                else b.push_back(s.substr(lpos,i-lpos));
                b.push_back("");
            }
            else {
                int f = 0;
                if(isdigit(s[lpos]) && !(i - lpos + 1 > 1 && s[lpos] == '0')) {
                    for(int j = lpos; j < i; j++) {
                        if(!isdigit(s[j])) {f = 1;break;}  
                    }
                }
                else f = 1;
                if(!f) a.push_back(s.substr(lpos,i - lpos + 1));
                else b.push_back(s.substr(lpos,i - lpos + 1));
            }        
        }
        else if(s[i] == ',' || s[i] == ';') {
            int f = 0;
            if(isdigit(s[lpos]) && !(i - lpos > 1 && s[lpos] == '0')) {
                for(int j = lpos; j < i; j++) {
                    if(!isdigit(s[j])) {f = 1;break;}  
                }
            }
            else f = 1;
            if(!f) a.push_back(s.substr(lpos,i - lpos));
            else b.push_back(s.substr(lpos,i-lpos));
            lpos = i + 1;
        }
    }

    if(sz(a)) {
        cout << '"';
        for(int i = 0; i < sz(a); i++) cout << a[i] << (i == (sz(a) - 1)?"":",");
        cout << '"';
    } 
    else cout << '-';
    cout << '\n';
    
    if(sz(b)) {
        cout << '"';
        for(int i = 0; i < sz(b); i++) cout << b[i] << (i == (sz(b) - 1)?"":",");
        cout << '"';
    }
    else cout << '-'; 
    cout << '\n';
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