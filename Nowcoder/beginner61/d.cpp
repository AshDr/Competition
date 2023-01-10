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
#define int long long 
const int N = 2e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const LL MOD = 1e9 + 7;
int TT = 1;
int T[N];
void solve() {
    int n,ec,et,p,s;
    cin >> n >> ec >> et >> p >> s;
    for(int i = 1; i <= n; i++) cin >> T[i];
    if(ec > s) cout << -1 << '\n';
    else {
    	int delta = 0,ans = 0,occ = 0;
    	for(int i = 1; i <= n; i++) {
    		if(s >= ec) {
    			s -= ec;
    		}
    		else {
                if(delta == 0) {
                    ans += T[i - 1];
                    ++delta;
                    int t = ec - s;
                    int tim = (t + delta * p - 1) / (delta * p); 
                    s += tim * p * delta;
                    s -= ec;
                    ans += tim;
                    ans += et;
                    s += et * delta * p;
                    continue;
                }
    			int t = ec - s;
    			int tim = (t + delta * p - 1) / (delta * p); 
    			//要考虑上一次的占领
    			if(tim <= T[i - 1]) {
    				s += tim * p * delta;
    				s -= ec;
    				++delta;
    				ans += tim;

    			}
    			else {
    				s += T[i - 1] * p * delta;
    				++delta;
    				ans += T[i - 1];
    				assert(s < ec);
    				int tmp = ec - s,tmp1 = (tmp + delta * p - 1) / (delta * p);
    				s += tmp1 * delta * p;
    				ans += tmp1;
    				s -= ec;
    			}

    		}
    		//培养工程师
    		ans += et;
    		s += et * delta * p;
    		//占领的时候可以继续生产
    		//下一次占领完成的时候 上一次的占领一定是完成了的
    	}
    	cout << ans + T[n]<< '\n';
    }
}
signed main() {
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