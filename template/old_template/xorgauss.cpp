#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstring>
#include <iomanip>
//#define cerr cout<<"#case:"
#define LOG(FMT...) fprintf(stderr, FMT)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
const int N = 1e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const LL MOD = 1e9 + 7;
int TT,n,m;


//LL fac[N],inv[N];
LL gcd(LL x, LL y) {return y == 0 ? x : gcd(y, x % y);}
LL qpow(LL base, LL x, LL mod = MOD) {
    LL res = 1;
    while(x) {
       if(x & 1) res = (res * base) % mod;
       base = (base * base) % mod;
       x >>= 1;
    } 
    return res;
}

#define endl '\n'
LL a[60],ans[60];
LL xorGauss() {
    int nwline = 1;
    for(int i = n; i >= 1; i--) {
        int pos = nwline;
        for(int j = nwline; j <= n; j++) {
            if((a[j] >> i) & 1) {
                pos = j;
                break;
            }
        }
        if(!((a[pos] >> i) & 1)) continue;
        if(pos != nwline) swap(a[pos],a[nwline]);
        for(int j = nwline + 1; j <= n; j++) {// 或者1~n
            if((a[j] >> i) & 1) a[j] ^= a[nwline];
        }
        ++nwline;
    }
    if(nwline <= n) {
        for(int i = 1; i <= n; i++) {
            if(a[i] == 1) return -1;
            if(a[i] == 0) return 1ll << (n - i + 1);
        }
    }
    for (int i = 1; i <= n; i++) {
        int res = a[i] & 1;
        for (int j = i - 1; j; j--)
            res ^= ((a[i] >> j) & 1) ^ ans[j];
        ans[i] = res;
    }
    return 1;
}
void solve() {
    cin>>n;
    for(int i = 1; i <= n; i++) cin>>a[i];
    for(int i = 1; i <= n; i++) {
        int t;
        cin>>t;
        a[i] ^= t;
        a[i] |= (1 << i);
    }
    int x,y;
    while(cin>>x>>y) {
        if(x == 0 && y == 0) break;
        a[y] |= (1 << x);
    }
    LL ans = xorGauss();
    if(ans == -1) cout<<"Oh,it's impossible~!!"<<endl;
    else cout<<ans<<endl;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout<<fixed<<setprecision(8);
    cin>>TT;
    //TT = 1;
    while(TT--) solve();
    return 0;
}