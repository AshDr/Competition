#include<bits/stdc++.h>
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

const int N = 1e7 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const LL MOD = 1e9 + 7;
int TT = 1;
struct node {
	int ls,rs;
}tr[N];
int n;
int a[N],rt = 1;
LL s[N];
void cartesianTree(){
	stack<int> stk;
	for(int i = 1; i <= n; i++) {
		int t = 0;
		while(!stk.empty() && a[stk.top()] < a[i]) t = stk.top(),stk.pop();
		if(stk.size()) tr[i].ls = tr[stk.top()].rs,tr[stk.top()].rs = i;
		else tr[i].ls = t,rt = i;
		stk.push(i);
	}	
}

void solve() {
	cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        s[i] = s[i - 1] + a[i];
    }
    cartesianTree();
    // cout << rt << '\n';
    // for(int i = 1; i <= n; i++) cout << i << ':' << tr[i].ls << ' ' << tr[i].rs << '\n';
    vector<vector<pair<int, LL>>> ps(2);
    ps[0].emplace_back(0, 0);
    for (int i = 1; i <= n; i++)
        ps[s[i] & 1].emplace_back(i, s[i]);
    LL ans = 0;
    function<void(int , int , int)> dfs = [&](int curm, int curl, int curr) {
        if(curm - curl < curr - curm) {
            for(int L = curl; L <= curm; L++) {
                LL p = s[L - 1];
                int resl = 0,resr = 0;
                {
                    int l = 0, r = sz(ps[p & 1]);
                    while(l < r) {
                        int mid = (l + r) >> 1;
                        if(ps[p & 1][mid].second >= p + 2 * a[curm] and ps[p & 1][mid].first >= curm) r = mid;
                        else l = mid + 1;
                    }
                    resl = l;
                }
                {
                    int l = 0, r = sz(ps[p & 1]);
                    while(l < r) {
                        int mid = (l + r) >> 1;
                        if(ps[p & 1][mid].first > curr) r = mid;
                        else l = mid + 1;
                    }
                    resr = l;
                }
                ans += max(resr - resl,0);
            }
        }
        else {
            for (int R = curm; R <= curr; R++) {
                LL p = s[R];
                int resl = 0, resr = 0;
                {
                    int l = -1, r = sz(ps[p & 1]) - 1; //!!!l - 1
                    while (l < r) {
                        int mid = (l + r + 1) / 2;
                        if (ps[p & 1][mid].second <= p - 2 * a[curm] and ps[p & 1][mid].first < curm) l = mid;
                        else r = mid - 1;
                    }
                    resl = l;
                }
                {
                    int l = -1, r = sz(ps[p & 1]) - 1;//!!!l - 1
                    while (l < r) {
                        int mid = (l + r + 1) / 2;
                        if (ps[p & 1][mid].first < curl - 1) l = mid;
                        else r = mid - 1;
                    }
                    resr = l;
                }
                ans += max(resl - resr, 0);
            }
        }
        //cout << curm << ' ' << ans << '\n';
        if(tr[curm].ls) dfs(tr[curm].ls, curl, curm - 1);
        if(tr[curm].rs) dfs(tr[curm].rs, curm + 1,curr);
    };//heuristic
    dfs(rt, 1, n);
    cout << ans << '\n';
}
int main() {
    #ifdef ASHDR
    freopen("data.in","r",stdin);
    int nol_cl = clock();
    #endif
    // ios::sync_with_stdio(0);
    // cin.tie(nullptr);
    // cout<<fixed<<setprecision(8);
    //cin>>TT;
    while(TT--) solve();
    #ifdef ASHDR
    LOG("Time: %dms\n", int ((clock()
            -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
    #endif
    return 0;
}