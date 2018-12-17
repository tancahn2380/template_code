# include "bits/stdc++.h"
using namespace std;
using LL = long long;
template<class T>constexpr T INF() {return ::std::numeric_limits<T>::max();}

//01BFS
//辺のコストが0,1だけの時に使えるよ

const int MAX_V = 100000;
struct edge { int to, cost; };
int k;
vector<edge> G[MAX_V];
LL d[MAX_V];
void bfs01(int s) {
	deque<pair<int, int>> que;
	fill(d, d + k, INF<LL>());
	d[s] = 0;
	que.push_back(make_pair(0, s));
	while (!que.empty()) {
		pair<int, int> p = que.front(); que.pop_front();
		int v = p.second;
		if (d[v] < p.first)continue;
		for (int i = 0; i < (int)G[v].size(); i++) {
			edge e = G[v][i];
			if (d[e.to] > d[v] + e.cost) {
				d[e.to] = d[v] + e.cost;
				if (e.cost == 0)que.push_front(make_pair(d[e.to], e.to));
				else que.push_back(make_pair(d[e.to], e.to));
			}
		}
	}
}
