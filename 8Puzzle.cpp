# include "bits/stdc++.h"

const int n = 3;

struct Puzzle {
	int f[n*n];
	int space;
	string path;

	bool operator < (const Puzzle &p)const {
		for (int i = 0; i < n*n; i++) {
			if (f[i] == p.f[i])continue;
			return f[i] > p.f[i];
		}
		return false;
	};
};

bool istarget(Puzzle p) {
	for (int i = 0; i < n*n; i++) {
		if (p.f[i] != (i + 1))return false;
	}
	return true;
}

string bfs(Puzzle s) {
	queue<Puzzle> q;
	map<Puzzle, bool> V;
	Puzzle u, v;
	s.path = "";
	q.push(s);
	V[s] = true;

	while (!q.empty()) {
		u = q.front();
		q.pop();
		if (istarget(u))return u.path;
		int sx = u.space / n;
		int sy = u.space % n;
		for (int r = 0; r < 4; r++) {
			int tx = sx + dx[r];
			int ty = sy + dy[r];
			if (tx < 0 || ty < 0 || tx >= n || ty >= n)continue;
			v = u;
			swap(v.f[u.space], v.f[tx*n + ty]);
			v.space = tx*n + ty;
			if (!V[v]) {
				V[v] = true;
				v.path += dir[r];
				q.push(v);
			}
		}
	}
	return "unsolvable";
}

int main() {
	Puzzle in;

	for (int i = 0; i < n*n; i++) {
		cin >> in.f[i];
		if (in.f[i] == 0) {
			in.f[i] = n*n;
			in.space = i;
		}
	}
	string ans = bfs(in);
	cout << ans.size() << endl;
}