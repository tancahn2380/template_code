# include "bits/stdc++.h"
using namespace std;

//BIT
//1-indexdであることに注意する

struct BIT {
	vector<LL> bit;
	BIT(int n) {
		bit.resize(n+10);
		for (int i = 0; i < n; i++)bit[i] = 0;
	}
	int sum(int i) {
		LL s = 0;
		while (i>0) {
			s += bit[i];
			i -= i& -i;
		}
		return s;
	}
	void add(int i, LL x) {
		while (i <= bit.size()-1) {
			bit[i] += x;
			i += i& -i;
		}
	}
};

int main() {
	BIT bit(n);
	cout << bit.sum(5) << endl;
}