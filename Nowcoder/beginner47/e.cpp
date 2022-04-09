#include<bits/stdc++.h>
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
int read() {
	char ch = getchar();
	int res = 0,f = 1;
	while(ch < '0' || ch > '9') {if(ch == '-') f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9') {
		res = res * 10 + ch - '0';
		ch = getchar();
	}
	return f * res;
}
const int N = 1e3 + 10;
const int M = 1e6 + 10;
const int INF = 2147483647;
const LL MOD = 1e9 + 7;
int TT = 1;
int pre[N][N],a[M][4];
void solve() {
	int n, m;
	cin >> n >> m;
	vector<vector<pii>> col(M);
	for(int i = 1; i < M; i++) a[i][0] = a[i][1] = M;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			int x;
			cin >> x;
			a[x][0] = min(a[x][0],i);
			a[x][1] = min(a[x][1],j);
			a[x][2] = max(a[x][2],i);
			a[x][3] = max(a[x][3],j);
			col[x].push_back({i, j});
		}
	} 
	for(int i = 0; i < M; i++) {
		if(sz(col[i]) <= 1) continue;
		else {
			pre[a[i][0]][a[i][1]]++;
			pre[a[i][2] + 1][a[i][1]]--;
			pre[a[i][0]][a[i][3] + 1]--;
			pre[a[i][2] + 1][a[i][3] + 1]++;
		}
	}
	int res = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			pre[i][j] += pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1];
			if(pre[i][j] == 0) {
				res++;
			}
		}
		
	}
	cout << res << '\n';
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