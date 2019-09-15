#include "bits/stdc++.h"
using namespace std;
struct SCC{
private:
    int v;
    vector<vector<int>> G;  //グラフの隣接リスト表現
    vector<vector<int>> rG; //辺の向きを逆にしたグラフ
    vector<int> vs;         //帰りがけ順の並び
    vector<bool> used;      //すでに調べたか
    void dfs(int cur){
        used[cur] = true;
        for (int i = 0; i < (int)G[cur].size(); i++) {
            if (!used[G[cur][i]])dfs(G[cur][i]);
        }
        vs.emplace_back(cur);
    }
    void rdfs(int cur, int k) {
        used[cur] = true;
        cmp[cur] = k;
        for (int i = 0; i < (int)rG[cur].size(); i++) {
            if (!used[rG[cur][i]])rdfs(rG[cur][i], k);
        }
    }
public:
    vector<int> cmp;        //属する競連結成分のトポロジカル順序
    SCC(){}
    SCC(int V){
        v = V;
        G.resize(v);
        rG.resize(v);
        used.resize(v, false);
        cmp.resize(v, 0);
    }
    void init(int V){
        v = V;
        G.resize(v);
        rG.resize(v);
        used.resize(v, false);
        cmp.resize(v, 0);
    }

    void add_edge(int f, int t){
        G[f].emplace_back(t);
        rG[t].emplace_back(f);
    }

    //分解後のグラフのサイズを返す
    int scc() {
        vs.clear();
        for (int i = 0; i < v; i++) {
            if (!used[i])dfs(i);
        }
        used.assign(v, 0);
        int k = 0;
        for (int i = vs.size() - 1; i >= 0; i--) {
            if (!used[vs[i]])rdfs(vs[i], k++);
        }
        return k;
    }
};