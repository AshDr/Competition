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
struct point {
	int x,y,id,val;
};
void solve() {
    int n;
    cin >> n;
    vector<point> a(n);
    vector<int> b(n);
    for(int i = 0; i < n; i++) {
    	cin >> a[i].x >> a[i].y;
    	a[i].id = i;
    	a[i].val = a[i].y - a[i].x;
    }
	cin >> b;

    map<int,int> mp,Count;
    int cnt = 0;
	for(int i = 0; i < n; i++) {
		if(!mp.count(b[i])) mp[b[i]] = cnt++;
		Count[mp[b[i]]]++;
	}
	vector<vector<point>> vec(cnt,vector<point>());
	for(int i = 0; i < n; i++) {
		int val = a[i].val;
		if(!mp.count(a[i].val)) {
			cout << "NO" << '\n';
			return ;
		}
		int idx = mp[a[i].val];
		vec[idx].emplace_back(a[i]);
	}
	for(auto [key,val]: Count) {
		if(sz(vec[key]) != val) {
			cout << "NO" << '\n';
			return ;
		}
	}
	for(int i = 0; i < cnt; i++) sort(vec[i].rbegin(),vec[i].rend(),[&](point &p1, point &p2) {
		if(p1.x == p2.x) return p1.y < p2.y;
		return p1.x < p2.x;
	});
	int mxp_x = -1,mxp_y = -1;
	vector<point> ans(n);
	for(int i = 0; i < n; i++) {
		int idx = mp[b[i]];
		point p = vec[idx].back();
		vec[idx].pop_back();
		if(mxp_x >= p.x && mxp_y >= p.y) {
			cout << "NO" << '\n';
			return ;
		}
		else {
			ans[i] = p;
			if(p.x >= mxp_x && p.y >= mxp_y) {
				mxp_x = p.x;
				mxp_y = p.y;
			}
		}
	}
	cout << "YES" << '\n';
	for(int i = 0; i < n; i++) cout << ans[i].x << ' ' << ans[i].y << '\n';
	/*
	同一直线上的偏序关系不变
	因此根据b数组 每个点的位置唯一确定 只需要check是否满足条件即可
	*/

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