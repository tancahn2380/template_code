#include "bits/stdc++.h"
using namespace std;


//オイラーツアー
//木を根からDFSするときに通過する頂点を一直線に並べたもの
//Begin[i],End[i]はiを根とした時の部分木のオイラーツアーのindexを表す

struct Euler_tour {
private:
	int n;
	vector<vector<int>> g;
	vector<int>euler_tour;
	vector<int>Begin, End;
	int k, root;
public:

	void calc(int v, int p) {
		Begin[v] = k;
		euler_tour.emplace_back(v);
		k++;
		for (int i = 0; i < g[v].size(); i++) {
			if (g[v][i] != p) {
				calc(g[v][i], v);
				euler_tour.emplace_back(v);
				k++;
			}
		}
		End[v] = k;
	}

	Euler_tour(int N, vector<int>*G, int Root) {
		n = N;
		g.resize(N);
		Begin.resize(2 * N);
		End.resize(2 * N);
		k = 0;
		root = Root;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < G[i].size(); j++) {
				g[i].emplace_back(G[i][j]);
			}
		}

		calc(root, -1);
	}

	vector<int> geteuler() {
		return euler_tour;
	}
	int beg(int v) {
		return Begin[v];
	}
	int end(int v) {
		return End[v];
	}
};