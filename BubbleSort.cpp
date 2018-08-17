#include "bits/stdc++.h"
using namespace std;

struct card {
	int value;

	bool operator<(const card& x) {
		return value < x.value;
	}
};

vector<card> BubbleSort(vector<card> c, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = n - 1; j >= i + 1; j--) {
			if (c[j] < c[j - 1]) {
				swap(c[j], c[j - 1]);
			}
		}
	}
	return c;
}
