# include "bits/stdc++.h"
using namespace std;
using LL = long long;
template<class T>constexpr T INF() {return ::std::numeric_limits<T>::max();}


//bfs(グラフ上)
//グラフ上のbfsを行う
//頂点startからの距離をdisに入れる
//条件式が必要な場合は条件式を書く
//MAX_Vの範囲に注意する

constexpr int MAX_V = 100001;
int V, E;
vector<int> G[MAX_V];

int dis[MAX_V];

void bfs(int start) {
	queue<int>que;
	for (int i = 0; i < MAX_V; i++)dis[i] = INF<int>();

	que.push(start);
	dis[start] = 0;

	while (que.size()) {
		int p = que.front();
		que.pop();

		for (int i = 0; i < G[p].size(); i++) {
			if (/*条件式&&*/dis[G[p][i]] == INF<int>()) {
				que.push(G[p][i]);
				dis[G[p][i]] = dis[p] + 1;
			}
		}
	}
}

int main() {
	cin >> V >> E;
	int a, b;
	for (int i = 0; i < E; i++) {
		cin >> a >> b;
		G[a].emplace_back(b);
		G[b].emplace_back(a);
	}
	bfs(0);
}