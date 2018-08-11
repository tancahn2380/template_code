#include "bits/stdc++.h"
using namespace std;

string sum_string(string a, string b) {
	int al = a.size(), bl = b.size();
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	string ret;
	int tmp = 0;
	for (int i = 0; i < al || i < bl || tmp; i++) {
		tmp += (i < al ? a[i] - '0' : 0) + (i < bl ? b[i] - '0' : 0);
		ret.push_back('0' + tmp % 10);
		tmp /= 10;
	}
	reverse(ret.begin(), ret.end());
	return ret;
}