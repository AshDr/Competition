// 单调决策二分队列
#include<bits/stdc++.h>
//#define cerr cout<<"case#:"
#define LOG(FMT...) fprintf(stderr, FMT)
using namespace std;
typedef long long LL;
const int N = 1e5 + 10;
const int M = 1e5 + 10;
const LL INF = 1e18;
const int MOD = 1e9 + 7;
struct tup {
	int j,lb,rb;
	tup(): j(0),lb(0),rb(0){};
	tup(int _j,int _lb, int _rb): j(_j),lb(_lb),rb(_rb){};
}q[N];
int T,n,m;
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
    for (int i = 1; i < v.size(); ++i)
      os << ' ' << v[i];
  }
  return os;
}
void dbg_out(){cerr<<"\b\b )"<<endl;}
template<typename Head,typename... Tail>
void dbg_out(Head H,Tail... T){cerr<<H<<",";dbg_out(T...);}
#define debug(...) cerr<<"( "<<#__VA_ARGS__<<" ) = (",dbg_out(__VA_ARGS__)
LL gcd(LL x, LL y) {return y == 0 ? x : gcd(y, x % y);}
long double qpow(long double base, LL x) {
    long double res = 1;
    while(x) {
        if(x & 1) res *= base;
        base *= base;
        x >>= 1;
    }
    return res;
}
LL qmul(LL a,LL b,LL mod) {
    LL res = 0;
    while(b) {
        if(b & 1) res = (res + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return res;
}//快速乘
void exgcd(LL a, LL b, LL &x, LL &y) {
    if(b == 0) {
        x = 1;y = 0;
        return ;
    }
    exgcd(b,a % b,y,x);
    y -= (a / b) * x;
}//模数无限制
LL getinv(LL x,LL mod) {
    LL x_0,y_0;
    exgcd(x,mod,x_0,y_0);
    return x_0;
}
LL l,p;
LL a[N],sum[N],nxt[N];
long double dp[N];
int ans[N];
string ss[N];
long double get(int i, int j) {
	return dp[j] + qpow(abs(sum[i] - sum[j] + i - j - 1 - l),p);
}
void solve() {
	memset(dp,0,sizeof dp);
	memset(ans,0,sizeof ans);
	memset(sum,0,sizeof sum);
	memset(q,0,sizeof q);
	memset(nxt,0,sizeof nxt);
    cin>>n>>l>>p;
    for(int i = 1; i <= n; i++) {
    	cin>>ss[i];
    	a[i] = ss[i].size();
    	sum[i] = sum[i - 1] + a[i];
    }
    int hh = 0,tt = 0;
    hh = 1;
    q[++tt] = tup(0,1,n);
    for(int i = 1; i <= n; i++) {
    	while(hh < tt && q[hh].rb < i) hh++;
    	//cerr<<"case#: "<<i<<"" <<q[hh].j<<endl;
    	dp[i] = get(i,q[hh].j);
    	ans[i] = q[hh].j;
    	while(hh < tt && get(q[tt].lb,i) <= get(q[tt].lb,q[tt].j)) --tt;
    	
    	//cerr<<"case#: "<<i<<" "<<q[head].c<<endl;

    	int l = q[tt].lb,r = q[tt].rb,j = q[tt].j;
    	int bound = q[tt].rb + 1;
    	while(l <= r) {
    		int mid = (l + r) >> 1;
    		if(get(mid,i) <= get(mid,j)) bound = mid,r = mid - 1;
    		else l = mid + 1;
    	} 
    	//cerr<<"case#: "<<i<<" "<<bound<<endl;
    	if(bound != q[tt].lb) q[tt].rb = bound - 1;
    	else --tt;
    	if(bound <= n) q[++tt] = tup(i,bound,n); 
    		
    }
    if(dp[n] > INF) cout<<"Too hard to arrange"<<endl;
    else {
    	cout<<(LL)dp[n]<<endl;
    	for(int i = n; i >= 1; i = ans[i]) nxt[ans[i]] = i;
    	int cur = 0;
    	for(int i = 1; i <= n; i++) {
    		cur = nxt[cur];
    		for(int j = i; j < cur; j++) cout<<ss[j]<<" ";
    		cout<<ss[cur]<<endl;
    		i = cur;
    	}
    }
    cout<<"--------------------"<<endl;
}
int main() {
    #ifdef ASHDR
    freopen("data.in","r",stdin);
    int nol_cl = clock();
    #endif
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin>>T;
    //T = 1;
    while(T--) solve();
    #ifdef ASHDR
    LOG("Time: %dms\n", int ((clock()
          -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
    #endif
    return 0;
}