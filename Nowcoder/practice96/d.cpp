#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define double long double
const int maxn = 2105;
int prime[maxn], np[maxn], tot = 0;
double lg_p[maxn];

void init(int n) {
    np[1] = 1;
    for(int i = 2; i <= n; ++i) {
        if(!np[i]) prime[++tot] = i;
        for(int j = 1; j <= tot; ++j) {
            if(i * prime[j] > n) break;
            np[i * prime[j]] = 1;
            if(i % prime[j] == 0) break;
        }
    }
}
int main() {
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    init(maxn - 1);
    for(int i = 1; i <= tot; ++i) lg_p[i] = log2((double)prime[i]) - 1;
    const ll inf = 1e12;
    vector<vector<ll>> a(11);
    for(int k = 0; k <= 10; ++k) {
        int cnt = 0;
        function<void(ll, double, int)> dfs = [&](ll cur, double lg, int p) {
            if(p == tot) {
                a[k].push_back(cur);
                return;
            }
            while(1) {
                dfs(cur, lg, p + 1);
                cur *= prime[p];
                lg += lg_p[p];
                if(cur > inf || lg > k) return;
            }
        };
        dfs(1, 0, 1);
        sort(a[k].begin(), a[k].end());
    } // 对每一种k打表 因为 log2(x) - k - nump 随着x的变大增长很快，对于k = 10 来说，仅有200w个数满足要求，k越小，满足要求的数越少
    int t;
    cin >> t;
    while(t--) {
        ll l, r;
        int k;
        cin >> l >> r >> k;
        cout << upper_bound(a[k].begin(), a[k].end(), r) - lower_bound(a[k].begin(), a[k].end(), l) << '\n';
    }
}