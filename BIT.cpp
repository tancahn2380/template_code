# include "bits/stdc++.h"
using LL = long long;
using namespace std;

//BIT

//0-indexed

struct BIT {
	vector<LL> bit;
	BIT(LL n) {
		bit.resize(n + 10);
		for (int i = 0; i < n + 10; i++)bit[i] = 0;
	}
	//[0,i)
	LL sum(int i) {
		LL s = 0;
		for (int x = i - 1; x >= 0; x = (x&(x + 1)) - 1) {
			s += bit[x];
		}
		return s;
	}
	void add(int a, LL w) {
		for (int x = a; x < bit.size(); x |= x + 1) {
			bit[x] += w;
		}
	}
};



//1-indexdであることに注意する

struct BIT {
	vector<LL> bit;
	BIT(int n) {
		bit.resize(n+10);
		for (int i = 0; i < n; i++)bit[i] = 0;
	}
	LL sum(int i) {
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