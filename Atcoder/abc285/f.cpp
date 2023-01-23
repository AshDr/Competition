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

const int N = 2e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const LL MOD = 1e9 + 7;
int TT = 1;
char s[N];
struct node {
    int mxpos[26],mnpos[26],num[26];
    int mxch,mnch;
}tr[N << 2];
int n,m;
#define lt idx<<1
#define rt idx<<1|1
void push_up(int idx) {
    for(int i = 0; i < 26; i++) {
        tr[idx].mnpos[i] = min(tr[lt].mnpos[i],tr[rt].mnpos[i]);
        tr[idx].mxpos[i] = max(tr[lt].mxpos[i],tr[rt].mxpos[i]);
        tr[idx].num[i] = tr[lt].num[i]+tr[rt].num[i];
        tr[idx].mnch = min(tr[lt].mnch,tr[rt].mnch);
        tr[idx].mxch = max(tr[lt].mxch,tr[rt].mxch);

    }
}
void build(int idx, int L, int R) {
    if(L == R) {
        for(int i = 0; i < 26; i++) tr[idx].mxpos[i]=0,tr[idx].mnpos[i]=n+1,tr[idx].num[i]=0;
        tr[idx].mnpos[s[L]-'a']=L;
        tr[idx].mxpos[s[L]-'a']=L;
        tr[idx].num[s[L]-'a']=1;
        tr[idx].mxch = s[L]-'a';
        tr[idx].mnch = s[L]-'a';
        return;
    }
    int mid = (L + R) >> 1;
    build(lt,L,mid);
    build(rt,mid+1,R);
    push_up(idx);
}
void modify(int idx, int pos, int ch, int L, int R) {
    if(L == R) {
        int curch = s[L]-'a';
        tr[idx].num[curch]=0;
        tr[idx].num[ch]=1;
        tr[idx].mnpos[curch]=n+1;
        tr[idx].mnpos[ch]=L;
        tr[idx].mxpos[curch]=0;
        tr[idx].mxpos[ch]=L;
        tr[idx].mnch=tr[idx].mxch=ch;
        return;
    }
    int mid = (L+R)>>1;
    if(pos <= mid) modify(lt, pos, ch, L, mid);
    else modify(rt, pos, ch, mid+1, R);
    push_up(idx);
}
pair<int,int> querymxandmn(int idx, int l, int r, int L, int R) {
    if(l <= L && r >= R) {
        return {tr[idx].mnch,tr[idx].mxch};
    }
    int mid = (L+R)>>1;
    pii t1,t2; 
    if(l <= mid && r > mid) {
       t1 = querymxandmn(lt,l,r,L,mid);
       t2 = querymxandmn(rt,l,r,mid+1,R);
       return {min(t1.first,t2.first),max(t1.second,t2.second)};
    }
    else if(l <= mid) {
       t1 = querymxandmn(lt,l,r,L,mid);
       return t1;
    }
    else {
       t2 = querymxandmn(rt,l,r,mid+1,R);
       return t2;
    }
}
vector<int> querymnpos(int idx, int l, int r, int L, int R) {
    if(l <= L && r >= R) {
        vector<int> tmp;
        for(int i = 0; i < 26; i++) {
            tmp.push_back(tr[idx].mnpos[i]);
        }
        return tmp;
    }
    int mid = (L+R)>>1;
    vector<int> t1,t2,res;
    if(l <= mid && r > mid) {
        t2=querymnpos(rt,l,r,mid+1,R);
        t1=querymnpos(lt, l, r, L, mid);
        for(int i = 0; i < 26; i++) {
            res.push_back(min(t1[i],t2[i]));
        }
    }
    else if(l <= mid) {
        res=querymnpos(lt, l, r, L, mid);
    }
    else {
        res=querymnpos(rt,l,r,mid+1,R);
    }
    return res;
}
vector<int> querymxpos(int idx, int l, int r, int L, int R) {
    if(l <= L && r >= R) {
        vector<int> tmp;
        for(int i = 0; i < 26; i++) {
            tmp.push_back(tr[idx].mxpos[i]);
        }
        return tmp;
    }
    int mid = (L+R)>>1;
    vector<int> t1,t2,res;
    if(l <= mid && r > mid) {
        t2=querymxpos(rt,l,r,mid+1,R);
        t1=querymxpos(lt, l, r, L, mid);
        for(int i = 0; i < 26; i++) {
            res.push_back(max(t1[i],t2[i]));
        }
    }
    else if(l <= mid) {
        res=querymxpos(lt, l, r, L, mid);
    }
    else {
        res=querymxpos(rt,l,r,mid+1,R);
    }
    return res;
}
vector<int> querynum(int idx, int l, int r, int L, int R) {
    if(l <= L && r >= R) {
        vector<int> tmp;
        for(int i = 0; i < 26; i++) {
            tmp.push_back(tr[idx].num[i]);
        }
        return tmp;
    }
    int mid = (L+R)>>1;
    vector<int> t1,t2,res;
    if(l <= mid && r > mid) {
        t2=querynum(rt,l,r,mid+1,R);
        t1=querynum(lt, l, r, L, mid);
        for(int i = 0; i < 26; i++) {
            res.push_back(t1[i]+t2[i]);
        }
    }
    else if(l <= mid) {
        res=querynum(lt, l, r, L, mid);
    }
    else {
        res=querynum(rt,l,r,mid+1,R);
    }
    return res;
}
void solve() {
    cin >> n;
    cin >> (s + 1);
    cin >> m;
    build(1,1,n);
    for(int i = 0; i < m; i++) {
        int op;
        cin >> op;
        if(op == 1) {
            int pos;
            char ch;
            cin >> pos >> ch;
            modify(1, pos, ch-'a', 1, n);
            s[pos]=ch;
        }
        else {
            int l,r,f=0;
            cin>>l>>r;
            vector<int> mnpos=querymnpos(1, l, r, 1, n);
            vector<int> mxpos=querymxpos(1, l, r, 1, n);
            for(int i = 0; i < 26; i++) {
                for(int j = i + 1; j < 26; j++) {
                    if((mxpos[i] != 0 && mnpos[i] != n+1 && mxpos[j]!=0 && mnpos[j] != n+1) && (mxpos[i] > mnpos[j])) {
                        f=1;
                        break;
                    }
                }
            }
            //nlogn
            if(f) cout << "No" << "\n";
            else {
                vector<int> num=querynum(1, l, r, 1, n);
                pii t = querymxandmn(1, l, r, 1, n);
                for(int i = t.first+1; i < t.second; i++) {
                    if(num[i] < tr[1].num[i]) {
                        f = 1;
                        break;
                    }
                }
                if(f) cout << "No" << "\n";
                else cout << "Yes" << "\n";
            }
        }
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