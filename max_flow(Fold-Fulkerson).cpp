#include "bits/stdc++.h"
using namespace std;
using LL = long long;

//最大流(Fold-Fulkerson)
//Vの範囲に注意する

constexpr int MAX_V = 1000;

//行先、容量、逆辺
struct edge { LL to, cap, rev; };

vector<edge> G[MAX_V];
bool used[MAX_V];

//fromからtoへ向かう容量capの辺をグラフに追加する
void add_edge(int from, int to, LL cap) {
	G[from].emplace_back(edge{ to, cap, (LL)G[to].size() });
	G[to].emplace_back(edge{ from,0,(LL)G[from].size() - 1 });
}

//増加パスをDFSで探す
LL dfs(LL v, LL t, LL f) {
	if (v == t)return f;
	used[v] = true;
	for (int i = 0; i < G[v].size(); i++) {
		edge &e = G[v][i];
		if (!used[e.to] && e.cap > 0) {
			LL d = dfs(e.to, t, min(f, e.cap));
			if (d > 0) {
				e.cap -= d;
				G[e.to][e.rev].cap += d;
				return d;
			}
		}
	}
	return 0;
}

//sからtへの最大流を求める
LL max_flow(int s, int t) {
	LL flow = 0;
	while (true) {
		for (int i = 0; i < MAX_V; i++)used[i] = false;
		LL f = dfs(s, t, INF);
		if (f == 0)return flow;
		flow += f;
	}
}