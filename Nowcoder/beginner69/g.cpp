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
#include <cctype>
#define LOG(FMT...) fprintf(stderr, FMT)
#define sz(x) (int)x.size()
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef unsigned int ui;
typedef unsigned long long ull;
typedef pair<double,double> pdd;
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
int n;
ll a,b,p;
ll c[N][N];
void init(int nn) {
	for(int i=1; i<=nn; i++) {
		c[i][0]=1%p;c[i][1]=i%p;
		for(int j=2; j<=i; j++) {
			c[i][j]=(c[i-1][j]+c[i-1][j-1])%p;
		}
	}
}
void solve() {
    string s;
    cin>>s;
    vector<char> alp;
    string rem;
    for(auto ch: s) {
        if(isalpha(ch)) alp.push_back(ch);
    }
    for(int i=0; i<sz(s); i++) {
        if(i==1) {
            while(!isalpha(s[i])) {
                a=a*10+s[i]-'0';
                ++i;
            }
        }
        if(s[i-1]=='+') {
            while(!isalpha(s[i])) {
                b=b*10+s[i]-'0';
                ++i;
            }
        }
        if(s[i-1]=='^') {
            while(s[i]!='%') {
                n=n*10+s[i]-'0';
                ++i;
            }
        }
        if(s[i-1]=='%') {
            rem=s.substr(i-1);
            while(i<sz(s)) {
                p=p*10+s[i]-'0';
                ++i;
            }
        }
    }
    n=max(n,1);
    a=max(a,1ll);
    b=max(b,1ll);
    p=max(p,1ll);
    if(alp.front()==alp.back()) {
        a+=b;
        ll val=qpow(a,n,p);
        if(val==0) {
            cout<<s<<" = 0"<<"\n";
            return ;
        }
        cout<<s<<" = ";
        if(val!=1) cout<<val<<"*";
        cout<<alp[0];
        if(n!=1) cout<<"^"<<n;
        cout<<rem;
    }   
    else {
        init(n);
        vector<ll> res;
        int num=0;
        for(int i=0; i<=n; i++) {
            ll x=c[n][i]*qpow(a,n-i,p)%p*qpow(b,i,p)%p;
            if(x!=0) ++num;
            res.push_back(x);
        }
        if(num==0) {
            cout<<s<<" = 0"<<"\n";
            return ;
        }
        cout<<s<<" = ";
        if(num>1) {
            cout<<'(';
        }
        for(int i=0; i<=n; i++) {
            if(res[i]==0) continue;
            else {
                if(res[i]!=1) cout<<res[i]<<"*";

                if(i==0) {
                    if(n-i!=1) cout<<alp[0]<<"^"<<n-i<<"+";
                    else cout<<alp[0]<<"+";
                }   
                else if(i==n) {
                    if(i!=1) cout<<alp[1]<<"^"<<n;
                    else cout<<alp[1];
                }
                else{
                    if(i!=1&&n-i!=1) cout<<alp[0]<<"^"<<n-i<<"*"<<alp[1]<<"^"<<i<<"+";
                    else if(n-i==1&&i==1)cout<<alp[0]<<"*"<<alp[1]<<"+";
                    else if(i==1) cout<<alp[0]<<"^"<<n-i<<"*"<<alp[1]<<"+";
                    else if(n-i==1) cout<<alp[0]<<"*"<<alp[1]<<"^"<<i<<"+";
                }
            }
        }
        if(num>1) {
            cout<<')';
        }
        cout<<rem<<"\n";
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