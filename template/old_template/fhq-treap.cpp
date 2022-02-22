#include<bits/stdc++.h>
//#define cerr cout<<"#case:"
#define LOG(FMT...) fprintf(stderr, FMT)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
const int N = 2e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const LL MOD = 1e9 + 7;
int TT,n,m;
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
LL MOD_sub(LL x,LL y) {
    return ((x - y) % MOD + MOD) %MOD;
}
LL MOD_add(LL x, LL y) {
    return ((x + y) % MOD + MOD) % MOD;
}

struct node {
    string s;
    int rd;
    int sz,ch[2];
}fhq[N];
int cnt = 0;
int root;
int newnode(string s) {
    ++cnt;
    fhq[cnt].s = s;fhq[cnt].sz = 1;
    fhq[cnt].ch[0] = fhq[cnt].ch[1] = 0;
    fhq[cnt].rd = rand();
    return cnt;
}
#define ls fhq[cur].ch[0]
#define rs fhq[cur].ch[1]
void push_up(int cur) {fhq[cur].sz = fhq[ls].sz + fhq[rs].sz + 1;}
void split(int cur, int limit,int &x, int &y) {
    if(!cur) {x = 0;y = 0;return ;}
    else {
        int lsz = fhq[fhq[cur].ch[0]].sz;
        //push_down
        if(limit <= lsz) {
            y = cur;
            split(fhq[cur].ch[0],limit,x,fhq[y].ch[0]);
        }  
        else {
            x = cur;
            split(fhq[cur].ch[1],limit - lsz - 1,fhq[x].ch[1],y);
        }
        push_up(cur);
    }
}
int merge(int x, int y) {
    if(!x || !y) return x + y;
    if(fhq[x].rd <= fhq[y].rd) {
        fhq[x].ch[1] = merge(fhq[x].ch[1],y);
        push_up(x);
        return x;
    }
    else {
        fhq[y].ch[0] = merge(x,fhq[y].ch[0]);
        push_up(y);
        return y;
    }
}
void insert(string s,int pos) {
    int t1,t2;
    split(root,pos - 1,t1,t2);
    root = merge(t1,merge(newnode(s),t2));
}
void query(int pos) {
    int t1,t2,t3,t4;
    split(root,pos - 1,t1,t2);
    split(t2,1,t3,t4);
    cout<<fhq[t3].s<<'\n';
    root = merge(t1,merge(t3,t4));
}
void solve() {
    cin>>n;
    for(int i = 1; i <= n; i++) {
        string s;
        cin>>s;
        insert(s,i);
    }
    cin>>m;
    for(int i = 1; i <= m; i++) {
        string s;
        int pos;
        cin>>s>>pos;
        ++pos;
        insert(s,pos);
    }
    int q;
    cin>>q;
    for(int i = 1; i <= q; i++) {
        int pos;
        cin>>pos;
        ++pos;
        query(pos);
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
    TT = 1;
    while(TT--) solve();
    #ifdef ASHDR
    LOG("Time: %dms\n", int ((clock()
            -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
    #endif
    return 0;
}