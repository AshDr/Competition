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

const int N = 5e6 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const LL MOD = 1e9 + 7;
int TT = 1;
struct node {
    int val;
    int son[10];
};
vector<node> trie(N); 
int tot = 0;
void trie_add(vector<int>& a, int val) {
    int pos = 0;
    for(int i = 0; i < sz(a); i++) {
        int cur = a[i];
        if(!trie[pos].son[cur]) {
            trie[pos].son[cur] = ++tot;
            int nxt = trie[pos].son[cur];
            trie[nxt].val = val;
        }
        pos = trie[pos].son[cur];
        trie[pos].val = min(trie[pos].val,val);
    }
}
int trie_query(vector<int> &a) {
    int pos = 0;
    for(int i = 0; i < sz(a); i++) {
        int cur = a[i];
        if(!trie[pos].son[cur]) return -1;
        pos = trie[pos].son[cur];
    }
    return trie[pos].val;
}
void solve() {
    int n,m;
    cin >> n >> m;
    vector<pii> a(n);
    for(int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
	vector<int> t(10);
	iota(t.begin(),t.end(),0);
	trie_add(t, 0);
	for(int r = 0; r < n; r++) {
		vector<int> b(10);
		iota(b.begin(),b.end(),0);
		for(int l = r; l >= 0; l--) {
			int x = a[l].first, y = a[l].second;
			--x;--y;
			swap(b[x], b[y]);	
            trie_add(b, r - l + 1);
		}
	}	
    for(int i = 0; i < m; i++) {
    	int k;
    	cin >> k;
    	vector<int> tmp(k);
    	for(int j = 0; j < k; j++) cin >> tmp[j],tmp[j]--;
    	cout << trie_query(tmp) << '\n';
    }
}
int main() {
    #ifdef ASHDR
    freopen("data.in","r",stdin);
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