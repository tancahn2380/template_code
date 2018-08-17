#include "bits/stdc++.h"
using namespace std;
template<class T>constexpr T INF() { return ::std::numeric_limits<T>::max(); }

vector<int>L(252525), R(252525);

void Merge(vector<int> &A, int left, int mid, int right) {
	int n1 = mid - left;
	int n2 = right - mid;
	for (int i = 0; i < n1; i++)L[i] = A[left + i];
	for (int i = 0; i < n2; i++)R[i] = A[mid + i];
	L[n1] = R[n2] = INF<int>();
	int i = 0, j = 0;
	for (int k = left; k < right; k++) {
		if (L[i] <= R[j]) {
			A[k] = L[i++];
		}
		else {
			A[k] = R[j++];
		}
	}
}

void MergeSort(vector<int> &A, int left, int right) {
	if (left + 1 < right) {
		int mid = (left + right) / 2;
		MergeSort(A, left, mid);
		MergeSort(A, mid, right);
		Merge(A, left, mid, right);
	}
}

int n;

int main() {
	vector<int> A;
	cin >> n;
	REP(i, n) {
		int num;
		cin >> num;
		A.emplace_back(num);
	}
	MergeSort(A, 0, n);

	REP(i, n) {
		if (i)cout << " ";
		cout << A[i];
	}
	cout << endl;
}