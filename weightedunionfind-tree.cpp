#include "bits/stdc++.h"
using LL = long long;


//https://beta.atcoder.jp/contests/arc090/tasks/arc090_b
template <typename T>
struct WeightedUnionFind {
	LL n;
	T d;
	vector<LL> r, p;
	vector<T> ws;
	WeightedUnionFind() {}
	WeightedUnionFind(LL sz, T d_) :
		n(sz), d(d_), r(n, 1), p(n), ws(n, d) {
		iota(p.begin(), p.end(), 0);
	}
	LL find(LL x) {
		if (x == p[x]) {
			return x;
		}
		else {
			LL t = find(p[x]);
			ws[x] += ws[p[x]];
			return p[x] = t;
		}
	}
	T weight(LL x) {
		find(x);
		return ws[x];
	}
	bool same(LL x, LL y) {
		return find(x) == find(y);
	}
	void unite(LL x, LL y, T w) {
		w += weight(x);
		w -= weight(y);
		x = find(x); y = find(y);
		if (x == y) return;
		if (r[x]<r[y]) swap(x, y), w = -w;
		r[x] += r[y];
		p[y] = x;
		ws[y] = w;
	}
	T diff(LL x, LL y) {
		return weight(y) - weight(x);
	}
};

int main() {
	LL n, m;
	cin >> n >> m;
	WeightedUnionFind<LL> wuf(n + 1, 0);
	for (LL i = 0; i<m; i++) {
		LL l, r, d;
		cin >> l >> r >> d;
		l--; r--;
		if (wuf.same(l, r)) {
			if (wuf.diff(l, r) != d) {
				cout << "No" << endl;
				return 0;
			}
		}
		else {
			wuf.unite(l, r, d);
		}
	}
	cout << "Yes" << endl;
}