#include "bits/stdc++.h"
using namespace std;
using LL = long long;


//Makeprime(n)を呼びだすとnまでの素数の配列ができる

std::vector<int> prime;
void MakePrime(int n) {
	prime.emplace_back(2);
	for (int i = 3; i < n; i += 2) {
		bool a = false;
		for (int j = 3; j <= std::sqrt(i); j += 2) {
			if (i%j == 0) {
				a = true;
			}
		}
		if (a == false) {
			prime.emplace_back(i);
		}
	}
}

////

int prime[101010];
bool is_prime[101010];

// n以下の素数の数を返す
int sieve(int n) {
	int p = 0;
	for (int i = 0; i <= n; i++) {
		is_prime[i] = true;
	}
	is_prime[0] = false;
	is_prime[1] = false;
	for (int i = 2; i <= n; i++) {
		if (is_prime[i]) {
			prime[p++] = i;
			for (int j = 2 * i; j <= n; j += i) {
				is_prime[j] = false;
			}
		}
	}
	return p;
}


//素因数分解
vector<LL> PrimeFact(LL n) {
	vector<LL> res;
	while (n != 1) {
		if (n == 2 || n == 3) {
			res.emplace_back(n); n /= n;
			continue;
		}
		bool prime_flag = false;
		for (int i = 2; i*i <= n; i++) {
			if (n%i == 0) {
				res.emplace_back(i); n /= i;
				prime_flag = true;
				break;
			}
		}
		if (!prime_flag) { res.emplace_back(n); n /= n; }
	}
	return res;
}

//単純な素数判定

bool isprime(LL x) {
	if (x == 2)return true;
	if (x % 2 == 0)return false;
	for (LL i = 3; i <= sqrt(x); i += 2) {
		if (x%i == 0)return false;
	}
	return true;
}