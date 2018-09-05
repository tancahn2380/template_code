#include "bits/stdc++.h"
using namespace std;
using LL = long long;

const LL MOD = 1000000007;
LL combi(LL N_, LL C_) {
	const int NUM_ = 400001;
	static LL fact[NUM_ + 1], factr[NUM_ + 1], inv[NUM_ + 1];
	if (fact[0] == 0) {
		inv[1] = fact[0] = factr[0] = 1;
		for (int i = 2; i <= NUM_; ++i) inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
		for (int i = 1; i <= NUM_; ++i) fact[i] = fact[i - 1] * i%MOD, factr[i] = factr[i - 1] * inv[i] % MOD;
	}
	if (C_<0 || C_>N_) return 0;
	return factr[C_] * fact[N_] % MOD*factr[N_ - C_] % MOD;
}
LL hcomb(int P_, int Q_) { return (P_ == 0 && Q_ == 0) ? 1 : combi(P_ + Q_ - 1, Q_); }

LL modpow(LL a, LL n = MOD - 2) {
	LL r = 1;
	while (n) r = r*((n % 2) ? a : 1) % MOD, a = a*a%MOD, n >>= 1;
	return r;
}