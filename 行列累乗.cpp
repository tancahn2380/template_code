# include "bits/stdc++.h"
using namespace std;
using LL = long long;

//行列は二次元vectorを用いることにする
typedef vector<LL> vec;
typedef vector<vec> mat;

//A*Bの計算
mat mul(mat &A, mat&B, int M) {
	mat C(A.size(), vec(B[0].size()));
	for (int i = 0; i < A.size(); i++) {
		for (int k = 0; k < B.size(); k++) {
			for (int j = 0; j < B[0].size(); j++) {
				C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % M;
			}
		}
	}
	return C;
}

//A^nの計算
mat pow(mat A, LL n, int M) {
	mat B(A.size(), vec(A.size()));
	for (int i = 0; i < A.size(); i++) {
		B[i][i] = 1;
	}
	while (n > 0) {
		if (n & 1)B = mul(B, A, M);
		A = mul(A, A, M);
		n >>= 1;
	}
	return B;
}

LL n;

int main() {
	cin >> n;
	mat A(2, vec(2));
	A[0][0] = 1, A[0][1] = 1;
	A[1][0] = 1, A[1][1] = 0;
	A = pow(A, n,1e9+7);
	cout << A[1][0] << endl;
}