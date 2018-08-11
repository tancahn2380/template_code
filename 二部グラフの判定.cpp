#include "bits/stdc++.h"
using namespace std;

//Vの定義に注意

const int MAX_V = 100100;

vector<int> G[MAX_V];
LL V;
int color[MAX_V];
//頂点を1と-1で塗っていく
bool dfs(int v, int c) {
	color[v] = c;//vをcで塗る
	for (int i = 0; i < G[v].size(); i++) {
		//隣接している頂点が同じ色ならfalse
		if (color[G[v][i]] == c)return false;
		//隣接している頂点がまだ塗られてないなら-cで塗る
		if (color[G[v][i]] == 0 && !dfs(G[v][i], -c))return false;
	}
	//全ての頂点が塗れたらtrue
	return true;
}

int main() {
	LL m;
	cin >> V >> m;
	int a, b;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		a--, b--;
		G[a].emplace_back(b);
		G[b].emplace_back(a);
	}
	for (int i = 0; i < V; i++) {
		if (color[i] == 0) {
			//まだ頂点が塗られてなければ1で塗る
			if (!dfs(i, 1)) {
				cout << "NO" << endl;
				return 0;
			}
		}
	}
	cout << "YES" << endl;
}