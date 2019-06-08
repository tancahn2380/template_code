#include "bits/stdc++.h"
template<class T>constexpr T INF() { return ::std::numeric_limits<T>::max(); }
using namespace std;

struct UnionFind {
	vector<int>Par;
	UnionFind(int n) {
		Par.resize(n);
		for (int i = 0; i < n; i++) {
			Par[i] = i;
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
		Par[x] = y;
	}

	bool same(int x, int y) {
		return find(x) == find(y);
	}
};

//skew heapに遅延伝播と対応する辺のidを追加したもの
struct Heap {
	Heap *l, *r;
	int add, v, id;
	Heap() {}
	Heap(int v, int id) :l(NULL), r(NULL), add(0), v(v), id(id) {}
};

void lazy(Heap *a) {
	if (a->l)a->l->add += a->add;
	if (a->r)a->r->add += a->add;
	a->v += a->add;
	a->add = 0;
}

Heap *meld(Heap *a, Heap *b) {
	if (a == NULL)return b;
	if (b == NULL)return a;
	if (a->v + a->add > b->v + b->add)swap(a, b);
	lazy(a);
	a->r = meld(a->r, b);
	swap(a->l, a->r);
	return a;
}

Heap *pop(Heap *a) {
	lazy(a);
	return meld(a->l, a->r);
}

Heap pool[10101010];
int it;//poolをどこまで使ったか

struct edge {
	int from, to, cost;
	edge(int from, int to, int cost) :from(from), to(to), cost(cost) {}
};

int n, m, R;

vector<edge> edges;

Heap *come[101010];//圧縮されたグラフ上で、その点に入ってくる辺をコストの小さい順に管理するヒープ
int used[101010];//  0:未処理,1:処理中,2:完成
int from_cost[101010];//作っている木においてその点に入ってくる辺の圧縮されたグラフ上のコスト
int from[101010];//作っている木においてその点に入ってくる辺の圧縮されたグラフ上のfrom

int Minimum_CostArborescence(int r) {//rを根とする最小全域有向木のコストの計算
	//初期化
	UnionFind uf(n);
	it = 0;
	for (int i = 0; i < n; i++) {
		used[i] = 0;
		come[i] = NULL;
	}
	used[r] = 2;//根だけは最初から完成している

	//最初に各点に入ってくる辺をヒープに追加
	for (int i = 0; i < edges.size();i++) {
		edge &e = edges[i];
		pool[it] = Heap(e.cost, i);
		come[e.to] = meld(come[e.to], &pool[it++]);
	}
	int res = 0;

	for (int start = 0; start < n; start++) {
		if (used[start] != 0)continue;
		int cur = start;
		vector<int> processing;

		while (used[cur] != 2) {//パスを伸ばしていく
			used[cur] = 1;//現在の頂点を処理中にする
			processing.emplace_back(cur);

			if (!come[cur])return INF<int>();//入ってくる辺が無かったら全域有向木は成立しない

			from[cur] = uf.find(edges[come[cur]->id].from);//今の頂点に入ってくる辺のうち、一番コストが小さい辺を使う。その辺のfrom
			from_cost[cur] = come[cur]->v + come[cur]->add;//その辺のcost
			come[cur] = pop(come[cur]);//用済みなのでヒープから取り除く
			if (from[cur] == cur)continue;//自己ループだったらやり直し

			res += from_cost[cur];//辺が確定したので、そのコストを足す

			if (used[from[cur]] == 1) {//サイクルができた時
				int p = cur;
				do {//サイクルをまわる（現在の頂点はp）
					if (come[p])come[p]->add -= from_cost[p];//その頂点に入ってくるコストをサイクルの前の辺のコストの分だけへらす
					if (p != cur) {
						uf.unite(p, cur);//サイクルの頂点を圧縮
						come[cur] = meld(come[cur], come[p]);//ヒープもマージ
					}
					p = uf.find(from[p]);//一つ前の頂点、パスを伸ばしていく途中で圧縮されているかもしれないのでfindする必要がある
				} while (p != cur);//次の頂点は、圧縮した頂点から始める。union-findでcurに圧縮されているのでcurを変更する必要はない
			}
			else {//サイクルができなかった場合
				cur = from[cur];//そのまま次の頂点に移る
			}
		}
		//伸びてきたパスが根につながった

		for (int v : processing) {
			used[v] = 2;//漬かった頂点を完成させた
		}
	}
	return res;
}

int main() {
	cin >> n >> m >> R;
	for(int i = 0; i < m;i++) {
		int s, t, c;
		cin >> s >> t >> c;
		edges.emplace_back(s, t, c);
	}
	cout << Minimum_CostArborescence(R) << endl;
}