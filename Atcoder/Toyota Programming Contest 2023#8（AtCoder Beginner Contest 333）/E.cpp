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
#include <random>
#define LOG(FMT...) fprintf(stderr, FMT)
#define sz(x) (int)x.size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef unsigned int ui;
typedef unsigned long long ull;
typedef pair<double,double> pdd;
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
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll myRand(ll B) {return (ull)rng()%B;}
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

void solve() {
	int n;
	cin >> n;
    vector<pii> events(n); 
    vector<int> cnt(n + 1);
    int f = 1;
    vector<vector<int>> pos(n + 1);
    for(int i = 0; i < n; i++) {
    	cin >> events[i].first >> events[i].second;
    	if(events[i].first == 1) {
    		cnt[events[i].second]++;
    		pos[events[i].second].push_back(i);
    	}else {
    		if(!cnt[events[i].second]) {
    			f = 0;
    		}else {
    			--cnt[events[i].second];
    		}
    	}
    }    
    if(!f) {
    	cout << "-1\n";
    	return ;
    }
    vector<int> cnt2(n + 1),vis(n);
    for(int i = n - 1; i >= 0; i--) {
    	if(events[i].first == 1) {
    		if(cnt2[events[i].second] == 0) continue;
    		else {
    			if(cnt2[events[i].second] > 0) {
    				vis[i] = 1;
    			}
    			--cnt2[events[i].second];
    		}
    	}else {
    		++cnt2[events[i].second];
    	}
    }
    for(int i = 1; i <= n; i++) {
    	if(cnt2[i] > 0) {
    		cout << "-1\n";
    		return ;
    	}
    }

    vector<int> ans(n);
    auto check = [&](int num) {
    	int sum = 0;
    	vector<int> res(n);
    	for(int i = 0; i < n; i++) {
    		if(vis[i]) {
    			sum++;
    			res[i] = 1;
    			if(sum > num) return false;
    		}else if(events[i].first == 2) {
    			assert(sum > 0);
    			--sum;
    		}
    	}
    	ans = res;
    	return true;
    };
    int l = 0,r = n;
    while(l < r) {
    	int mid = (l + r) >> 1;
    	if(check(mid)) r = mid;
    	else l = mid + 1;
    }
   
    cout << l << "\n";

    for(int i = 0; i < n; i++) {
    	if(events[i].first == 1) cout << ans[i] << " ";
    }
    cout << "\n";
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