#include "bits/stdc++.h"

int a[101010], n;
 
struct BIT {
	int bit[202020];
	void init() {
		REP(i, 202020)bit[i] = 0;
	}
	int sum(int i) {
		int s = 0;
		while (i>0) {
			s += bit[i];
			i -= i& -i;
		}
		return s;
	}
	void add(int i, int x) {
		while (i <= 202020) {
			bit[i] += x;
			i += i& -i;
		}
	}
};
 
int main() {
	BIT bit;
	bit.init();
	cin >> n;
	for (int i = 0; i < n; i++)cin >> a[i];
 
	LL ans = 0;
	for (int j = 0; j < n; j++) {
		ans += j - bit.sum(a[j]);
		bit.add(a[j], 1);
	}
	cout << ans << endl;
}