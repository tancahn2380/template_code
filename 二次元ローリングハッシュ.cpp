#include"bits/stdc++.h"

using ULL = unsigned long long;

const ULL B[] = { 999999937ULL,1000000007ULL };

const int MAX_SIZE = 1010;

int h, w, r, c;

char field[MAX_SIZE][MAX_SIZE];//検索対象
char patterns[MAX_SIZE][MAX_SIZE];//検索パターン

ULL Hash[MAX_SIZE][MAX_SIZE], tmp[MAX_SIZE][MAX_SIZE];

//aのP*Qの部分に関するハッシュを計算
void compute_hash(char a[MAX_SIZE][MAX_SIZE], int n, int m) {
	ULL t0 = 1;//B0のQ乗
	for (int j = 0; j < c; j++) t0 *= B[0];

	//行方向にハッシュ値を計算
	for (int i = 0; i < n; i++) {
		ULL e = 0;
		for (int j = 0; j < c; j++)e = e*B[0] + a[i][j];

		for (int j = 0; j + c <= m; j++) {
			tmp[i][j] = e;
			if (j + c < m)e = e*B[0] - t0*a[i][j] + a[i][j + c];
		}
	}

	ULL t2 = 1;//B2のp乗
	for (int i = 0; i < r; i++)t2 *= B[2];

	//列方向にハッシュ値を計算
	for (int j = 0; j + c <= m; j++) {
		ULL e = 0;
		for (int i = 0; i < r; i++)e = e*B[2] + tmp[i][j];

		for (int i = 0; i + r <= n; i++) {
			Hash[i][j] = e;
			if (i + r < n)e = e*B[2] - t2*tmp[i][j] + tmp[i + r][j];
		}
	}
}

int main() {
	cin >> h >> w;
	REP(i, h)REP(j, w)cin >> field[i][j];
	cin >> r >> c;
	REP(i, r)REP(j, c)cin >> patterns[i][j];
	compute_hash(patterns, r, c);
	ULL HashP = Hash[0][0];
	
	compute_hash(field, h, w);
	for (int i = 0; i + r <= h; i++) {
		for (int j = 0; j + c <= w; j++) {
			if (HashP == Hash[i][j]) {
				cout << i << " " << j << endl;
			}
		}
	}
}