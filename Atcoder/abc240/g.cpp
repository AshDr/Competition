#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int MAXN = 1e7 + 5;
const int mod = 998244353;

inline void add_mod(int &a,int b){ a+=b; if(a>=mod) a-=mod;}

inline ll pw(ll a,ll b)
{
    ll res = 1;
    while(b)
    {
        if(b&1) res=res*a%mod;
        a=a*a%mod; b>>=1;
    }
    return res;
}

ll fac[MAXN], inv[MAXN];
inline ll C(int n,int m){ return n<0||m<0||n<m? 0: fac[n] * inv[m] %mod * inv[n-m] %mod;}

int main(void)
{
    fac[0] = 1;
    for(int i=1; i<MAXN; ++i) fac[i] = fac[i-1] * i %mod;
    inv[MAXN-1] = pw(fac[MAXN-1], mod-2);
    for(int i=MAXN-2; i>=0; --i) inv[i] = inv[i+1] * (i+1) %mod;
    
    int n,x,y,z;
    scanf("%d%d%d%d",&n,&x,&y,&z);
    
    {
        int xx = x+y, yy = x-y;
        x = xx; y = yy;
    }
    
    auto calc = [&] (int p,int q) -> ll
    {
        if((p+q)%2 != 0) return 0;
        return C(p, (p+q)/2);
    };
    
    int ans = 0;
    for(int i=0; i<=n; ++i)
        ans = (ans + C(n, i) * calc(i, z) %mod * calc(n-i, x) %mod * calc(n-i, y)) %mod;
    printf("%d",ans);
    return 0;
}