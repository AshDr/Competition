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
#include <queue>
#define LOG(FMT...) fprintf(stderr, FMT)
#define sz(x) (int)x.size()
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef unsigned int ui;
typedef unsigned long long ull;
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

const int N = 1e3 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
char s[N][N];
int n,m;
int col_cnt,col[N][N],siz[N*N];
const int dx[] = {-1,1,0,0};
const int dy[] = {0,0,1,-1};
bool check(int x, int y) {
	if(x<1||x>n||y<1||y>m) return false;
	return true;
}
void solve() {
    cin>>n>>m;
    for(int i=1; i<=n; i++) {
    	cin>>(s[i]+1);
    }
    for(int i=1; i<=n; i++) {
    	for(int j=1; j<=m; j++) {
    	   	if(!col[i][j]&&s[i][j]=='.') {
                ++col_cnt;
                queue<pii> q;
                q.push({i,j});
                col[i][j]=col_cnt;
                while(!q.empty()) {
                    auto [x,y]=q.front();q.pop();
                    siz[col_cnt]++;
                    for(int k=0; k<4; k++) {
                        int xx=x+dx[k],yy=y+dy[k];
                        if(check(xx, yy)&&!col[xx][yy]&&s[xx][yy]=='.') {
                            col[xx][yy]=col_cnt;
                            q.push({xx,yy});
                        }
                    }
                }
            }
        }
    }
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=m; j++) {
            if(s[i][j]=='*') {
                set<int> st;
                for(int k=0; k<4; k++) {
                    int x=i+dx[k],y=j+dy[k];
                    if(check(x, y)&&s[x][y]=='.') {
                        st.insert(col[x][y]);
                    }
                }
                int ans=1;
                for(auto c:st) {
                    ans+=siz[c];
                }
                cout<<ans%10;
            }
            else cout<<".";
        }
        cout<<"\n";
    }
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