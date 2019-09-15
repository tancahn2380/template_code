#include "bits/stdc++.h"
using namespace std;

struct LCA {
private:
	int n;
	vector<vector<int>>g;
	int root;
	vector<int>depth;
	vector<vector<int>>par;
public:

	void dfs(int v, int p, int d) {
		par[v][0] = p;
		depth[v] = d;
		for (int i = 0; i<g[v].size(); i++) {
			if (g[v][i] == p)continue;
			dfs(g[v][i], v, d + 1);
		}
	}

	LCA(int N,vector<int>* G,int Root) {
		n = N;
		g.resize(N);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < G[i].size(); j++) {
				g[i].emplace_back(G[i][j]);
			}
		}
		depth.resize(N);
		par.resize(N);
		for (int i = 0; i < N; i++)par[i].resize(31);
		root = Root;
		dfs(root, -1, 0);
		for (int i = 0; i < 30; i++) {
			for (int j = 0; j < N; j++) {
				if (par[j][i] == -1)par[j][i + 1] = -1;
				else par[j][i + 1] = par[par[j][i]][i];
			}
		}
	}

	int get(int u, int v) {
		if (depth[u] > depth[v])swap(u, v);
		for (int i = 30; i >= 0; i--) {
			if (((depth[v] - depth[u]) >> i) & 1) {
				v = par[v][i];
			}
		}
		if (u == v)return u;

		for (int i = 30; i >= 0; i--) {
			if (par[u][i] != par[v][i]) {
				u = par[u][i];
				v = par[v][i];
			}
		}
		return par[u][0];
	}
};

int n;
vector<int> g[101010];

int main() {
	cin >> n;
	for(int i = 0;i < n;i++) {
		int k;
		cin >> k;
		for(int j = 0;j < k;j++) {
			int c;
			cin >> c;
			g[i].emplace_back(c);
			g[c].emplace_back(i);
		}
	}
	LCA lca(n, g, 0);
	int q;
	cin >> q;
	for(int qqq = 0;qqq < q;qqq++) {
		int u, v;
		cin >> u >> v;
		cout << lca.get(u, v) << endl;
	}
}