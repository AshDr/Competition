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
    int n,k;
    cin >> n >> k;
	vector<pii> a(n);
	map<int,int> num;
	for(int i = 0; i < n; i++) {
		cin >> a[i].first;
		a[i].second = i;
		num[a[i].first]++;
	}
	sort(a.begin(), a.end());
	vector<int> ans(n);
	int mx = a.back().first;
	int ok = 0;
	if(mx % 4 == 2 && num.count(mx / 2)) ok = 1;
	for(int i = 0; i < n; i++) {
		if(i + num[a[i].first] - 1 >= k - 1) {// x ->(div) 2x + 1 ->(mul) 4x + 2 (2 5 10)
			if(a[i].first * 2 >= mx / 2 || (ok && a[i].first >= mx / 4)) { //特判
				ans[a[i].second] = 1;
				for(int j = i + 1; j < n; j++) ans[a[j].second] = 1;
				break;
			}
			else ans[a[i].second] = 0;
		}// 只用和mx比一次
		else {
			int remain = k - (i + num[a[i].first] - 1);
			if(remain > 2) {
				ans[a[i].second] = 0;
			}
			else { // remain == 2
				if(a[i].first * 2 >= mx || a[i].first >= mx / 2) ans[a[i].second] = 1;
				else ans[a[i].second] = 0; 
			}
		}
		while(i < n - 1 && a[i + 1].first == a[i].first) ans[a[i + 1].second] = ans[a[i].second],++i;
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

/*
1 2 3 5
2x -> 4x (*) 4x + 1(/)
2x + 1 -> 4x + 2(*) 4x + 3(/)

11 can be beated by 2

*/