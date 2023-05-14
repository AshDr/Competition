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
mt19937 myrand(chrono::steady_clock::now().time_since_epoch().count());
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

const int N = 2e3 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
int len;
ll memo[N][N][2][2][2];
string s;
int m,d;
ll dfs(int cur, int lst, int cnt,int f, int g) {
	if(cur>=len) return cnt==len/2&&lst==0;
	if(~memo[cur][lst][cnt][f][g]) return memo[cur][lst][cnt][f][g];
	int lim=9;
	if(f) lim=s[cur]-'0';
	ll res=0;
	for(int i=0; i<=lim; i++) {
		if(i!=d) {
            if(cur%2==0) res+=dfs(cur+1,(lst*10+i)%m,cnt,f&&(i==s[cur]-'0'),g&&(i==0));
        }
		else {
			if(cur&1) res+=dfs(cur+1,(lst*10+i)%m,cnt+1,f&&(i==s[cur]-'0'),g&&(i==0));
		}
		res%=MOD;
	}
	return memo[cur][lst][cnt][f][g]=res;
} 
ll gao(string x) {
	len=sz(x);
	s=x;
	memset(memo,-1,sizeof memo);
	return dfs(0,0,0,1,1);
} 
int check(string x) {
    int sum=0;
    for(int i=0; i<sz(x); i++) {
        if(i&1) {
            if(x[i]-'0'!=d) {
                return 0;
            } 
        }else {
            if(x[i]-'0'==d) {
                return 0;
            }
        }
        sum=sum*10+x[i]-'0';
        sum%=m;
    }
    return sum==0;
}
void solve() {
	cin>>m>>d;
    string a,b;
    cin>>a>>b;
    // cout<<gao(b)<<" "<<gao(a)<<"\n";
    cout<<(((gao(b)-gao(a))%MOD)+MOD+check(a))%MOD<<"\n";
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