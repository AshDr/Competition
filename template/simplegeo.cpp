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