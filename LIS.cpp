#include "bits/stdc++.h"
template<class T>constexpr T INF() { return ::std::numeric_limits<T>::max(); }
using namespace std;

constexpr int MAX_N = 100000;

int n;
int a[MAX_N];
int dp[MAX_N];

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	fill(dp, dp + n, INF);
	for (int i = 0; i < n; i++) {
		*lower_bound(dp, dp + n, a[i]) = a[i];
	}
	cout << lower_bound(dp, dp + n, INF) - dp << endl;
}

int lis(vector<int> &v) {
	vector<int> ans(v.size(), INF);
	for (int i = 0; i < v.size();i++) {
		(*lower_bound(ans.begin(), ans.end(), v[i])) = v[i];
	}
	return lower_bound(ans.begin(), ans.end(), INF) - ans.begin();
}