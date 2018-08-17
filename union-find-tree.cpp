#include "bits/stdc++.h"

using namespace std;

//unionfind
//initを最初に実行しておくこと

int Par[100000];   //親
int Rank[100000];  //木の深さ

//n要素で初期化
void init(int n) {
	for (int i = 0; i < n; i++) {
		Par[i] = i;
		Rank[i] = 0;
	}
}

//木の根を求める
int find(int x) {
	if (Par[x] == x) {
		return x;
	}
	else {
		return Par[x] = find(Par[x]);
	}
}

//xとyの属する集合を併合
void unite(int  x, int y) {
	x = find(x);
	y = find(y);
	if (x == y) return;
	if (Rank[x] < Rank[y]) {
		Par[x] = y;
	}
	else {
		Par[y] = x;
		if (Rank[x] == Rank[y])Rank[x]++;
	}
}

bool same(int x, int y) {
	return find(x) == find(y);
}
/* コピペ用
struct UnionFind {

	int Par[100000];
	int Rank[100000];

	UnionFind(int n) {
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
			return Par[x] = find(Par[x]);
		}
	}

	void unite(int  x, int y) {
		x = find(x);
		y = find(y);
		if (x == y) return;
		if (Rank[x] < Rank[y]) {
			Par[x] = y;
		}
		else {
			Par[y] = x;
			if (Rank[x] == Rank[y])Rank[x]++;
		}
	}

	bool same(int x, int y) {
		return find(x) == find(y);
	}
};

int main() {
	int n;
	cin >> n;
	UnionFind uf(n);
	int q;
	cin >> q;
	REP(i, q) {
		int a, b, c;
		cin >> a >> b >> c;
		if (a == 0)uf.unite(b, c);
		else cout << uf.same(b, c) << endl;
	}
}
*/

//satanic0258
/*
//Union-Find
class UnionFind {
private:
	std::vector<int> parent;
	std::vector<int> height;
	std::vector<int> m_size;

public:
	UnionFind(int size_) : parent(size_), height(size_, 0), m_size(size_, 1) {
		for (int i = 0; i < size_; ++i) parent[i] = i;
	}
	void init(int size_) {
		parent.resize(size_);
		height.resize(size_, 0);
		m_size.resize(size_, 0);
		for (int i = 0; i < size_; ++i) parent[i] = i;
	}
	int find(int x) {
		if (parent[x] == x) return x;
		return parent[x] = find(parent[x]);
	}
	void unite(int x, int y) {
		x = find(x);
		y = find(y);
		if (x == y) return;
		int t = size(x) + size(y);
		m_size[x] = m_size[y] = t;
		if (height[x] < height[y]) parent[x] = y;
		else parent[y] = x;
		if (height[x] == height[y]) ++height[x];
	}
	bool same(int x, int y) {
		return find(x) == find(y);
	}
	int size(int x) {
		if (parent[x] == x) return m_size[x];
		return size(parent[x] = find(parent[x]));
	}
};
*/