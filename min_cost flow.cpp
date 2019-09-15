# include "bits/stdc++.h"
using namespace std;
template<class T>constexpr T INF() { return ::std::numeric_limits<T>::max(); }
//最小費用龍
typedef pair<int, int> P;//firstは最短距離、secondは頂点の番号
//revは逆辺
struct edge { int to, cap, cost, rev; };
int V; //頂点数
vector<edge> G[101010];
int h[101010];//ポテンシャル
int dist[101010];//最短距離
int prevv[101010], preve[101010];//直前の頂点と辺
 
void add_edge(int from, int to, int cap, int cost) {
    G[from].emplace_back(edge{ to,cap,cost,(int)G[to].size() });
    G[to].emplace_back(edge{ from,0,-cost,(int)G[from].size() - 1 });
}
 
//最小費用流、流せない場合は-1
 
int min_cost_flow(int s, int t, int f) {
    int res = 0;
    REP(i,V)h[i]=0;//初期化
    while (f > 0) {
        //ダイクストラ法を用いてhを更新
        priority_queue<P, vector<P>, greater<P>> que;
        REP(i, V)dist[i] = INF<int>();
        dist[s] = 0;
        que.push(P(0, s));
        while (que.size()) {
            P p = que.top();
            que.pop();
            int v = p.second;
            if (dist[v] < p.first)continue;
            for (int i = 0; i < G[v].size(); i++) {
                edge &e = G[v][i];
                if (e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
                    dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
                    prevv[e.to] = v;
                    preve[e.to] = i;
                    que.push(P(dist[e.to], e.to));
                }
            }
        }
        if (dist[t] == INF<int>()) {
            return -1;
            //これ以上流せない
        }
        for (int v = 0; v < V; v++)h[v] += dist[v];
 
        //s-t間最短路に沿ってめいっぱい流す
        int d = f;
        for (int v = t; v != s; v = prevv[v]) {
            d = min(d, G[prevv[v]][preve[v]].cap);
        }
        f -= d;
        res += d*h[t];
        for (int v = t; v != s; v = prevv[v]) {
            edge &e = G[prevv[v]][preve[v]];
            e.cap -= d;
            G[v][e.rev].cap += d;
        }
    }
    return res;
}