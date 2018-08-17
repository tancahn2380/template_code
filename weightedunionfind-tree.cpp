#include "bits/stdc++.h"
using LL = long long;

struct Weighted_Union_Find_Tree {
	vector<int>Par, Rank,Diff_Weight;
	Weighted_Union_Find_Tree(int n) {
		Par.resize(n);
		Rank.resize(n);
		Diff_Weight.resize(n);
		for (int i = 0; i < n; i++) {
			Par[i] = i;
			Rank[i] = 0;
		}
	}

	int find(int x) {
		if (Par[x] == x) {
			return x;
		}
		else {
			int r = find(Par[x]);
			Diff_Weight[x] += Diff_Weight[Par[x]];//累積和をとる
			return Par[x] = r;
		}
	}

	bool same(int x, int y) {
		return find(x) == find(y);
	}

	int weight(int x) {
		find(x);//経路圧縮
		return Diff_Weight[x];
	}

	int diff(int x, int y) {
		return weight(y) - weight(x);
	}

	// weight(y) - weight(x) = w となるように merge する
	bool merge(int x, int y, int w) {
		// x と y それぞれについて、 root との重み差分を補正
		w += weight(x); w -= weight(y);

		// x と y の root へ (x と y が既につながっていたら false を返すようにした)
		x = find(x); y = find(y);
		if (x == y) return false;

		// Rank[x] >= Rank[y] となるように x と y を swap (それに合わせて w も符号反転します)
		if (Rank[x] < Rank[y]) swap(x, y), w = -w;

		// y (のroot) を x (のroot) の下にくっつける 
		if (Rank[x] == Rank[y]) ++Rank[x];
		Par[y] = x;

		// x が y の親になるので、x と y の差分を diff_weight[y] に記録
		Diff_Weight[y] = w;

		return true;
	}
};

int main() {
	int n, q;
	cin >> n >> q;
	Weighted_Union_Find_Tree uf(n);
	REP(i, q){
		int num;
		cin >> num;
		if (num == 0) {
			int x, y, z;
			cin >> x >> y >> z;
			uf.merge(x, y, z);
		}
		else {
			int x, y;
			cin >> x >> y;
			if (uf.same(x, y)) {
				cout << uf.diff(x, y) << endl;
			}
			else {
				cout << "?" << endl;
			}
		}
	}
}