#include<bits/stdc++.h>
//#define cerr cout<<"#case:"
//#define ASHDR
#define LOG(FMT...) fprintf(stderr, FMT)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
const int N = 2e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const LL MOD = 1e9 + 7;
int T,n,m;
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
    for (int i = 1; i < v.size(); ++i)
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
/*
LL binom(int n, int k) {
  if(k > n) return 0;
  return (fac[n] * inv[k] % mod * inv[n - k]) % mod;
}
*/
struct node {
    int ls,rs;
    LL sz;
}tr[N << 5];
int top,tot,rt_num;
int buff[N << 5],rt[N];
int newnode() {return (top?buff[top--]:++tot);}
void del(int i) {
    tr[i].ls = tr[i].rs = tr[i].sz = 0;
    buff[++top] = i;
}
void modify(int &i, int L, int R, int pos, int val) {
    if(!i) i = newnode();
    tr[i].sz += val;
    if(L == R) return ;
    int mid = (L + R) >> 1;
    if(pos <= mid) modify(tr[i].ls,L,mid,pos,val);
    else modify(tr[i].rs,mid + 1,R,pos,val);
}
LL range_query(int i, int L, int R, int l, int r) {
    if(l <= L && r >= R) return tr[i].sz;
    if(R < l || L > r) return 0;
    int mid = (L + R) >> 1;
    return range_query(tr[i].ls,L,mid,l,r) + range_query(tr[i].rs,mid + 1,R,l,r);
}
void split(int i,int &y,LL lim) {// 1~y-1   y-1~n 
    if(i == 0) return;
    y = newnode();
    LL szz = tr[tr[i].ls].sz;
    if(lim > szz) split(tr[i].rs,tr[y].rs,lim - szz);
    else swap(tr[i].rs,tr[y].rs);
    if(szz > lim) split(tr[i].ls,tr[y].ls,lim);
    tr[y].sz = tr[i].sz - lim;
    tr[i].sz = lim;
    return ;
}
int merge(int x, int y) {
    if(!x || !y) return x + y;
    tr[x].sz += tr[y].sz;
    tr[x].ls = merge(tr[x].ls,tr[y].ls);
    tr[x].rs = merge(tr[x].rs,tr[y].rs);
    del(y);
    return x;
}
int kth(int i,int L, int R,int k) {
    if(L == R) return L;
    LL szz = tr[tr[i].ls].sz; 
    int mid = (L + R) >> 1;
    if(k <= szz) return kth(tr[i].ls,L,mid,k);
    else return kth(tr[i].rs,mid + 1,R,k - szz);
} 
void solve() {
    cin>>n>>m;
    rt_num = 1;
    for(int i = 1; i <= n; i++) {
        int x;
        cin>>x;
        modify(rt[1],1,n,i,x);
    }
    for(int i = 1; i <= m; i++) {
        //debug(i);
        int op,x,y,z;
        cin>>op;
        if(op == 0) {
            cin>>x>>y>>z;
            LL num1 = range_query(rt[x],1,n,1,z);
            LL num2 = range_query(rt[x],1,n,y,z);
            //debug(i,num1,num2);
            int tmp;
            split(rt[x],rt[++rt_num],num1 - num2);
            split(rt[rt_num],tmp,num2);
            rt[x] = merge(rt[x],tmp);
        }
        else if(op == 1) {
            cin>>x>>y;
            rt[x] = merge(rt[x],rt[y]);
        }
        else if(op == 2) {
            cin>>x>>y>>z;
            modify(rt[x],1,n,z,y);
        }
        else if(op == 3) {
            cin>>x>>y>>z;
            cout<<range_query(rt[x],1,n,y,z)<<'\n';
        }
        else if(op == 4) {
            cin>>x>>y;
            if(tr[rt[x]].sz < y) cout<<-1<<'\n';
            else cout<<kth(rt[x],1,n,y)<<'\n';
        }
    }
}
int main() {
  #ifdef ASHDR
  freopen("data.in","r",stdin);
  //freopen("data.out","w",stdout);
  int nol_cl = clock();
  #endif
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  cout<<fixed<<setprecision(8);
  //cin>>T;
  T = 1;
  while(T--) solve();
  #ifdef ASHDR
    LOG("Time: %dms\n", int ((clock()
          -nol_cl) / (double)CLOCKS_PER_SEC * 1000));
  #endif
  return 0;
}