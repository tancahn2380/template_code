#include "bits/stdc++.h"
using namespace std;

const int n = 4;
const int LIMIT = 45;

int MDT[n*n][n*n];

struct Puzzle { int f[n*n], space, MD; };

Puzzle state;
int limit;//深さの制限
int path[LIMIT];

int getALLMD(Puzzle pz) {
	int sum = 0;
	for (int i = 0; i < n*n; i++) {
		if (pz.f[i] == n*n) continue;
		sum += MDT[i][pz.f[i] - 1];
	}
	return sum;
}

bool issolved() {
	for (int i = 0; i < n*n; i++) {
		if (state.f[i] != i + 1)return false;
	}
	return true;
}

bool dfs(int depth, int prev) {
	if (state.MD == 0)return true;
	//現在の深さにヒューリスティックを足して制限を超えたら枝を刈る
	if (depth + state.MD > limit)return false;


	int sx = state.space / n;
	int sy = state.space % n;
	Puzzle tmp;

	for (int r = 0; r < 4; r++) {
		if (abs(r - prev) == 2)continue;
		int tx = sx + dx[r];
		int ty = sy + dy[r];
		if (tx < 0 || ty < 0 || tx >= n || ty >= n)continue;
		tmp = state;
		//マンハッタン距離の差分を計算しつつ、ピースをスワップ
		state.MD -= MDT[tx*n + ty][state.f[tx*n + ty] - 1];
		state.MD += MDT[sx*n + sy][state.f[tx*n + ty] - 1];
		swap(state.f[tx*n + ty],state.f[sx*n+sy]);
		state.space = tx*n + ty;
		if (dfs(depth + 1, r)) {
			path[depth] = r;
			return true;
		}
		state = tmp;
	}
	return false;
}

//反復深化
string iterative_deepening(Puzzle in) {
	in.MD = getALLMD(in);//初期状態のマンハッタン距離
	for (limit = in.MD; limit <= LIMIT; limit++) {
		state = in;
		if (dfs(0, -100)) {
			string ans = "";
			for (int i = 0; i < limit; i++)ans += dir[path[i]];
			return ans;
		}
	}
	return "unsolvable";
}

int main() {
	INIT;
	for (int i = 0; i < n*n; i++) {
		for (int j = 0; j < n*n; j++) {
			MDT[i][j] = abs(i / n - j / n) + abs(i%n - j%n);
		}
	}
	Puzzle in;
	for (int i = 0; i < n*n; i++) {
		cin >> in.f[i];
		if (in.f[i] == 0) {
			in.f[i] = n*n;
			in.space = i;
		}
	}
	string ans = iterative_deepening(in);
	cout << ans.size() << endl;
}