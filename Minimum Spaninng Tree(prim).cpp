#include "bits/stdc++.h"
using namespace std;
template<class T>constexpr T INF() { return ::std::numeric_limits<T>::max(); }

//O(V^2)
const int MAX_V = 1010;

int cost[MAX_V][MAX_V];
int mincost[MAX_V];
bool used[MAX_V];
int V;

int prim() {
	for (int i = 0; i < V; i++) {
		mincost[i] = INF<int>();
		used[i] = false;
	}
	mincost[0] = 0;
	int res = 0;

	while (true) {
		int v = -1;
		for (int u = 0; u < V; u++) {
			if (!used[u] && (v == -1 || mincost[u] < mincost[v]))v = u;
		}
		if (v == -1)break;
		used[v] = true;
		res += mincost[v];
		for (int u = 0; u < V; u++) {
			mincost[u] = min(mincost[u], mincost[v]);
		}
	}
	return res;
}