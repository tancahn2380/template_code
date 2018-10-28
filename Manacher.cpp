# include <bits/stdc++.h>
using namespace std;

//O(|S|)
//http://snuke.hatenablog.com/entry/2014/12/02/235837
//verified
//https://yukicoder.me/submissions/294991

struct Manacher {
	string s;
	vector<int> radius;

	Manacher(string str) {
		for (int i = 0; i < str.size(); i++) {
			if (i)s += "#";
			s += str[i];
		}
		radius.resize(s.size());

		int i = 0, j = 0;
		while (i < s.size()) {
			while (i - j >= 0 && i + j < s.size() && s[i - j] == s[i + j])++j;
			radius[i] = j;
			int k = 1;
			while (i - k >= 0 && i + k < s.size() && k + radius[i - k] < j)radius[i + k] = radius[i - k], ++k;
			i += k, j -= k;
		}
	}
	//[l,r]
	bool is_palindrome(int l,int r) {
		return radius[l + r] >= r - l + 1;
	}
};

