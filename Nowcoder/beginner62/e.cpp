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

const int N = 1e7 + 10;
const int M = 5e5 + 10;
const int INF = 2147483647;
const LL MOD = 1e9 + 7;
int TT = 1;
int n,m;
int siz[N],sum[N],ans[M],dfn[N],rev[N],dfn_cnt;
void dfs(int u) {
	siz[u] = 1;dfn[u] = ++dfn_cnt;rev[dfn_cnt] = u;
	if(2 * u <= n) dfs(2 * u),siz[u] += siz[2 * u];
	if(2 * u + 1 <= n) dfs(2 * u + 1),siz[u] += siz[2 * u + 1];
}
void solve() {
	cin >> n >> m;
	dfs(1);
	for(int i = 1; i <= m; i++) {
		int op,x;
		cin >> op >> x;
		if(op == 1) {
			sum[dfn[x]]++;
			sum[dfn[x] + siz[x]]--;	
		}
		else if(op == 2){
			sum[1]++;
			sum[n + 1]--;
			sum[dfn[x]]--;
			sum[dfn[x] + siz[x]]++;
		}
		else if(op == 3) {
			while(x) {
				sum[dfn[x]]++;
				sum[dfn[x] + 1]--;
				x /= 2;
			}			
		}
		else {
			sum[1]++;
			sum[n + 1]--;
			while(x) {
				sum[dfn[x]]--;
				sum[dfn[x] + 1]++;
				x /= 2;
			}
		}
		// int t = 0;
		// for(int i = 1; i <= n; i++) {
		// 	t += sum[i];
		// 	cout << rev[i] << ' ' << t << '\n';
		// }
		// cout << "-------" << '\n';
	}
	int t = 0;
	for(int i = 1; i <= n; i++) {
		t += sum[i];
		// cout << i << ' ' << t << "\n";
		ans[t]++; 
	}
	for(int i = 0 ; i <= m; i++) cout << ans[i] << " \n"[i == m];
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