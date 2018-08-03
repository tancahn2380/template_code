# include "bits/stdc++.h"
using namespace std;
using LL = long long;
template<class T>constexpr T INF() {return ::std::numeric_limits<T>::max();}
template<class T>constexpr T HINF() { return INF<T>() / 2; }
const int dx[4] = { 0,1,0,-1 }, dy[4] = { 1,0,-1,0 };


//bfs(グリッド上)
//グリッド上のbfsを行う
//sx,sy,gx,gy,obstacleの入力に注意

string maze[1001];
int h, w;
int sx, sy, gx, gy;
char obstacle;

int d[1001][1001];
int bfs() {
	queue<pair<int, int>> que;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			d[i][j] = HINF<int>();
		}
	}
	que.push(pair<int, int>(sx, sy));
	d[sy][sx] = 0;
	while (que.size()) {
		pair<int, int> p = que.front();
		que.pop();
		for (int i = 0; i < 4; i++) {
			int nx = p.first + dx[i], ny = p.second + dy[i];
			if (0 <= nx&&nx < w && 0 <= ny&&ny < h &&maze[ny][nx] != obstacle && d[ny][nx] == HINF<int>()) {
				que.push(pair<int, int>(nx, ny));
				d[ny][nx] = d[p.second][p.first] + 1;
			}
		}
	}
	return d[gy][gx];
}