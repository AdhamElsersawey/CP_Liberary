
const double EPS = 1e-9, PI = acos(-1.0);
#define ld long double
// point
struct point { double x, y;
    point() { x = y = 0.0; }
    point(double _x, double _y) : x(_x), y(_y) {}
    bool operator < (point other) const {
        if (fabs(x - other.x) > EPS)
            return x < other.x;
        return y < other.y;
    }
    point operator + (const point& rhs) const {
        return point(x + rhs.x, y + rhs.y);
    }

    point operator - (const point& rhs) const {
        return point(x - rhs.x, y - rhs.y);
    }

    point operator * (const double & rhs) const {
        return point(x * rhs, y * rhs);
    }

    point operator / (const double & rhs) const {
        return point(x / rhs, y / rhs);
    }
    bool operator == (point other) const {return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS)); }
    // rotate p counterclockwise around origin (0,0)
    void rotate(double theta) { // theta in DEG
        double rad = theta * PI / 180.0;
        double _x = x , _y = y;
        x = _x * cos(rad) - _y * sin(rad);
        y = _x * sin(rad) + _y * cos(rad);
    }
};
double dist(point p1, point p2) {return hypot(p1.x - p2.x, p1.y - p2.y);}
// line
struct line { double a, b, c; };
line pointsToLine(point p1, point p2) {
    line l{};
    if (fabs(p1.x - p2.x) < EPS) { // vertical line b -> 0
        l.a = 1.0;
        l.b = 0.0;
        l.c = -p1.x;
    } else { // horizontal line b -> 1
        l.a = -(double) (p1.y - p2.y) / (p1.x - p2.x);
        l.b = 1.0;
        l.c = -(double) (l.a * p1.x) - p1.y;
    }
    return l;
}
bool areParallel(line l1, line l2) {return (fabs(l1.a-l2.a) < EPS) && (fabs(l1.b-l2.b) < EPS); }
bool areSame(line l1, line l2) { return areParallel(l1 ,l2) && (fabs(l1.c - l2.c) < EPS); }
bool areIntersect(line l1, line l2, point &p) {
    if (areParallel(l1, l2)) return false; // no intersection
    // solve system of 2 linear algebraic equations with 2 unknowns
    p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
    // special case: test for vertical line to avoid division by zero
    if (fabs(l1.b) > EPS) p.y = -(l1.a * p.x + l1.c);
    else p.y = -(l2.a * p.x + l2.c);
    return true;
}

struct vec {
    double x, y;
    vec(double _x, double _y) : x(_x), y(_y) {}
};
// a -> b
vec toVec(point a, point b) { return vec(b.x - a.x, b.y - a.y); }
// non-negative s = [0 , OO[
vec scale(vec v, double s) { return vec(v.x * s, v.y * s); }
point translate(point p, vec v) {return point(p.x + v.x , p.y + v.y); }
double dot(vec a, vec b) { return (a.x * b.x + a.y * b.y); }
double norm_sq(vec v) { return v.x * v.x + v.y * v.y; }
// min dist from p to line(a,b) and c is the intersection point
double distToLine(point p, point a, point b, point &c) {
    // formula: c = a + u * ab
    vec ap = toVec(a, p), ab = toVec(a, b);
    double u = dot(ap, ab) / norm_sq(ab);
    c = translate(a, scale(ab, u));
    return dist(p, c);
}
double distToLineSegment(point p, point a, point b, point &c) {
    vec ap = toVec(a, p), ab = toVec(a, b);
    double u = dot(ap, ab) / norm_sq(ab);
    if (u < 0.0) {
        c = point(a.x, a.y);
        return dist(p, a);
    }
    if (u > 1.0) {
        c = point(b.x, b.y);
        return dist(p, b);
    }
    return distToLine(p, a, b, c);
}
double angle(point a, point o, point b) { // returns angle aob in rad
    vec oa = toVec(o, a), ob = toVec(o, b);
    return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob)));
}
double angle2(point a) { // returns angle in polar
    return atan2(a.y, a.x);
}
double cross(vec a, vec b) { return a.x * b.y - a.y * b.x; }
// returns true if point r is on the left side of line pq , >= 0 to accept collinear
bool ccw(point p, point q, point r) { return cross(toVec(p, q), toVec(p, r)) > 0; }
bool collinear(point p, point q, point r) {return fabs(cross(toVec(p, q), toVec(p, r))) < EPS; }
double area(const vector<point>& fig) { // area of simple polygon
    double res = 0;
    for (unsigned i = 0; i < fig.size(); i++) {
        point p = i ? fig[i - 1] : fig.back();
        point q = fig[i];
        res += (p.x - q.x) * (p.y + q.y);
    }
    return fabs(res) / 2;
}
/*
 * area of latic polygon
 * S = I + B/2 - 1
 * I the number of points strictly in the polygon
 * B the number of points on the boundry
 * */