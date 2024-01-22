#include<bits/stdc++.h>

using namespace std;

#define re			register
#define int			long long
#define fi			first
#define se			second
#define pb 			push_back
#define all(x)		x.begin(), x.end()
#define max(a, b)	(a > b ? a : b)
#define min(a, b)	(a < b ? a : b)
#define il			inline
#define abs(x)		((x ^ (x >> 63)) - (x >> 63))

typedef pair<int, int> PII;

const int N = 1e6 + 10;
const int M = 1e6 + 10;
const int INF = 1e18, P = 998244353;
const double eps = 1e-6;

il int  read() { re int x = 0; re bool f = true; re char c = getchar(); while (c < 48 || c > 57) { if (c == '-') f = false; c = getchar(); } while (c >= 48 && c <= 57) x = (x << 3) + (x << 1) + c - 48, c = getchar(); return f ? x : -x; }
il void write(int x) { if (x < 0) putchar('-'), x = -x; if (x > 9) write(x / 10); putchar(x % 10 + 48); }
il void wel(int x) { write(x), putchar('\n'); }
il void wsp(int x) { write(x), putchar(' '); }

int n, q;

set <int> c[200005];

signed main() {
    scanf("%lld%lld", &n, &q);
    for (int i = 1, a; i <= n; ++ i) {
    	scanf("%lld", &a);
    	c[i].insert(a);
	}
	while (q -- ) {
		int a, b;
		scanf("%lld%lld", &a, &b);
		if (c[a].size() < c[b].size()) {
			for (set <int> :: iterator it = c[a].begin(); it != c[a].end(); ++ it) c[b].insert(*it);
			c[a].clear();
			printf("%lld\n", (int)c[b].size());
		} else {
			for (set <int> :: iterator it = c[b].begin(); it != c[b].end(); ++ it) c[a].insert(*it);
			c[b].clear();
			swap(c[a], c[b]);
			printf("%lld\n", (int)c[b].size());
		}
	}
    return 0;
}