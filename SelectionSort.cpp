#include "bits/stdc++.h"
using namespace std;

struct card {
	int value;

	bool operator<(const card& x) {
		return value < x.value;
	}
};

vector<card> SelectionSort(vector<card> c, int n) {
	for (int i = 0; i < n; i++) {
		int minj = i;
		for (int j = i; j < n; j++) {
			if (c[j] < c[minj]) {
				minj = j;
			}
		}
		swap(c[i], c[minj]);
	}
	return c;
}