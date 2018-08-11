#include "bits/stdc++.h"
using namespace std;

//Minimum Spanning Tree(最小全域木)
//VとEの定義に注意する

int V;
int E;
struct edge { int from, to, cost; };

typedef pair<int, int> PP;

vector<edge> e;

int Par[100000];
int Rank[100000];

void init(int n) {
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

// ソート時に比較するための関数 
bool comp(const edge& e1,const edge& e2){
	return e1.cost < e2.cost; 
}

int kruskal() {
	init(V);
	sort(e.begin(), e.end(), comp);
	int ans = 0; 
	for (int i = 0; i<E; i++) {
		if (!same(e[i].from, e[i].to)) {
			unite(e[i].from, e[i].to); 
			ans += e[i].cost;
		} 
	}
	return ans;
}

int main() {
	cin >> V >> E;
	int a, b, c;
	for (int i = 0; i < E; i++) {
		cin >> a >> b >> c;
		e.push_back(edge{ a,b,c });
	}
	cout << kruskal() << endl;
}
