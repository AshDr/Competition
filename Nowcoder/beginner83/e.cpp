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

// 开区间版 fw.sum(r) 表示 [0~r)
// 下标[0,n-1]
template <typename T>
struct Fenwick {
    int n;
    std::vector<T> a;
    
    Fenwick(int n = 0) {
        init(n);
    }
    
    void init(int n) {
        this->n = n;
        a.assign(n, T());
    }
    
    void add(int x, T v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] += v;
        }
    }
    
    T sum(int x) {
        auto ans = T();
        for (int i = x; i > 0; i -= i & -i) {
            ans += a[i - 1];
        }
        return ans;
    }//[1, x)
    
    T rangeSum(int l, int r) {
        return sum(r) - sum(l);
    }//[0~r)-[0~l)
    
    
    int kth(T k) {
        int x = 0;
        for (int i = 1 << std::__lg(n); i; i /= 2) {
            if (x + i <= n && k >= a[x + i - 1]) {
                x += i;
                k -= a[x - 1];
            }
        }
        return x;
    }
};

void solve() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> a(n, vector<int>(m)),id1(n, vector<int>(m)), id2(n, vector<int>(m));
	vector<Fenwick<int>> tp1(26,Fenwick<int>(n * m + 1));
	vector<Fenwick<int>> tp2(26,Fenwick<int>(n * m + 1));
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			char x;
			cin >> x;
			a[i][j] = x - 'a';
		}
	}    
	for(int i = 0,j = 0, cnt = 0; cnt < n * m; cnt++) {
		if((j == m && i % 2 == 0) || (j == -1 && i % 2 == 1)) {
			if(i % 2 == 0) j = m - 1;
			else j = 0;
			++i;
		}
		id1[i][j] = cnt;
		tp1[a[i][j]].add(cnt, 1);
		if(i & 1)j--;
		else j++;				
	}
	for(int i = 0, j = 0,cnt = 0; cnt < n * m; cnt++) {
		if((i == n && j % 2 == 0) || (i == -1 && j % 2 == 1)) {
			if(j % 2 == 0) i = n - 1;
			else i = 0;
			++j;
		}
		id2[i][j] = cnt;
		tp2[a[i][j]].add(cnt, 1);
		if(j & 1) i--;
		else i++;				
	}
	int q;
	cin >> q;
	for(int i = 0; i < q; i++) {
		int op;
		cin >> op;
		if(op == 1) {
			int x, y;
			char c;
			cin >> x >> y >> c;
			int cc = c - 'a';
			--x;--y;
			tp1[a[x][y]].add(id1[x][y], -1);
			tp2[a[x][y]].add(id2[x][y], -1);
			a[x][y] = cc;
			tp1[a[x][y]].add(id1[x][y], 1);
			tp2[a[x][y]].add(id2[x][y], 1);		
		}else if(op == 2) {
			int x, y;
			cin >> x >> y;
			--x;--y;
			int cc = a[x][y];
			int l = id1[x][y],r = n * m;
			while(l < r) {
				int mid = (l + r + 1) >> 1;
				if(tp1[cc].rangeSum(id1[x][y], mid) == mid - id1[x][y]) {
					l = mid;
				}else {
					r = mid - 1;
				}
			}
			cout << l - id1[x][y] << "\n";
		}else {
			int x, y;
			cin >> x >> y;
			--x;--y;
			int cc = a[x][y];
			int l = id2[x][y],r = n * m;
			while(l < r) {
				int mid = (l + r + 1) >> 1;
				if(tp2[cc].rangeSum(id2[x][y], mid) == mid - id2[x][y]) {
					l = mid;
				}else {
					r = mid - 1;
				}
			}
			cout << l - id2[x][y]<< "\n";
		}
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