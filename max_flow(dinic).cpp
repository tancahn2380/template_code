# include "bits/stdc++.h"
using namespace std;
using LL = long long;
template<class T>constexpr T INF() {return ::std::numeric_limits<T>::max();}

//最大流(dinic)
//dinic法で最大流を求める
//MAX_Vの範囲に注意する

const int MAX_V = 101010;

struct edge { int to; LL cap;int rev; };

vector<edge> G[MAX_V];
int level[MAX_V];
int iter[MAX_V];

void add_edge(int from, int to, LL cap) {
	G[from].emplace_back(edge{ to,cap,(int)G[to].size() });
	G[to].emplace_back(edge{ from,0,(int)G[from].size() - 1 });
}

void bfs(int s) {
	for (int i = 0; i < MAX_V;i++)level[i] = -1;
	queue<int> que;
	level[s] = 0;
	que.push(s);
	while (!que.empty()) {
		int v = que.front();
		que.pop();
		for (int i = 0; i < (int)G[v].size();i++) {
			edge &e = G[v][i];
			if (e.cap > 0 && level[e.to] < 0) {
				level[e.to] = level[v] + 1;
				que.push(e.to);
			}
		}
	}
}

LL dfs(int v, int t, LL f) {
	if (v == t)return f;
	for (int &i = iter[v]; i < (int)G[v].size(); i++) {
		edge &e = G[v][i];
		if (e.cap > 0 && level[v] < level[e.to]) {
			int d = dfs(e.to, t, min(f, e.cap));
			if (d > 0) {
				e.cap -= d;
				G[e.to][e.rev].cap += d;
				return d;
			}
		}
	}
	return 0LL;
}

LL max_flow(int s, int t) {
	int flow = 0;
	for (;;) {
		bfs(s);
		if (level[t] < 0)return flow;
		for (int i = 0; i < MAX_V;i++)iter[i] = 0;
		int f;
		while ((f = dfs(s, t, INF<LL>())) > 0) {
			flow += f;
		}
	}
}


int n, m;
int main() {
	cin >> n >> m;
	for (int i = 0; i < m;i++) {
		int a, b, c;
		cin >> a >> b >> c;
		add_edge(a, b, c);
	}
	cout << max_flow(0, n - 1) << endl;
}