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

const int N = 1e6 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const LL MOD = 1e9 + 7;
int TT = 1;
int n,m,len;
int a[N];
int ans = 0;
void solve() {
    /*
    	(s+a[l])*(s+a[r])=(s+a[l]+a[r])*s
		a[l]*a[r]=0 a[l]==0 or a[r]==0
		长度为len+2 包含0 且存在R(1<= i < n-len-1) 的区间L有多少个
    */
    cin >> n >> m >> len;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n - len - 1; i++) {
    	if(a[i] == 0) {
    		++ans;
    	}
    }
    for(int i = n; i >= 1 + len + 1; i--) {
    	if(a[i] == 0) {
    		if(a[i-len-1] != 0) ++ans;
    	}
    }
    for(int i = 1; i <= m; i++) {
    	int pos,val;
    	cin >> pos >> val;
    	if(val == 0) {
    		if(a[pos] != 0 && pos+len+1 <= n && a[pos+len+1]!=0) {
    			++ans;
    		}
    		if(a[pos] != 0 && pos-len-1 >= 1 && a[pos-len-1]!=0) {
    			++ans;
    		}
    	}
    	else {
    		if(a[pos] == 0) {
    			if(pos+len+1 <= n && a[pos+len+1] !=0) --ans;
    			if(pos-len-1 >= 1 && a[pos-len-1] !=0) --ans;

    		}
    	}
    	a[pos]=val;
    	cout << ans << "\n";
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