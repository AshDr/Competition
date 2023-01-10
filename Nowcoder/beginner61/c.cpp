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

const int N = 2e3 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const LL MOD = 1e9 + 7;
const int dx[]={1,-1,0,0};
const int dy[]={0,0,1,-1};
int TT = 1;
char s[N][N];
int go1[N][N],go2[N][N];
void solve() {
    int n, m, r1, r2;
    cin >> n >> m >> r1 >> r2;
    int sx,sy,ex,ey;
    for(int i = 1; i <= n; i++) {
    	for(int j = 1; j <= m; j++) {
    		cin >> s[i][j];
    		if(s[i][j] == 'P') {
    			sx = i;
    			sy = j;
    		}
    		if(s[i][j] == 'M') {
    			ex = i;
    			ey = j;
    		}
    	}
    }
    
    memset(go2,0x3f,sizeof go2);
    memset(go1,0x3f,sizeof go1);
    queue<pii> q1;
    q1.push({ex,ey});
    go2[ex][ey] = 0;
    while(!q1.empty()) {
    	int cx = q1.front().first,cy = q1.front().second;
    	q1.pop();
    	for(int i = 0; i < 4; i++) {
    		int xx = cx + dx[i],yy = cy + dy[i];
    		if(xx < 1 || xx > n || yy < 1 || yy > m) continue;
    		if(s[xx][yy] == '*') continue;
    		if(go2[xx][yy] > go2[cx][cy] + 1) {
    			go2[xx][yy] = go2[cx][cy] + 1;
    			q1.push({xx,yy});
    		}
    	}
    }
    queue<pii> q;
    q.push({sx,sy});
    go1[sx][sy] = 0;
    int ans = 0x3f3f3f3f;
    while(!q.empty()) {
    	int cx = q.front().first,cy = q.front().second;
    	if(abs(ex - cx) + abs(ey - cy) <= r2) {
    		ans = min(ans,go2[cx][cy] + go1[cx][cy]);
    	}
    	q.pop();
    	for(int i = 0; i < 4; i++) {
    		int xx = cx + dx[i],yy = cy + dy[i];
    		if(xx < 1 || xx > n || yy < 1 || yy > m) continue;
    		if(s[xx][yy] == '*') continue;
    		if(abs(xx - sx) + abs(yy - sy) > r1) continue;
    		if(go1[xx][yy] > go1[cx][cy] + 1) {
    			go1[xx][yy] = go1[cx][cy] + 1;
    			q.push({xx,yy});
    		}
    	}
    }
    if(ans == 0x3f3f3f3f) cout << -1 << '\n';
    else cout << ans << '\n';
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