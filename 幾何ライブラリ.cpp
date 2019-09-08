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
		if (fabs(add(x, -p.x)) < EPS)return y < p.y;
		return x < p.x;
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

//線分集合
typedef vector<Segment> Segments;

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
	if (norm(a) < norm(b))return ONLINE_FRONT;

	return ON_SEGMENT;
}

//線分p1p2と線分p3p4の交差判定
bool intersect(Point p1, Point p2, Point p3, Point p4) {
	return (ccw(p1, p2, p3)*ccw(p1, p2, p4) <= 0 && ccw(p3, p4, p1)*ccw(p3, p4, p2) <= 0);
}
bool intersectSS(Segment s1, Segment s2) {
	return intersect(s1.p1, s1.p2, s2.p1, s2.p2);
}
bool intersectLS(Line l, Segment s){
	return ccw(l.p1, l.p2, s.p1)*ccw(l.p1, l.p2, s.p2) <= 0;
}
//直線
static const int ICC_SEPERATE = 4;
static const int ICC_CIRCUMSCRIBE = 3;
static const int ICC_INTERSECT = 2;
static const int ICC_INSCRIBE = 1;
static const int ICC_CONTAIN = 0;

//円と円の交差判定
int intersect(Circle c1, Circle c2) {
	if (c1.r<c2.r) swap(c1, c2);
	double d = abs(c1.c - c2.c);
	double r = c1.r + c2.r;
	if (d == r) return ICC_CIRCUMSCRIBE;
	if (d>r) return ICC_SEPERATE;
	if (d + c2.r== c1.r) return ICC_INSCRIBE;
	if (d + c2.r<c1.r) return ICC_CONTAIN;
	return ICC_INTERSECT;
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
	if (intersectSS(s1, s2))return 0.0;
	return min({ getDistanceSP(s1, s2.p1), getDistanceSP(s1, s2.p2), getDistanceSP(s2, s1.p1), getDistanceSP(s2, s1.p2) });
}

//線分s1と線分s2の交点
Point getCrossPoint(Segment l, Segment m) {
	double d1 = (l.p2 - l.p1).det( m.p2 - m.p1);
	double d2 = (l.p2 - l.p1).det( l.p2 - m.p1);
	if (abs(d1) < EPS && abs(d2) < EPS) return m.p1;
	return m.p1 + (m.p2 - m.p1) * d2 / d1;
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


//点pを通る円cの接線
pair< Point, Point > tangent( Circle c1, Point p2) {
	pair<Point, Point> d = getCrossPoints(c1, Circle(p2, sqrt(norm(c1.c - p2) - c1.r * c1.r)));
	return  minmax(d.first, d.second);

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

//凸包を求める(辺上も含める場合は!=CLOCKWISEを==COUNTER_CLOCKWISEに)
Polygon convex_hull(Polygon s){
	Polygon u, l;
	if((int)s.size() < 3)return s;
	sort(s.begin(), s.end());
	u.emplace_back(s[0]);
	u.emplace_back(s[1]);
	l.emplace_back(s[(int)s.size() - 1]);
	l.emplace_back(s[(int)s.size() - 2]);

	//辺上も含める場合は!=CLOCKWISEを==COUNTER_CLOCKWISEに
	for(int i = 2;i < (int)s.size();i++){
		for(int n = (int)u.size();n >= 2 && ccw(u[n - 2], u[n - 1], s[i]) != CLOCKWISE;n--){
			u.pop_back();
		}
		u.emplace_back(s[i]);
	}

	//辺上も含める場合は!=CLOCKWISEを==COUNTER_CLOCKWISEに
	for(int i = (int)s.size() - 3;i >= 0;i--){
		for(int n = l.size();n >= 2 && ccw(l[n - 2], l[n - 1], s[i]) != CLOCKWISE;n--){
			l.pop_back();
		}
		l.emplace_back(s[i]);
	}
	reverse(l.begin(), l.end());
	for(int i = (int)u.size() - 2;i >= 1;i--)l.emplace_back(u[i]);

	return l;
}
//y座標の昇順でマージするための比較関数
bool compare_y(Point a, Point b) {
	return a.y < b.y;
}

//最近点対
double closest_pair(Point *a, int n) {
	if (n <= 1)return INF<double>();
	sort(a, a + n);
	int m = n / 2;
	double x = a[m].x;
	double d = min({ closest_pair(a,m),closest_pair(a + m,n - m) });//p,qが違う区間にある
	inplace_merge(a, a + m, a + n, compare_y);//2つのソートされた列をマージ

											  //p,qが同じ区間にある
	Points b;//直線から距離d未満の頂点を入れていく
	for (int i = 0; i < n; i++) {
		if (add(fabs(add(a[i].x, -x)), -d) >= 0.0)continue;

		//bに入っている頂点を、末尾からy座標の差がd以上になるまで見ていく
		for (int j = 0; j < (int)b.size(); j++) {
			Point dd;
			dd.x = add(a[i].x, -b[b.size() - j - 1].x);
			dd.y = add(a[i].y, -b[b.size() - j - 1].y);
			if (add(dd.y, -d) >= 0.0)break;
			d = min(d, abs(dd));
		}
		b.emplace_back(a[i]);
	}
	return d;
}

//多角形の面積
double area(Polygon p) {
	int n = p.size();
	double sum = 0.0;
	for (int i = 0; i < n; i++) {
		sum = add(sum,0.5*p[i].det(p[(i + 1) % n]));
	}
	return sum < 0.0 ? -sum : sum;
}

//凸性判定
bool is_convex(Polygon p) {
	for (int i = 0; i < (int)p.size(); i++) {
		if (ccw(p[(i - 1 + p.size()) % p.size()], p[i], p[(i + 1) % p.size()]) == -1)return false;
	}
	return true;
}

//切断
Polygon convex_cut(Polygon p, Line l) {
	Polygon ret;
	for (int i = 0; i < (int)p.size(); i++) {
		Point cur = p[i], nxt = p[(i + 1) % p.size()];
		if (ccw(l.p1, l.p2, cur) != -1)ret.emplace_back(cur);
		if (ccw(l.p1, l.p2, cur)*ccw(l.p1, l.p2, nxt) < 0) {
			Segment seg;
			seg.p1 = cur;
			seg.p2 = nxt;
			ret.emplace_back(getCrossPoint(seg, l));
		}
	}
	return ret;
}

//端点の種類
# define BOTTOM 0
# define LEFT 1
# define RIGHT 2
# define TOP 3

class EndPoint {
public:
	Point p;
	int seg, st;//入力線分のID,端点の種類
	EndPoint() {}
	EndPoint(Point p, int seg, int st) :p(p), seg(seg), st(st) {}

	bool operator <(const EndPoint &ep)const {
		//y座標が小さい順に整列
		if (p.y == ep.p.y) {
			return st < ep.st;//yが同一の場合は、下端点、左端点、右端点、上端点の順に調べる
		}
		else {
			return p.y < ep.p.y;
		}
	}
};

EndPoint EP[202020];//端点のリスト

//線分交差問題（マンハッタン幾何）

int ManhattanIntersection(vector<Segment> s) {
	int n = s.size();
	for (int i = 0, k = 0; i < n; i++) {
		//端点p1,p2が左下を基準に並ぶように調整
		if (s[i].p1.y == s[i].p2.y) {
			if(s[i].p1.x>s[i].p2.x)swap(s[i].p1, s[i].p2);
		}
		else if (s[i].p1.y > s[i].p2.y)swap(s[i].p1, s[i].p2);

		if (s[i].p1.y == s[i].p2.y) {//水平線分を端点リストに追加
			EP[k++] = EndPoint(s[i].p1, i, LEFT);
			EP[k++] = EndPoint(s[i].p2, i, RIGHT);
		}
		else {//垂直線分を端点リストに追加
			EP[k++] = EndPoint(s[i].p1, i, BOTTOM);
			EP[k++] = EndPoint(s[i].p2, i, TOP);
		}
	}
	sort(EP, EP + 2 * n);//端点のy座標に関して昇順に整列

	set<LL> bt;//二分探索木
	bt.insert(1010101010);
	int cnt = 0;

	for (int i = 0; i < 2 * n; i++) {
		if (EP[i].st == TOP) {
			bt.erase(EP[i].p.x);//上端点を削除
		}
		else if (EP[i].st == BOTTOM) {
			bt.insert(EP[i].p.x);
		}
		else if (EP[i].st == LEFT) {
			set<LL>::iterator b = bt.lower_bound(s[EP[i].seg].p1.x);
			set<LL>::iterator e = bt.upper_bound(s[EP[i].seg].p2.x);
			cnt += distance(b, e);//bとeの距離（点の数）を加算
		}
	}
	return cnt;
}
