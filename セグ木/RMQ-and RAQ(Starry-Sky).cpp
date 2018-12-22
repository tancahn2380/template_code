# include "bits/stdc++.h"
using namespace std;
template<class T>constexpr T INF() { return ::std::numeric_limits<T>::max(); }
int N, Q;

struct SegmentTree {
private:
	int n;
	vector<int> segMin, segAdd;
public:
	SegmentTree(vector<int> v) {
		int sz = v.size();
		n = 1; while (n < sz) n *= 2;
		segMin.resize(2 * n - 1, 0);
		segAdd.resize(2 * n - 1, 0);
		for (int i = 0; i<sz; i++) segMin[i + n - 1] = v[i];
		for (int i = n - 2; i >= 0; i--) segMin[i] = min(segMin[2 * i + 1], segMin[2 * i + 2]);
	}

	//区間[a, b)に値xを加算する.
	void add(int a, int b, int x, int k = 0, int l = 0, int r = -1){
		if (r < 0)r = n;

		if (r <= a || b <= l) return; //もし交差しない区間であれば終える.

		if (a <= l && r <= b) { //もし今みている区間[l, r)が[a, b)に完全に内包されていれば
			segAdd[k] += x;  //区間[l, r)にkを加算する.
			return;
		}

		add(a, b, x, k * 2 + 1, l, (l + r) / 2); //子の区間に(必要があれば)xを加算する.
		add(a, b, x, k * 2 + 2, (l + r) / 2, r); //〃

		//親の区間の最小値は, 子の区間の最小値 + 自分に一様に加算されている値 である.一様に加算される値は更新しなくて良い.
		segMin[k] = min(segMin[k * 2 + 1] + segAdd[k * 2 + 1], segMin[k * 2 + 2] + segAdd[k * 2 + 2]);
	}

	int getMin(int a, int b, int k = 0, int l = 0, int r = -1){
		if (r < 0)r = n;

		if (r <= a || b <= l) return (INF<int>());

		if (a <= l && r <= b) return (segMin[k] + segAdd[k]); //完全に内包されていれば,その区間の最小値を返す.

		int left = getMin(a, b, k * 2 + 1, l, (l + r) / 2); //子の区間の最小値を求める.
		int right = getMin(a, b, k * 2 + 2, (l + r) / 2, r); //子の区間の最小値を求める

		return (min(left, right) + segAdd[k]); //親の区間の最小値は, 子の区間の最小値 + 自分に一様に加算されている値 である (大切なので2回書きました!!)

	}
};

int main() {
	cin >> N >> Q;
	SegmentTree seg(vector<int>(N, 0));
	for (int i = 0; i < Q; i++) {
		int k;
		cin >> k;
		if (k == 0) {
			int s, t, x;
			cin >> s >> t >> x;
			seg.add(s, t + 1, x);
		}
		else {
			int s, t;
			cin >> s >> t;
			cout << seg.getMin(s, t + 1) << endl;
		}
	}
}