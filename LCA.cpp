#include "bits/stdc++.h"
using namespace std;

//LCA
//木の2頂点の祖先を求める

int N, root;
vector<int> g[101010];
int depth[101010];
int par[101010][30];

//木の深さを求める
void dfs(int v, int p, int d){
	par[v][0] = p;
	depth[v] = d;
	for (int i = 0; i<g[v].size(); i++){
		if (g[v][i] == p)continue;
		dfs(g[v][i], v, d + 1);
	}
}

//par[v][i]:=頂点vから2^i回親をたどった頂点（無かったら-1）
//vの親→par[v][0],vの親の親par[v][1]
//par[v][i+1]=par[par[v][i]]よりpar[~][i]が計算できればpar[~][i+1]も求まる
void fill_table(){
	for (int i = 0; i<19; i++) {
		for (int j = 0; j<N; j++){
			if (par[j][i] == -1)par[j][i + 1] = -1;
			else par[j][i + 1] = par[par[j][i]][i];
		}
	}
}


//頂点u,vのLCAを求める
int lca(int u, int v){

	if (depth[u]>depth[v])swap(u, v);
	//深さをそろえるための処理
	for (int i = 19; i >= 0; i--) {
		if (((depth[v] - depth[u]) >> i) & 1) {
			v = par[v][i];
		}
	}

	if (u == v)return u;
	//ダブリング
	for (int i = 19; i >= 0; i--){
		if (par[u][i] != par[v][i]){
			u = par[u][i];
			v = par[v][i];
		}
	}
	return par[u][0];
}

int main(){
	dfs(root, -1, 0);
	fill_table();
	return 0;
}
