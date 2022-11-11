#include<bits/stdc++.h>
#define cerr cout<<"#case:"
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
const int N = 1e7 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const LL MOD = 1e9 + 7;
int T,n,m,num;
int ans[N],min_d[N],prime[N];//最小质因子
LL min_prod[N],sum[N];//最小质因子的多项式 因数和
//LL fac[N],inv[N];
LL gcd(LL x, LL y) {return y == 0 ? x : gcd(y, x % y);}
LL qpow(LL base, LL x) {
  LL res = 1;
  while(x) {
    if(x & 1) res = (res * base) % MOD;
    base = (base * base) % MOD;
    x >>= 1;
  }
  return res;
}
/*
LL binom(int n, int k) {
  if(k > n) return 0;
  return (fac[n] * inv[k] % mod * inv[n - k]) % mod;
}
*/
void init() {
	sum[1] = min_prod[1] = 1;
	for(int i = 2; i < N; i++) {
		if(!min_d[i]) {
			prime[++num] = i;
			min_prod[i] = sum[i] = (1 + i);
		}
		for(int j = 1; j <= num && prime[j] * i < N; j++) {
			LL t = prime[j] * i;
			min_d[t] = prime[j];
			if(i % prime[j] == 0) {
				min_prod[t] = min_prod[i] * prime[j] + 1;
				sum[t] = sum[i] / min_prod[i] * min_prod[t];
				break;
			}
			sum[t] = sum[i] * (prime[j] + 1);
			min_prod[t] = (1 + prime[j]);
			
		}
	}
	memset(ans,-1,sizeof ans);
	for(int i = N - 1; i >= 1; i--) if(sum[i] < N) ans[sum[i]] = i;
}
void solve() {
    cin>>n;
    cout<<ans[n]<<'\n';
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  init();
  cin>>T;
  //T = 1;
  while(T--) solve();
  return 0;
}