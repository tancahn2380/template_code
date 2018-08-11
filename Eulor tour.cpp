#include "bits/stdc++.h"
using namespace std;


//オイラーツアー
//木を根からDFSするときに通過する頂点を一直線に並べたもの
//Begin[i],End[i]はiを根とした時の部分木のオイラーツアーのindexを表す

const int MAX_N = 100100
vector<int> g[MAX_N];
vector<int> euler_tour;
int Begin[2 * MAX_N], End[2 * MAX_N];
int k = 0, root = 0;
void eulor(int v, int p){
	Begin[v] = k;
	euler_tour.emplace_back(v);
	k++;
	for (int i = 0; i<g[v].size(); i++)
	{
		if (g[v][i] != p)
		{
			eulor(g[v][i], v);
			euler_tour.emplace_back(v);
			k++;
		}
	}
	End[v] = k;
}

int main(){
	eulor(root, -1);
}
