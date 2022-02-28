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

const int N = 2e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const LL MOD = 1e9 + 7;
int TT = 1;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    vector<vector<int>> stmax(n,vector<int>(20)),stmin(n,(vector<int>(20)));
    vector<int> log_2(n + 1);
    log_2[1] = 0;
    for(int i = 2; i <= n; i++) log_2[i] = log_2[i / 2] + 1;
    for(int i = 0; i < n; i++) {
    	cin >> a[i];
    	stmax[i][0] = a[i];
    	stmin[i][0] = a[i];
    }
    for(int i = 1; (1 << i) <= n; i++) {
    	for(int j = 0; j + (1 << i) - 1 < n; j++) {
    		stmax[j][i] = max(stmax[j][i - 1],stmax[j + (1 << (i - 1))][i - 1]);
    		stmin[j][i] = min(stmin[j][i - 1],stmin[j + (1 << (i - 1))][i - 1]);
    	}
    }
    auto st_query = [&](int l, int r)-> pii {
    	int len = log_2[r - l + 1];
    	//assert(l > r);
    	int mx = max(stmax[l][len],stmax[r - (1 << len) + 1][len]);
    	int mn = min(stmin[l][len],stmin[r - (1 << len) + 1][len]);
    	return make_pair(mx,mn);
    };
    
    LL ans = 0;
    for(int i = 0; i < n; i++) {
    	int l = i,r = n - 1;
    	while(l < r) {
    		int mid = l + r + 1 >> 1;
    		auto p = st_query(i,mid);
    		if(p.first > p.second + k) r = mid - 1;
    		else l = mid;
    	}
    	int rb = l;
    	// cerr << rb << '\n';
    	auto tmp = st_query(i,rb);
    	bool ok = 1;
    	if(tmp.first != tmp.second + k) ok = 0; // warn: l = 0
    	l = i,r = n - 1;
    	while(l < r) {
    		int mid = l + r + 1 >> 1;
    		auto p = st_query(i,mid);
    		// cerr << mid <<' '<< p.first << ' ' << p.second << '\n';
    		if(p.first >= p.second + k) r = mid - 1;
    		else l = mid;
    	}
    	tmp = st_query(i,l);
    	int lb;
    	if(tmp.first == tmp.second + k) lb = l; //warn: l = 0
    	else lb = l + 1;    	
    	//cout << lb << ' ' << rb << '\n';
    	if(ok) ans += rb - lb + 1;
    }
    cout << ans << '\n';
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