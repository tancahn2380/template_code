#include "bits/stdc++/h"
using namespace std;
using LL = long long;
using ULL = unsigned long long;

const ULL B[] = { 999999937ULL,1000000007ULL };

//aはbに含まれているか?O(|b|)
bool contain(string a, string b) {
	int al = a.length(), bl = b.length();
	if (al > bl)return false;

	//Bのal乗を計算
	ULL t[] = { 1 ,1 };
	for (int i = 0; i < al; i++)t[0] *= B[0];
	for (int i = 0; i < al; i++)t[1] *= B[1];

	//aとbの最初のal文字に関するハッシュ値を計算
	ULL ah[] = { 0 ,0 }, bh[] = { 0 ,0 };
	for (int i = 0; i < al; i++)ah[0] = ah[0] * B[0] + a[i];
	for (int i = 0; i < al; i++)bh[0] = bh[0] * B[0] + b[i];
	for (int i = 0; i < al; i++)ah[1] = ah[1] * B[1] + a[i];
	for (int i = 0; i < al; i++)bh[1] = bh[1] * B[1] + b[i];

	//bの場所を1つずつ進めながらハッシュ値をチェック
	for (int i = 0; i + al <= bl; i++) {
		if (ah[0] == bh[0] && ah[1] == bh[1])return true;//bのi文字目からのal文字が一致
		if (i + al < bl) {
			bh[0] = bh[0] * B[0] + b[i + al] - b[i] * t[0];
			bh[1] = bh[1] * B[1] + b[i + al] - b[i] * t[1];
		}
	}
	return false;//一致する文字列がない
}


const ULL B[] = { 999999937ULL,1000000007ULL };

//aはbにいくつ含まれているか?O(|b|)
int contain(string a, string b) {
	
	int ret = 0;

	int al = a.length(), bl = b.length();
	if (al > bl)return false;

	//Bのal乗を計算
	ULL t[] = { 1 ,1 };
	for (int i = 0; i < al; i++)t[0] *= B[0];
	for (int i = 0; i < al; i++)t[1] *= B[1];

	//aとbの最初のal文字に関するハッシュ値を計算
	ULL ah[] = { 0 ,0 }, bh[] = { 0 ,0 };
	for (int i = 0; i < al; i++)ah[0] = ah[0] * B[0] + a[i];
	for (int i = 0; i < al; i++)bh[0] = bh[0] * B[0] + b[i];
	for (int i = 0; i < al; i++)ah[1] = ah[1] * B[1] + a[i];
	for (int i = 0; i < al; i++)bh[1] = bh[1] * B[1] + b[i];

	//bの場所を1つずつ進めながらハッシュ値をチェック
	for (int i = 0; i + al <= bl; i++) {
		if (ah[0] == bh[0] && ah[1] == bh[1])ret++;//bのi文字目からのal文字が一致
		if (i + al < bl) {
			bh[0] = bh[0] * B[0] + b[i + al] - b[i] * t[0];
			bh[1] = bh[1] * B[1] + b[i + al] - b[i] * t[1];
		}
	}
	return ret;
}

//sの部分文字列同士の比較がO(1)でできるもの
//https://topcoder.g.hatena.ne.jp/spaghetti_source/20130209/1360403866
const ULL MOD = 1000000007ULL;

struct rolling_hash{
	int n;
	vector<ULL> t, h;
	rolling_hash(string s){
		n = (int)s.size();
        t.assign(n + 1, 0);
		h.assign(n + 1, 0);
		t[0] = 1;
		for(int i = 0;i < n;i++)t[i + 1] = t[i] * MOD;

		for(int i = 0;i < n;i++)h[i + 1] = h[i] * MOD + s[i];
	}

	//[l, r)(もとの文字列の0-indexed)のハッシュ値を返す
	ULL hash(int l,int r){
		if(l > r)return 0;
		return h[r] - h[l]*t[r - l];
	}
};