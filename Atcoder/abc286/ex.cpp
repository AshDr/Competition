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
#include <istream>
#include <vector>
#define LOG(FMT...) fprintf(stderr, FMT)
#define sz(x) (int)x.size()
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
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

const int N = 2e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const ll MOD = 1e9 + 7;
int TT = 1;
const double pi = acos(-1);
const double eps = 1e-8;
int sgn(double x) {
    if(fabs(x) < eps) return 0;
    if(x < 0) return -1;
    else return 1;
}
inline double sqr(double x) {return x * x;}
struct Point {
    double x,y;
    Point(){}
    Point(double _x,double _y) {
        x = _x;
        y = _y;
    }
    void input() {
        cin>>x>>y;
    }
    void output() {
        cout<<x<<' '<<y<<endl;
    }
    friend std::ostream & operator << (std::ostream & os,
	    const Point & rhs) {
	    return os << rhs.x << " " << rhs.y;
	}
	friend std::istream & operator >> (std::istream & is, Point & rhs) {
	    is >> rhs.x >> rhs.y;
	    return is;
	}
    bool operator == (Point b) const {
        return sgn(x - b.x) == 0 && sgn(y - b.y) == 0;
    }
    bool operator < (Point b) const {
        return sgn(x - b.x) == 0 ? sgn(y - b.y) < 0 : x < b.x;
    }
    Point operator - (const Point &b) const{
        return Point(x - b.x, y - b.y);
    }
    double operator ^ (const Point & b) const {
        return x * b.y - y * b.x;
    }
    double operator *(const Point &b) const{
        return x*b.x + y*b.y;
    }
    double len() {
        return hypot(x,y);
    }//到原点长度
    double len2() {
        return x * x + y * y;
    }
    double distance(Point p) {
        return hypot(x - p.x,y - p.y);
    }//两点距离
    Point operator + (const Point &b) const {
        return Point(x + b.x,y + b.y);
    } 
    Point operator *(const double &k) const {
        return Point(x * k,y * k);
    }
    Point operator / (const double &k) const{
        return Point(x / k,y / k);
    }
    double rad(Point a,Point b) {
        Point p = *this;
        return fabs(atan2(fabs((a - p) ^ (b - p)),(a - p) * (b - p)));
    }// 求 pa pb 夹角
    Point trunc(double r) {
        double l = len();
        if(!sgn(l)) return *this;
        r /= l;
        return Point(x*r,y*r);
    }//点转vec
    
    Point rotleft() {
        return Point(-y,x);
    }//逆90°
    
    Point rotright() {
        return Point(y,-x);
    }//顺90°

    Point rotate(Point p,double angle) { // 弧度
        Point v = (*this) - p;
        double c = cos(angle),s = sin(angle);
        return Point(p.x + v.x*c - v.y*s,p.y + v.x*s + v.y*c);
    }//绕p转x°
};
vector<Point> convexHull(vector<Point> ps) {    // 求凸包
	int n = ps.size(); if(n <= 1) return ps;
	sort(ps.begin(), ps.end());
	vector<Point> qs(n * 2); int k = 0;
	for (int i = 0; i < n; qs[k++] = ps[i++]) 
		while (k > 1 && sgn((qs[k - 1] - qs[k - 2])^(ps[i] - qs[k - 2])) <= 0) --k;
	for (int i = n - 2, t = k; i >= 0; qs[k++] = ps[i--])
		while (k > t && sgn((qs[k - 1] - qs[k - 2])^(ps[i] - qs[k - 2])) <= 0) --k;
	qs.resize(k - 1);
	return qs;
}
int n;
void solve() {
	cin >> n;
	vector<Point> pts(n);
	for(int i = 0; i < n; i++) {
		cin >> pts[i];
	}
	Point s,t;
	cin >> s >> t;
	pts.push_back(s);
	pts.push_back(t);
    vector<Point> conh = convexHull(pts);
    auto ps = find(conh.begin(),conh.end(),s);
    auto pt = find(conh.begin(),conh.end(),t);
    double ans = 0;
    if(ps==conh.end()||pt==conh.end()) {
        ans = s.distance(t);
    }
    else {
        double ans1 = 0,ans2 = 0;
        for(auto i = ps; i != pt;) {
            auto nxt = next(i);
            if(nxt == conh.end()) {
                nxt = conh.begin();
            }
            ans1 += i->distance(*nxt);
            i = nxt;
        }
        for(auto i = pt; i != ps;) {
            auto nxt = next(i);
            if(nxt == conh.end()) {
                nxt = conh.begin();
            }
            ans2 += i->distance(*nxt);
            i = nxt;
        }
        ans = min(ans1,ans2);
    }
    cout << ans << "\n";
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