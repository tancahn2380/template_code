#include "bits/stdc++.h"
using namespace std;


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