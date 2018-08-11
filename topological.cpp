#include "bits/stdc++/h"
using namespace std;

//https://www.slideshare.net/hcpc_hokudai/topological-sort-69581002
//コード例は24ページ
//verified
//http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3064543#1

vector<int> tsort_kahn(const vector<vector<int>>& g) {
	const int V = g.size();
	vector<int> indeg(V, 0);
	stack<int> S;

	for (auto& u_out_edges : g) {
		for (auto& v : u_out_edges) {
			indeg[v]++;
		}
	}

	for (int i = 0; i < V; i++) {
		if (indeg[i] == 0) {
			S.push(i);
		}
	}

	vector <int>ans;
	while (S.size() > 0) {
		int u = S.top(); S.pop();
		ans.emplace_back(u);
		for (auto& v : g[u]) {
			indeg[v]--;
			if (indeg[v] == 0)S.push(v);
		}
	}
	return ans;
}

int main() {
	int v, e;
	cin >> v >> e;
	vector<vector<int>>vv(v);
	REP(i, e) {
		int s, t;
		cin >> s >> t;
		vv[s].emplace_back(t);
	}
	vector<int> ans = tsort_kahn(vv);
	REP(i, v) {
		cout << ans[i] << endl;
	}
}
//辞書順最小(verified)
vector<int> tsort_kahn_lexicographically(const vector<vector<int>>& g) {
	const int V = g.size();
	vector<int> indeg(V, 0);
	priority_queue<int,vector<int>,greater<int>> S;

	for (auto& u_out_edges : g) {
		for (auto& v : u_out_edges) {
			indeg[v]++;
		}
	}

	for (int i = 0; i < V; i++) {
		if (indeg[i] == 0) {
			S.push(i);
		}
	}

	vector <int>ans;
	while (S.size() > 0) {
		int u = S.top(); S.pop();
		ans.emplace_back(u);
		for (auto& v : g[u]) {
			indeg[v]--;
			if (indeg[v] == 0)S.push(v);
		}
	}
	return ans;
}
