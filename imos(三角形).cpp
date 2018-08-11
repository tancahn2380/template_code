#include "bits/stdc++.h"
using namespace std;

//三角形上にやる奴（JOI釘）
int trimos[5050][5050];

int main() {
	int n, m;
	cin >> n >> m;
	int a, b, c;
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;
		c++;
		trimos[a][b]++;
		trimos[a][b + 1]--;
		trimos[a + c][b]--;
		trimos[a + c + 1][b + 1]++;
		trimos[a + c][b + c + 1]++;
		trimos[a + c + 1][b + c + 1]--;
	}
	for (int i = 1; i <= n + 1; i++) {
		for (int j = 1; j <= n + 1; j++) {
			trimos[i][j] += trimos[i][j - 1];
		}
	}
	for (int i = 1; i <= n + 1; i++) {
		for (int j = 1; j <= n + 1; j++) {
			trimos[i][j] += trimos[i - 1][j - 1];
		}
	}
	for (int i = 1; i <= n + 1; i++) {
		for (int j = 1; j <= n + 1; j++) {
			trimos[i][j] += trimos[i - 1][j];
		}
	}
	int ans = 0;
	for (int k = 0; k <= n; k++) {
		for (int j = 0; j <= n; j++) {
			if (trimos[k][j])ans++;
		}
	}
	cout << ans << endl;
}