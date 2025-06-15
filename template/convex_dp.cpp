namespace ConvexDP {
const double eps = 1e-8;
const double slope_INF = 1e18;
// TODO: may change here
bool isLowerConvex = true;  // true for lower convex hull, false for upper convex hull
int tp = 0;                 // tp for two types of lowerbound
int sgn(double x) {
  if (fabs(x) < eps) return 0;
  if (x < 0)
    return -1;
  else
    return 1;
}
struct Point {
  double x, y, k;
  Point(double _x, double _y, double _k = (isLowerConvex ? slope_INF : -slope_INF)) : x(_x), y(_y), k(_k) {}
  bool operator<(const Point &b) const {
    if (!tp) {
      return x == b.x ? y < b.y : x < b.x;
    } else {
      if (isLowerConvex)
        return k < b.k;  // 下凸包
      else
        return k > b.k;  // 上凸包
    }
  }
  Point operator-(const Point &b) const { return {x - b.x, y - b.y, 0}; }
  double operator^(const Point &b) const { return x * b.y - y * b.x; }
};

// TODO: define your X and Y
double X(int i) { return 0.0; }
double Y(int i) { return 0.0; }

// 注意哪个点在前，哪个在后
double slope(Point a, Point b) {
  if (sgn(a.x - b.x) == 0) {
    if (sgn(b.y - a.y) > 0)
      return INF;
    else if (sgn(b.y - a.y) < 0)
      return -INF;
    else
      assert(0);
  }
  return (b.y - a.y) / (b.x - a.x);
}
set<Point> convex;
void insert(Point p) {
  tp = 0;
  if (sz(convex) == 0) {
    convex.insert(p);
    return;
  }
  auto itl = convex.lower_bound(p), itr = itl--;
  if (itr != convex.end() && itr != convex.begin()) {
    Point pre = *itl, nxt = *itr;
    if (isLowerConvex) {
      if (sgn((p - pre) ^ (nxt - pre)) <= 0) {  // 下凸包
        return;
      }
    } else {
      if (sgn((p - pre) ^ (nxt - pre)) >= 0) {  // 上凸包
        return;
      }
    }
  }
  // 向前删没用的点
  if (itr != convex.begin()) {
    auto tmp = itl--;
    while (1) {
      if (tmp == convex.begin()) {
        break;
      }
      Point pt1 = *itl, pt2 = *tmp, pt3 = p;
      if (isLowerConvex) {
        if (sgn((pt2 - pt1) ^ (pt3 - pt1)) <= 0) {
          convex.erase(tmp);
        } else
          break;
      } else {
        if (sgn((pt2 - pt1) ^ (pt3 - pt1)) >= 0) {
          convex.erase(tmp);
        } else
          break;
      }
      tmp = itl--;
    }
    Point b = *tmp;
    b.k = slope(b, p);
    convex.erase(tmp);
    convex.insert(b);  // 维护凸包的过程中，顺便维护k-1个斜率
  }
  // 向后删没用的点
  if (itr != convex.end()) {
    auto tmp = itr++;
    while (1) {
      if (itr == convex.end()) {
        break;
      }
      Point pt1 = p, pt2 = *tmp, pt3 = *itr;
      if (isLowerConvex) {
        if (sgn((pt2 - pt1) ^ (pt3 - pt1)) <= 0) {  // 下凸包
          convex.erase(tmp);
        } else
          break;
      } else {
        if (sgn((pt2 - pt1) ^ (pt3 - pt1)) >= 0) {  // 上凸包
          convex.erase(tmp);
        } else
          break;
      }
      tmp = itr++;
    }
    p.k = slope(p, *tmp);
  }
  convex.insert(p);
}
pdd query(double k0) {
  tp = 1;
  auto it = convex.lower_bound({0, 0, k0});
  if (it == convex.end()) {
    --it;
  }
  return {it->x, it->y};
}
};  // namespace ConvexDP