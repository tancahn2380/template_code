#include "bits/stdc++.h"
using LL = long long;
template<class T>constexpr T INF() { return ::std::numeric_limits<T>::max(); }
template<class T>constexpr T HINF() { return INF<T>() / 2; }
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
	fill(dp, dp + n, INF<int>());
	for (int i = 0; i < n; i++) {
		*lower_bound(dp, dp + n, a[i]) = a[i];
	}
	cout << lower_bound(dp, dp + n, INF<int>()) - dp << endl;
}

int lis(vector<LL> &v) {
	vector<LL> ans(v.size(), HINF<LL>());
	for (int i = 0; i < v.size();i++) {
		(*lower_bound(ans.begin(), ans.end(), v[i])) = v[i];
	}
	return lower_bound(ans.begin(), ans.end(), HINF<LL>()) - ans.begin();
}

//広義短調増加

int lis2(vector<LL> &v) {
	vector<LL> ans(v.size(), HINF<LL>());
	for (int i = 0; i < v.size(); i++) {
		(*upper_bound(ans.begin(), ans.end(), v[i])) = v[i];
	}
	return lower_bound(ans.begin(), ans.end(), HINF<LL>()) - ans.begin();
}