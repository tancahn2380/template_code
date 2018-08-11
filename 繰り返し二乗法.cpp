#include "bits/stdc++.h"

//n^k%MOD
long long power(long long n, long long k, long long m) {
	if (k == 0) {
		return 1;
	}
	else if (k % 2 == 1) {
		return power(n, k - 1, m)*n%m;
	}
	else {
		long long t = power(n, k / 2, m);
		return t*t%m;
	}
}