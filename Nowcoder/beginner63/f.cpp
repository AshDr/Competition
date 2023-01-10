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
#define int long long 
LL siz[20],presiz[20],w[20];
LL n,m;
void solve() {
	cin >> n >> m;
	LL p = 1;
	int limit = 18;
	bool f = false;
	memset(siz,0,sizeof siz);
	memset(presiz,0,sizeof presiz);
	memset(w,0,sizeof w);
	for(int i = 1; i <= 18; i++) {
		siz[i] = 9ll * p;
		if(p * 10 >= m) {
			siz[i] = m - p;
			f = true;
		}
		w[i] = w[i - 1] + siz[i] * i;
		presiz[i] = presiz[i - 1] + siz[i];
		if(f) {
			limit = i;
			break;
		}
		p *= 10;
	}

	LL res = 1e18;
	for(int i = 1; i <= limit; i++) {
		if(n % i == 0 && n / i >= 0 && n / i <= siz[i]) {
			res = min(res,n / i);
		}
	}//1 block

	auto gao = [&](LL a, LL b, LL d)->LL {
		// cout << a << ' ' << b << "start \n";
		LL Gcd = gcd(a,b), k = d / Gcd;
		LL x,y;
		exgcd(a,b,x,y);
		LL init_x = x * k,init_y = y * k,delta_x = b / Gcd,delta_y = a / Gcd;
		LL l = -1e18,r = 1e18;
		
		auto check = [&](LL mid) {
			LL xx = init_x + mid * delta_x, yy = init_y - mid * delta_y;
			// cout << xx << ' ' << yy << "\n";
			//a * xx + b * yy = d
			//min(xx + yy) b > a
			if(xx >= 0 && yy <= siz[b]){
				return true;
			}  
			else return false;
		};
		while(l < r) {
			LL mid = (l + r) >> 1;
			if(check(mid)) r = mid; //让y变大
			else l = mid + 1;
		}
		LL xx = init_x + l * delta_x, yy = init_y - l * delta_y;
		if(xx >= 0 && xx <= siz[a] && yy >= 0 && yy <= siz[b]) return xx + yy;
		return (LL)1e18;
	};
	
	for(int i = 1; i <= limit; i++) {
		for(int j = i; j <= limit; j++) {
			LL sum = w[j] - w[i - 1],tmp = presiz[j] - presiz[i - 1];
			if(n >= sum && (n - sum) % gcd(i - 1,j + 1) == 0) {//Feishu Theory
				res = min(res,gao(i - 1,j + 1,n - sum) + tmp);
			}
		}
	}// >= 3 block
	for(int i = 1; i <= limit; i++) {
		res = min(res,gao(i - 1,i,n));
	}// 2 block
	if(res == 1e18) cout << "GingerNB\n";
	else cout << res << "\n";
}
signed main() {
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