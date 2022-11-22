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

const int N = 2e2 + 10;
const int M = 1e6 + 10;
const int INF = 2147483647;
const LL MOD = 1e9 + 7;
int TT = 1;
int n, m, q, len;
int a[N][N],b[N][2];
int head[N][N],tox[M],toy[M],nxt[M],cnt;
int vis1[N][N],vis2[N][N];
int cirnum,belong[N][N],have[M][10];
int g[10];
stack<pii> stk;
vector<pii> vec[M];
char s[M];
void addedge(int ux, int uy, int vx, int vy) {
    tox[cnt] = vx;
    toy[cnt] = vy;
    nxt[cnt] = head[ux][uy];
    head[ux][uy] = cnt++;
}
void dfs(int x, int y) {
    vis1[x][y] = 1;vis2[x][y] = 1;stk.push({x,y});
    int xx = x + b[a[x][y]][0],yy = y + b[a[x][y]][1];
    if(xx < 1 || xx > n || yy < 1 || yy > m) xx = x,yy = y;
    if(!vis1[xx][yy]) dfs(xx,yy);
    else if(vis2[xx][yy]) {
        ++cirnum;
        while(!stk.empty()) {
            int tx = stk.top().first,ty = stk.top().second; 
            belong[tx][ty] = cirnum;
            have[cirnum][a[tx][ty]] = 1;
            if(stk.top().first == xx && stk.top().second == yy) {
                stk.pop();
                break;
            }
            stk.pop();
        }
    }
    if(belong[x][y] == 0 && belong[xx][yy] != 0)  vec[belong[xx][yy]].push_back({x,y});//树边上第一个点 因为我们建的是反向图 这里要注意一下
    vis2[x][y] = 0;
    if(!stk.empty() && stk.top().first == x && stk.top().second == y) stk.pop(); 
}
bool Match(int x, int y, int p) {
    if(a[x][y] == s[p] - '0') p++;
    if(p == len + 1) return 1;
    bool res = 0;
    for(int i = head[x][y]; ~i; i = nxt[i]) res |= Match(tox[i],toy[i],p);
    return res;
}
void solve() {
    memset(head,-1,sizeof head);
    cin >> n >> m >> q;
    for(int i = 1; i <= n; i++) {
    	string t;
        cin >> t;
        for(int j = 1; j <= m; j++) {
    		a[i][j] = t[j - 1] - '0';
    	}
    }
    for(int i = 0; i < 10; i++) {
    	cin >> b[i][0] >> b[i][1];
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            int xx = i + b[a[i][j]][0],yy = j + b[a[i][j]][1];
            if(xx < 1 || xx > n || yy < 1 || yy > m) xx = i,yy = j;
            addedge(xx,yy,i,j);//反向加边 形成外向树(每个点有且仅有一个入边)
        }
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(!vis1[i][j]) dfs(i,j);
        }
    }

    // for(int k = 1; k <= cirnum; k++) {
    //     cout << k << ": \n";
    //     for(int i = 1; i <= n; i++) {
    //         for(int j = 1; j <= m; j++) {
    //             if(belong[i][j] == k) {
    //                 cout << "( " << i <<',' << j <<" )" << '\n';
    //             }
    //         }
    //     }
    //     for(int i = 0; i < 10; i++) if(have[k][i]) cout << i << ' ';
    //     cout << '\n';
    //     // cout << sz(vec[k]) << '\n';
    // }
    for(int tt = 0; tt < q; tt++) {
    	cin >> (s + 1);
        len = strlen(s + 1);
        for(int i = 0; i < 10; i++) g[i] = 0;
        reverse(s + 1,s + 1 + len);
    	for(int i = 1; i <= len; i++) if(!g[s[i] - '0']) g[s[i] - '0'] = i;
        bool flag = 0;
        for(int i = 1; i <= cirnum; i++) {
            int pos = len + 1;
            for(int j = 0; j < 10; j++) {
                if(!have[i][j] && g[j]) {
                    pos = min(pos,g[j]);
                }
            }
            if(pos == len + 1) {
                flag = 1;
                break;
            }
            
            for(int j = 0; j < sz(vec[i]); j++) {
                if(Match(vec[i][j].first,vec[i][j].second,pos)) {
                    flag = 1;
                    break;
                }
                if(flag) break;

            }
            if(flag) break;
        }
        cout << (flag == 1 ? "YES\n" : "NO\n");
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