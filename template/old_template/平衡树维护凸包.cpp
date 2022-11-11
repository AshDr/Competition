// convex
#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

double a[N], b[N], r[N];
double f[N];
int n;
double S;

const double eps = 1e-8;

int cmp(double i, double j) {
    return (fabs(i - j) < eps) ? 0 : ((i < j) ? -1 : 1);
}

struct point {
    double x, y;
    point(double _x = 0, double _y = 0) : x(_x), y(_y) {};
    friend bool operator< (point i, point j) {
        return (cmp(i.x, j.x) == 0) ? (cmp(i.y, j.y) < 0) : (cmp(i.x, j.x) < 0);
    }
    friend double operator* (point i, point j) {
        return i.x * j.y - i.y * j.x;
    }
    friend point operator- (point i, point j) {
        return point(i.x - j.x, i.y - j.y);
    }
};

struct line {
    point p0, p1;
    line(point _x, point _y) : p0(_x), p1(_y) {};
    friend bool operator< (line i, line j) {
        return (cmp((i.p1 - i.p0) * (j.p1 - j.p0), 0) < 0);
    }
};

set<point> sp;
set<line> sl;

void ins(point h) {
    set<point>::iterator l, r, t;
    l = r = sp.lower_bound(h);
    l--;

    if (cmp((*l - *r) * (*l - h), 0) < 0)
        return;

    sl.erase(line(*l, *r));
    sp.insert(h);

    while (1) {
        t = r;
        r++;

        if (r == sp.end())
            break;

        if (cmp((h - *t) * (h - *r), 0) < 0)
            break;

        sl.erase(line(*t, *r));
        sp.erase(t);
    }

    while (1) {
        if (l == sp.begin())
            break;

        t = l;
        l--;

        if (cmp((*l - h) * (*t - h), 0) < 0)
            break;

        sl.erase(line(*l, *t));
        sp.erase(t);
    }

    sp.insert(h);
    l = r = sp.find(h);
    l--, r++;
    sl.insert(line(*l, h));
    sl.insert(line(h, *r));
}

void add(int h) {
    double x = f[h] / (a[h] * r[h] + b[h]), y = x * r[h];
    ins(point(x, y));
}

int main() {
    scanf("%d%lf", &n, &S);

    for (int i = 1; i <= n; i++)
        scanf("%lf%lf%lf", &a[i], &b[i], &r[i]);

    sp.insert(point()), sp.insert(point(1e10, -1e20));
    sl.insert(line(point(), point(1e10, -1e20)));
    f[1] = S;
    add(1);

    for (int i = 2; i <= n; i++) {
        set<line>::iterator t = sl.lower_bound(line(point(), point(a[i], -b[i])));
        point h = t -> p0;
        f[i] = max(f[i - 1], h.x * b[i] + h.y * a[i]);
        add(i);
    }

    printf("%.3lf\n", (double) f[n]);
    return 0;
}