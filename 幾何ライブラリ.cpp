#include "bits/stdc++.h"
using namespace std;

//定義系

double EPS = 1e-10;

//誤差を考慮して足し算を行う
double add(double a, double b) {
	if (abs(a + b) < EPS*(abs(a) + abs(b)))return 0;
	return a + b;
}

//Point
struct Point {
	double x, y;
	Point() {}
	Point(double x, double y) :x(x), y(y) {
	}
	Point operator + (Point p) {
		return Point(add(x, p.x), add(y, p.y));
	}
	Point operator - (Point p) {
		return Point(add(x, -p.x), add(y, -p.y));
	}
	Point operator * (double d) {
		return Point(x*d, y*d);
	}
	Point operator / (double d) {
		return Point(x / d, y / d);
	}
	//内積
	double dot(Point p) {
		return add(x*p.x, y*p.y);
	}
	//外積
	double det(Point p) {
		return add(x*p.y, -y*p.x);
	}
	//点の大小比較
	bool operator <(const Point &p)const {
		if (fabs(add(x, -p.x))<EPS)return y<p.y;
		return x<p.x;
	}
	bool operator ==(const Point &p)const {
		return fabs(x - p.x) < EPS&&fabs(y - p.y) < EPS;
	}
};

//ベクトル。使い分けるといいかも
typedef Point Vector;

//ベクトルの大きさの2乗
double norm(Vector p) {
	return p.x*p.x + p.y*p.y;
}

//ベクトルの大きさ
double abs(Vector p) {
	return sqrt(norm(p));
}

//線分
struct Segment {
	Point p1, p2;
};

//直線
typedef Segment Line;

//中心c,半径rの円
struct Circle {
	Point c;
	double r;
	Circle(Point c = Point(), double r = 0.0) :c(c), r(r) {}
};

//多角形
typedef vector<Point> Polygon;

//頂点集合
typedef vector<Point> Points;




//計算・アルゴリズム系


//反時計回りCCW
static const int COUNTER_CLOCKWISE = 1;
static const int CLOCKWISE = -1;
static const int ONLINE_BACK = 2;
static const int ONLINE_FRONT = -2;
static const int ON_SEGMENT = 0;
int ccw(Point p0, Point p1, Point p2) {
	Vector a = p1 - p0;
	Vector b = p2 - p0;
	if (a.det(b) > EPS)return COUNTER_CLOCKWISE;
	if (a.det(b) < -EPS)return CLOCKWISE;
	if (a.dot(b) < -EPS)return ONLINE_BACK;
	if (norm(a)<norm(b))return ONLINE_FRONT;

	return ON_SEGMENT;
}

//線分p1p2と線分p3p4の交差判定
bool intersect(Point p1, Point p2, Point p3, Point p4) {
	return (ccw(p1, p2, p3)*ccw(p1, p2, p4) <= 0 && ccw(p3, p4, p1)*ccw(p3, p4, p2) <= 0);
}
bool intersect(Segment s1, Segment s2) {
	return intersect(s1.p1, s1.p2, s2.p1, s2.p2);
}

//ベクトルa,bの直交判定
bool isOrthogonal(Vector a, Vector b) {
	return a.dot(b) == 0.0;
}
bool isOrthogonal(Point a1, Point a2, Point b1, Point b2) {
	return isOrthogonal(a1 - a2, b1 - b2);
}
bool isOrthogonal(Segment s1, Segment s2) {
	return (s1.p2 - s1.p1).dot(s2.p2 - s2.p1) == 0.0;
}

//ベクトルa,bの並行判定
bool isParallel(Vector a, Vector b) {
	return a.det(b) == 0.0;
}
bool isParallel(Point a1, Point a2, Point b1, Point b2) {
	return isParallel(a1 - a2, b1 - b2);
}
bool isParallel(Segment s1, Segment s2) {
	return (s1.p2 - s1.p1).det(s2.p2 - s2.p1) == 0.0;
}

//射影(点p1と点p2を通る直線に点pから垂線を引いた交点xを求める)
Point project(Segment s, Point p) {
	Vector base = s.p2 - s.p1;
	double r = (p - s.p1).dot(base) / norm(base);
	return s.p1 + base*r;
}

//反射(点p1と点p2を通る直線を対象軸として点pと線対称の位置にある点xを求める)
Point reflect(Segment s, Point p) {
	return p + (project(s, p) - p)*2.0;
}

//点aと点bの距離
double getDistance(Point a, Point b) {
	return abs(a - b);
}

//直線lと点pの距離
double getDistanceLP(Line l, Point p) {
	return abs((l.p2 - l.p1).det(p - l.p1) / abs(l.p2 - l.p1));
}

//線分sと点pの距離
double getDistanceSP(Segment s, Point p) {
	if ((s.p2 - s.p1).dot(p - s.p1) < 0.0)return abs(p - s.p1);
	if ((s.p1 - s.p2).dot(p - s.p2) < 0.0)return abs(p - s.p2);
	return getDistanceLP(s, p);
}

//線分s1と線分s2の距離
double getDistance(Segment s1, Segment s2) {
	if (intersect(s1, s2))return 0.0;
	return min({ getDistanceSP(s1, s2.p1), getDistanceSP(s1, s2.p2), getDistanceSP(s2, s1.p1), getDistanceSP(s2, s1.p2) });
}

//線分s1と線分s2の交点
Point getCrossPoint(Segment s1, Segment s2) {
	Vector base = s2.p2 - s2.p1;
	double d1 = abs(base.det(s1.p1 - s2.p1));
	double d2 = abs(base.det(s1.p2 - s2.p1));
	double t = d1 / (d1 + d2);
	return s1.p1 + (s1.p2 - s1.p1)*t;
}

//円cと線分lの交点
pair<Point, Point>getCrossPoints(Circle c, Line l) {
	Vector pr = project(l, c.c);
	Vector e = (l.p2 - l.p1) / abs(l.p2 - l.p1);
	double base = sqrt(c.r*c.r - norm(pr - c.c));
	return make_pair(pr + e*base, pr - e*base);
}

//円c1と円c2の交点
double arg(Vector p) { return atan2(p.y, p.x); }
Vector polar(double a, double r) { return Point(cos(r)*a, sin(r)*a); }
pair<Point, Point>getCrossPoints(Circle c1, Circle c2) {
	double d = abs(c1.c - c2.c);
	double a = acos((c1.r*c1.r + d*d - c2.r*c2.r) / (2 * c1.r*d));
	double t = arg(c2.c - c1.c);
	return make_pair(c1.c + polar(c1.r, t + a), c1.c + polar(c1.r, t - a));
}

//点の内包 0:in,1:on,2:out
int contains(Polygon g, Point p) {
	int n = g.size();
	bool x = false;
	for (int i = 0; i < n; i++) {
		Point a = g[i] - p, b = g[(i + 1) % n] - p;
		if (abs(a.det(b)) < EPS&&a.dot(b) < EPS) return 1;
		if (a.y > b.y)swap(a, b);
		if (a.y < EPS&&EPS < b.y&&EPS < a.det(b))x = !x;
	}
	return (x ? 2 : 0);
}

//凸包を求める
Polygon convex_hull(Polygon s,bool on_seg) {
	Polygon u, l;
	if (s.size() < 3) {
		return s;
	}
	sort(s.begin(), s.end());//x,yを基準に昇順ソート

	//xが小さいものから2つuに追加
	u.emplace_back(s[0]);
	u.emplace_back(s[1]);
	//xが大きいものから2つlに追加
	l.emplace_back(s[s.size()-1]);
	l.emplace_back(s[s.size()-2]);

	if (on_seg) {

		//凸包の上部を生成
		for (int i = 2; i < s.size(); i++) {
			for (int n = u.size(); n >= 2 && ccw(u[n - 2], u[n - 1], s[i]) == COUNTER_CLOCKWISE; n--) {
				u.pop_back();
			}
			u.emplace_back(s[i]);
		}

		//凸包の下部を生成
		for (int i = s.size() - 3; i >= 0; i--) {
			for (int n = l.size(); n >= 2 && ccw(l[n - 2], l[n - 1], s[i]) == COUNTER_CLOCKWISE; n--) {
				l.pop_back();
			}
			l.emplace_back(s[i]);
		}
	}
	else {
		//凸包の上部を生成
		for (int i = 2; i < s.size(); i++) {
			for (int n = u.size(); n >= 2 && ccw(u[n - 2], u[n - 1], s[i]) != CLOCKWISE; n--) {
				u.pop_back();
			}
			u.emplace_back(s[i]);
		}

		//凸包の下部を生成
		for (int i = s.size() - 3; i >= 0; i--) {
			for (int n = l.size(); n >= 2 && ccw(l[n - 2], l[n - 1], s[i]) != CLOCKWISE; n--) {
				l.pop_back();
			}
			l.emplace_back(s[i]);
		}
	}
	//時計回りになるように凸包の点の列を生成
	reverse(l.begin(), l.end());
	for (int i = u.size() - 2; i >= 1; i--) {
		l.push_back(u[i]);
	}
	return l;
}

