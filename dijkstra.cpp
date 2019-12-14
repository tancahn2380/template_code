# include "bits/stdc++.h"
using namespace std;
using LL = long long;
template<class T>constexpr T INF() {return ::std::numeric_limits<T>::max();}
template<class T>constexpr T HINF() { return INF<T>() / 2; }

//dijkstra
//startからの最小コストをdに入れる
// V,E,startの定義に注意する

//型に注意しろよ

struct edge { LL to, cost; };
int start;
LL d[100100];
vector<edge> vec[100100];
 
void dijkstra() {
	for (int i = 0; i < 100100; i++)d[i] = HINF<LL>();
	priority_queue<pair<LL, int>, std::vector<pair<LL, int>>, std::greater<pair<LL, int>>> pq;
	d[start] = 0;
	pq.push(make_pair(d[start], start));//cost,to
	while (!pq.empty()) {
		pair<LL, int> p = pq.top();
		pq.pop();
		int i = p.second;
		if (d[i] < p.first)continue;
		for (int k = 0; k < (int)vec[i].size(); k++) {
			edge e = vec[i][k];
			if (d[e.to] <= d[i] + e.cost)continue;
			d[e.to] = d[i] + e.cost;
			pq.push(make_pair(d[e.to], e.to));
		}
	}
}

