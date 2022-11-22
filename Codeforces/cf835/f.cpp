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
    int n,d;
    LL c;
    cin >> n >> c >> d;
    vector<int> a(n);
    vector<LL> suf(n + 1);
    cin >> a;
    sort(a.begin(),a.end());
    LL sum = accumulate(a.begin(),a.end(),0ll);
    suf[n - 1] = a[n - 1];
    for(int i = n - 2; i >= 0; i--) suf[i] = suf[i + 1] + a[i];
    if(suf[max(0,n - d)] >= c) {
    	cout << "Infinity" << '\n';
    	return ;
    }
    if(1ll * d * a.back() < c) {
    	cout << "Impossible" << '\n';
    	return ;
    }    
	auto check = [&](LL x) ->bool {
		if(x >= n) {
			LL t = d / (x + 1),q = d % (x + 1);
			LL tmp = t * sum;
			if(q >= n) tmp += sum;
			else tmp += suf[n - q];

			return tmp >= c; 
		}
		else {
			LL t = d / (x + 1), q = d % (x + 1);

			return t * suf[n - x - 1] + suf[n - q] >= c;
		}

	};
    LL l = 0,r = d;
	while(l < r) {
		LL mid = (l + r + 1) >> 1;
		if(check(mid)) l = mid;
		else r = mid - 1;
	}
	cout << l << '\n';
    //d day gain at least c coins, find the maxinium of k
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