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
int sgf[1005][1005];
int sg(int x, int y) {
	if(x<=0||y<=0) return 0;
	if(x==0&&y==0) return 0;
	if(x==0&&y==1) return 0;
	if(x==0&&y==2) return 0;
	if(x==1&&y==0) return 0;
	if(x==1&&y==1) return 0;
	if(x==1&&y==2) return 1;
	if(x==2&&y==0) return 0;
	if(x==2&&y==1) return 1;
	if(!sg(x-1,y-2)||!sg(x-2,y-1)) sgf[x][y]=1;
	else sgf[x][y]=0;
	return sgf[x][y];
}
void solve1(LL a, LL b) {
	int aa=a%3,bb=b%3;
	if(aa > bb) swap(aa,bb);
	if(aa==0&&bb==0) {
		cout << "niumei\n";
	}
	else if(aa==0&&bb==1) {
		if(a%3==0&&b%3==1){
			if(b<=a-2) cout << "niuniu\n";	
			else cout << "niumei\n";
		} 
		else {
			if(b<=a-1) cout << "niumei\n";
			else cout <<"niuniu\n";
		}
	}
	else if(aa==0&&bb==2){
        if(a%3==0&&b%3==2){
            if(b<=a-1) cout << "niuniu\n";  
            else cout << "niumei\n";
        } 
        else {
            if(b<a+1) cout << "niumei\n";
            else cout <<"niuniu\n";
        }
	}
	else if(aa==1&&bb==1) {
        if(a==b) cout << "niumei\n";
        else cout << "niuniu\n";
	}
	else if(aa==1&&bb==2) {
		cout << "niuniu\n";
	}
	else {
        cout << "niuniu\n";
	}
}
void solve() {
    LL a,b;
    cin >> a >> b;
    solve1(a, b);
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
    cin>>TT;
    while(TT--) solve();
    #ifdef ASHDR
    LOG("Time: %dms\n", int ((clock()
            -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
    #endif
    return 0;
}