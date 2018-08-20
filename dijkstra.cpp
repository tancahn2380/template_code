# include "bits/stdc++.h"
using namespace std;
using LL = long long;
template<class T>constexpr T INF() {return ::std::numeric_limits<T>::max();}
template<class T>constexpr T HINF() { return INF<T>() / 2; }
typedef pair<LL, LL> pii;

//dijkstra
//startからの最小コストをdに入れる
// V,E,startの定義に注意する

int V, E;
struct edge { LL to, cost; };
int start;
LL d[100100]; //距離
vector<edge> vec[100100];

void dijkstra() {
	for (int i = 0; i < 100100; i++)d[i] = HINF<LL>();
	priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
	d[start] = 0;
	pq.push(make_pair(d[start], start));//cost,to
	while (!pq.empty()) {
		pii p = pq.top();
		pq.pop();
		int i = p.second;
		if (d[i] < p.first)continue;
		for (int k = 0; k < vec[i].size(); k++) {
			edge e = vec[i][k];
			if (d[e.to] <= d[i] + e.cost)continue;
			d[e.to] = d[i] + e.cost;
			pq.push(make_pair(d[e.to], e.to));
		}
	}
}

int main() {
	cin >> V >> E;
	int a, b, c;
	for (int i = 0; i < E; i++) {
		cin >> a >> b >> c;
		vec[a].push_back(edge{ b,c });
		vec[b].push_back(edge{ a,c });
	}
	dijkstra();
}