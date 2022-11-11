#include<bits/stdc++.h>
//#define cerr cout<<"#case:"
#define LOG(FMT...) fprintf(stderr, FMT)
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
const int N = 1e5 + 10;
const int M = 1e5 + 10;
const int INF = 2147483647;
const LL MOD = 1e9 + 7;
const double pi = acos(-1);
const double eps = 1e-8;
#define ASHDR
void dbg_out() { cerr << "\b\b )" << endl; }
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T){cerr << H << ", ";dbg_out(T...);}
#define debug(...) cerr << "( " << #__VA_ARGS__ << " ) = ( ", dbg_out(__VA_ARGS__)
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
struct Line {
    Point s,e;
    Line (){}
    Line (Point _s,Point _e) {
        s = _s;
        e = _e;
    }
    bool operator == (Line v) {
        return (s == v.s) && (e == v.e);
    }

    Line (Point p,double angle) {
        s = p;
        if(sgn(angle - pi / 2) == 0) {
            e = (s + Point(0,1));
        }
        else {
            e = (s + Point (1,tan(angle)));
        }
    }//根据点和倾斜角确定直线

    Line (double a,double b,double c) {
        if(sgn(a) == 0) {
            s = Point(0,-c / b);
            e = Point(1,-c / b);
        }
        else if(sgn(b == 0)) {
            s = Point(-c / a,0);
            e = Point(-c / a,1);
        }
        else {
            s = Point(0,-c / b);
            e = Point(1,(- c - a) / b);
        }
    }// ax + by + c = 0形式

    void input() {
        s.input();
        e.input();

    }
    void adjust() {
        if(e < s) swap(s,e);
    }

    double length() {
        return s.distance(e);
    }

    double angle() {
        double k = atan2(e.y - s.y,e.x - s.x);
        if(sgn(k) < 0) k += pi;
        if(sgn(k - pi) == 0) k -= pi;
        return k;
    }// 直线倾斜角 0~pi

    int relation(Point p) {
        int c = sgn((p-s) ^ (e-s));
        if(c < 0) return 1;
        else if(c > 0) return 2;
        else return 3;
    }
    // 1左侧  2 右侧  3线上

    bool pointonseg(Point p) {
        return sgn((p-s)^(e-s)) == 0 && sgn((p-s)*(p-e)) <= 0;
    }//判断点是否在线段上

    bool parallel(Line v){
        return sgn((e-s)^(v.e-v.s)) == 0;
    }//判断两向量是否平行

    int segcrossseg(Line v) {
        int d1 = sgn((e-s)^(v.s-s));
        int d2 = sgn((e-s)^(v.e-s));
        int d3 = sgn((v.e-v.s) ^ (s-v.s));
        int d4 = sgn((v.e - v.s) ^ (e - v.s));
        if((d1^d2) == -2 && (d3 ^ d4) == -2) return 2;
        return (d1 == 0 && sgn((v.s-s)*(v.s-e)) <= 0) || 
               (d2 == 0 && sgn((v.e - s)*(v.e - e)) <= 0) ||
               (d3 == 0 && sgn((s - v.s)*(s - v.e)) <= 0) ||
               (d4 == 0 && sgn((e - v.s) * (e - v.e)) <= 0);
    }
    // 两线段相交判断
    //2 规范相交
    //1 非规范相交
    //0 不相交

    int linecrossseg(Line v) {
        int d1 = sgn((e - s) ^ (v.s - s));
        int d2 = sgn((e - s) ^ (v.e - s));
        if((d1 ^ d2) == -2) return -2;
        return (d1 == 0 || d2 == 0);
    }
    // 直线与线段相交判断 当前是直线   v是线段
    //2 规范相交
    //1 不规范相交
    //0 不相交

    int linecrossline(Line v) {
        if((*this).parallel(v)) return v.relation(s)==3;
        return 2;
    }
    //两直线的关系
    //0平行
    //1重合
    //2相交

    Point crosspoint(Line v) {
        double a1 = (v.e - v.s) ^ (s - v.s);
        double a2 = (v.e - v.s) ^ (e - v.s);
        return Point((s.x * a2 - e.x * a1) / (a2 - a1),(s.y * a2 - e.y * a1) / (a2 - a1));
    }// 两直线交点 要求不重合或平行

    double dispointtoline(Point p) {
        return fabs((p-s) ^ (e-s)) / length();
    }//点到直线距离

    double dispointtoseg(Point p) {
        if(sgn((p-s)*(e-s)) < 0 || sgn((p-e)*(s-e)) < 0) 
            return min(p.distance(s),p.distance(e));
        return dispointtoline(p); 
    }//点到线段的距离

    double dissegtoseg(Line v) {
        return min(min(dispointtoseg(v.s),dispointtoseg(v.e)),min(v.dispointtoseg(s),v.dispointtoseg(e)));
    }// 线段到线段的距离 前提是不相交

    Point lineprog(Point p) {
        return s + ( ((e - s) * ((e - s) * (p - s))) / ((e - s).len2()) );
    }//点在直线上的投影

    Point symmetrypoint(Point p) {
        Point q = lineprog(p);
        return Point(2*q.x - p.x,2*q.y - p.y);
    }//关于直线的对称点
};
struct circle {
    Point p;//圆心
    double r;
    circle(){}
    circle(Point _p,double _r) {
        p = _p;
        r = _r;
    }
    circle(double x,double y,double _r) {
         p = Point(x,y);
         r = _r;
    }
    circle(Point a,Point b,Point c) {
        Line u = Line((a + b)/ 2,((a + b) / 2) + ((b - a).rotleft()));
        Line v = Line ((b + c) / 2,((b + c) / 2) + ((c - b).rotleft()));
        p = u.crosspoint(v);
        r = p.distance(a);
    }//三角形外接圆 利用两边中垂线得到圆心

    circle(Point a,Point b,Point c,bool t) {
        Line u,v;
        double m = atan2(b.y - a.y,b.x - a.x),n = atan2(c.y - a.y,c.x - a.x);
        u.s = a;
        u.e = u.s + Point(cos((n + m) / 2),sin((n + m) / 2));
        v.s = b;
        m = atan2(a.y - b.y,a.x - b.x),n = atan2(c.y - b.y,c.x - b.x);
        v.e = v.s + Point(cos((n + m) / 2),sin((n + m) / 2));
        p = u.crosspoint(v);
        r = Line (a,b).dispointtoseg(p);
    }
    void input() {
        p.input();
        cin>>r;
    }
    void output() {
        cout<<p.x<<' '<<p.y<<' '<<r<<endl;
    }
    bool operator == (circle v) {
        return (p == v.p) && sgn(r - v.r) == 0;
    }
    bool operator <(circle v) const {
        return ((p < v.p) || ((p == v.p) && sgn(r - v.r) < 0 ));
    }
    double area() {
        return pi * r * r;
    }
    double circumference() {
        return 2 * pi * r;
    }

    int relation(Point b) {
        double dst = b.distance(p);
        if(sgn(dst - r) < 0) return 2;
        else if(sgn(dst - r) == 0) return 1;
        return 0;
    }//0圆外 1圆上 2圆内

    int relationonseg(Line v) {
        double dst = v.dispointtoseg(p);
        if(sgn(dst - r) < 0) return 2;
        else if(sgn(dst - r) == 0) return 1;
        else return 0;
    }

    int relationline(Line v) {
        double dst = v.dispointtoline(p);
        if(sgn(dst - r) < 0) return 2;
        else if(sgn(dst - r) == 0) return 1;
        return 0;
    }
    // 0不相交 1相切 2相交

    int relationcircle(circle v) {
        double d = p.distance(v.p);
        if(sgn(d - r - v.r) > 0) return 5;
        if(sgn(d - r - v.r) == 0) return 4;
        double l = fabs(r - v.r);
        if(sgn(d - r - v.r) < 0 && sgn(d - l) > 0) return 3;
        if(sgn(d - l) == 0) return 2;
        if(sgn(d - l) < 0) return 1;
    }//5相离  4相切 3相交 2内切 1内含

    int pointcrosscircle(circle v,Point &p1,Point &p2) {
        int rel = relationcircle(v);
        if(rel == 1 || rel == 5) return 0;
        double d = p.distance(v.p);
        double l = (d*d + r * r - v.r * v.r ) / (2*d);
        double h = sqrt(r*r - l*l);
        Point tmp = p + (v.p - p).trunc(l);
        p1 = tmp + ((v.p - p).rotleft().trunc(h));
        p2 = tmp + ((v.p - p).rotright().trunc(h));
        if(rel == 2 || rel == 4) return 1;
        return 2;
    }
    //求两个圆的交点以及数目

    int pointcrossline(Line v,Point &p1,Point &p2) {
        if(!(*this).relationline(v)) return 0;
        Point a = v.lineprog(p);
        double d = v.dispointtoline(p);
        d = sqrt(r*r - d*d);
        if(sgn(d) == 0) { // 相切
            p1 = a;
            p2 = a;
            return 1;
        }
        // 相交
        p1 = a + (v.e - v.s).trunc(d);
        p2 = a - (v.e - v.s).trunc(d);
        return 2;
    }
    //直线与圆的交点以及个数

    double areatriangle(Point a,Point b) {
        if(sgn((p - a) ^ (p - b)) == 0) return 0.0;
        Point q[5];
        //q[0] = p;

        int len = 0;
        q[len++] = a;

        Line l(a,b);
        Point p1,p2;
        if(pointcrossline(l,q[1],q[2]) == 2) {
            if(sgn((a - q[1])*(b - q[1])) < 0) q[len++] = q[1];
            if(sgn((a - q[2])*(b - q[2])) < 0) q[len++] = q[2];
        }

        q[len++] = b;

        if(len == 4 && sgn((q[0] - q[1]) * (q[2] - q[1])) > 0) swap(q[1],q[2]);
        double res = 0;
        for(int i = 0; i < len - 1; i++) {
            if(relation(q[i]) == 0 || relation(q[i + 1]) == 0) {
                double arg = p.rad(q[i],q[i + 1]);
                
                res += r * r * arg / 2.0;
            }
            else res += fabs((q[i] - p)^(q[i + 1] - p)) / 2.0;     
        } 
        return res;
    }
};
//0 开始
struct polygon {
    int n;
    Point p[N];
    Line l[N];
    void input(int _n) {
        n = _n;
        for(int i = 0 ; i < n; i++) p[i].input();
    }
    void add(Point q) {
        p[n++] = q;
    }
    void getline() {
        for(int i = 0 ; i < n; i++) {
            l[i] = Line(p[i],p[(i + 1) % n]);
        }
    }
    int relationpoint (Point q) {
        for(int i = 0 ; i< n; i++) if(p[i] == q) return 3;
        getline();
        for(int i = 0; i < n; i++) {
            if(l[i].pointonseg(q)) return 2;
        }
        int cnt = 0;
        for(int i =0 ; i < n; i++) {
            int j = (i + 1) % n;
            int k = sgn((q - p[j])^(p[i] - p[j]));
            int u = sgn(p[i].y - q.y);
            int v = sgn(p[j].y - q.y);
            if(k > 0 && u < 0 && v >= 0) cnt++;
            if(k < 0 && v < 0 && u >= 0) cnt--;
        }
        return cnt != 0;
    }
    //3点上  2边上 1内部 0 外部
    struct cmp {
        Point p;
        cmp(const Point &p0) {p = p0;}
        bool operator ()(const Point &aa,const Point &bb) {
            Point a = aa,b = bb;
            int d = sgn((a - p) ^ (b - p));
            if(d == 0) {
                return sgn(a.distance(p) - b.distance(p)) < 0;
            }
            return d > 0;
        }
    };
    void norm() {
        Point mi = p[0];
        for(int i = 1;  i < n; i++) mi = min(mi,p[i]);
        sort(p,p + n, cmp(mi));
    }//极角排序 凸多边形用
    double getarea() {
        double sum = 0;
        for(int i = 0; i < n; i++) {
            sum += (p[i] ^ p[(i + 1) % n]);
        }
        return fabs(sum / 2);
    }
    double getcircumference() {
        double sum = 0;
        for(int i =0 ; i < n; i++) {
            sum += p[i].distance(p[(i + 1)% n]);
        }
        return sum;
    }
    void getconvex(polygon &convex){
        sort(p,p+n);
        convex.n = n;
        for(int i = 0; i < min(n,2); i++) convex.p[i] = p[i];  
        if(convex.n == 2 && (convex.p[0] == convex.p[1])) convex.n--;
        if(n <= 2) return ;
        int &top = convex.n;
        top = 1;
        for(int i = 2; i < n; i++) {
            while(top && sgn((convex.p[top] - p[i]) ^ (convex.p[top - 1] - p[i])) <= 0) top--;
            convex.p[++top] = p[i];
        }
        int temp = top;
        convex.p[++top] = p[n - 2];
        for(int i = n - 3; i >= 0; i--) {
            while(top != temp && sgn((convex.p[top] - p[i]) ^ (convex.p[top - 1] - p[i])) <= 0) top--;
            convex.p[++top] = p[i];                       
        }
        if(convex.n == 2 && (convex.p[0] == convex.p[1]))convex.n--;
        convex.norm();
    }
    double areacircle(circle c) {
        double ans = 0;
        for(int i = 0 ;i < n; i++) {
            int j = (i + 1) % n;
            if(sgn((p[j] - c.p) ^ (p[i] - c.p)) >= 0) ans += c.areatriangle(p[i],p[j]);
            else ans -= c.areatriangle(p[i],p[j]);
            //debug(ans);
        }
        
        return fabs(ans);
    }
    double cross(Point A,Point B,Point C) {
        return (B - A) ^ (C - A);
    }
    double dot(Point A,Point B,Point C) {
        return (B - A) * (C - A);
    }
    double minRectangleCover(polygon A) {
        if(A.n < 3) return 0.0;
        A.p[A.n] = A.p[0];
        double ans = -1;
        int r = 1,p = 1,q;
        for(int i = 0; i < A.n; i++) {
            while(sgn(cross(A.p[i],A.p[i + 1],A.p[r + 1]) - cross(A.p[i],A.p[i + 1],A.p[r])) >= 0)
                r = (r + 1) % A.n;
            while(sgn(dot(A.p[i],A.p[i + 1],A.p[p + 1]) - dot(A.p[i],A.p[i + 1],A.p[p])) >= 0)
                p = (p + 1)  % A.n;
            if(i == 0) q = p;
            while(sgn(dot(A.p[i],A.p[i + 1],A.p[q + 1]) - dot(A.p[i],A.p[i + 1],A.p[q])) <= 0)
                q = (q + 1) % A.n;
            double d = (A.p[i] - A.p[i + 1]).len2();
            double tmp = cross(A.p[i],A.p[i + 1],A.p[r]) * (dot(A.p[i],A.p[i+1],A.p[p]) - dot(A.p[i],A.p[i+1],A.p[q])) / d;
            if(ans < 0 || ans > tmp) ans = tmp;
        }
        return ans;
    }
};
int TT,n,m,T;
void solve() {
}

int main() {
    #ifdef ASHDR
    //freopen("data.in","r",stdin);
    freopen("data.out","w",stdout);
    int nol_cl = clock();
    #endif
    ios::sync_with_stdio(0);
    srand(time(NULL));
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