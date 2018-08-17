# include "bits/stdc++.h"
using namespace std;
using LL = long long;
template<class T>constexpr T INF() { return ::std::numeric_limits<T>::max(); }

struct LazySegmentTree {
private:
	int n;
	vector<LL> node, lazy;
public:
	LazySegmentTree(int sz) {
		n = 1; while (n < sz) n *= 2;
		node.resize(2 * n - 1,INF<int>());
		lazy.resize(2 * n - 1, -1);
	}

	void eval(int k, int l, int r) {
		if (lazy[k] != -1) {
			node[k] = lazy[k];;
			if (k < n - 1) {
				lazy[k * 2 + 1] = lazy[k * 2 + 2] = lazy[k];
			}
			lazy[k] = -1;
		}
	}

	void add(int a, int b, LL x, int k = 0, int l = 0, int r = -1) {
		if (r < 0) r = n;
		eval(k, l, r);
		if (b <= l || r <= a) return;
		if (a <= l && r <= b) {
			lazy[k] = x;
			eval(k, l, r);
		}
		else {
			add(a, b, x, 2 * k + 1, l, (l + r) / 2);
			add(a, b, x, 2 * k + 2, (l + r) / 2, r);
			node[k] = min( node[2 * k + 1] , node[2 * k + 2]);
		}
	}

	LL getmin(int a, int b, int k = 0, int l = 0, int r = -1) {
		if (r < 0) r = n;
		eval(k, l, r);
		if (b <= l || r <= a) return INF<int>();
		if (a <= l && r <= b) return node[k];
		LL vl = getmin(a, b, 2 * k + 1, l, (l + r) / 2);
		LL vr = getmin(a, b, 2 * k + 2, (l + r) / 2, r);
		return min(vl ,vr);
	}
};

int main() {
	int n, q;
	cin >> n >> q;
	LazySegmentTree seg(n);
	REP(i, q) {
		int k, s, t, x;
		cin >> k;
		if (k == 0) {
			cin >> s >> t >> x;
			seg.add(s, t + 1, x);
		}
		else {
			cin >> s;
			cout << seg.getmin(s, s + 1) << endl;
		}
	}
}