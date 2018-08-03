# include "bits/stdc++.h"
using namespace std;
using LL = long long;
template<class T>constexpr T INF() {return ::std::numeric_limits<T>::max();}


//Bellman-Ford
//負のコストがある最短経路を求める
//負閉路があったらfalseを返す
//V,Eを定義しているので初期化に注意

struct edge { LL from, to, cost; };
edge es[100000];

LL d[100000];
int V, E;
bool shortest_path(int s, int t) { // t: destination
	for (int i = 0; i <= V + 1; i++) d[i] = INF<LL>();
	d[s] = 0;
	for (int i = 0; i < 2 * V; i++) {
		for (int j = 0; j < E; j++) {
			edge e = es[j];
			if (d[e.from] != INF<LL>() && d[e.to]>d[e.from] + e.cost) {
				d[e.to] = d[e.from] + e.cost;

				if (i >= V - 1 && e.to == t) return true;
			}
		}
	}
	return false;
}
