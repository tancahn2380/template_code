#include "bits/stdc++.h"
using namespace std;

double EPS = 1e-10;

//誤差を考慮して足し算を行う
double add(double a, double b) {
	if (abs(a + b) < EPS*(abs(a) + abs(b)))return 0;
	return a + b;
}

//二次元ベクトル構造体

struct P {
	double x, y;
	P() {}
	P(double x, double y) :x(x), y(y) {
	}
	P operator + (P p) {
		return P(add(x, p.x), add(y, p.y));
	}
	P operator - (P p) {
		return P(add(x, -p.x), add(y, -p.y));
	}
	P operator * (double d) {
		return P(x*d, y*d);
	}
	//内積
	double dot(P p) {
		return add(x*p.x, y*p.y);
	}
	//外積
	double det(P p) {
		return add(x*p.y, -y*p.x);
	}
};

//距離の二乗
double dist(P p, P q) {
	return (p - q).dot(p - q);
}

//辞書順で比較
bool cmp_x(const P& p, const P& q) {
	if (p.x != q.x)return  p.x < q.x;
	return p.y < q.y;
}

//凸包を求める
vector<P> convex_hull(P* ps, int n) {
	sort(ps, ps + n, cmp_x);
	int k = 0;//凸法の頂点数
	vector<P> qs(n * 2);//構築中の凸包

						//下限凸包の作成
	for (int i = 0; i < n; i++) {
		while (k > 1 && (qs[k - 1] - qs[k - 2]).det(ps[i] - qs[k - 1]) <= 0)k--;
		qs[k++] = ps[i];
	}

	//上限凸包の作成
	for (int i = n - 2, t = k; i >= 0; i--) {
		while (k > t && (qs[k - 1] - qs[k - 2]).det(ps[i] - qs[k - 1]) <= 0)k--;
		qs[k++] = ps[i];
	}
	qs.resize(k - 1);
	return qs;
}