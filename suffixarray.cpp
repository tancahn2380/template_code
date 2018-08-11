#include "bits/stdc++.h"
using namespace std;

//suffixarray

const int MAX_N = 303030;

int n, k;
int Rank[MAX_N + 1];
int tmp[MAX_N + 1];

//(rank[i],rank[i+k])と(rank[j],rank[j+k])を比較
bool compare_sa(int i, int j) {
	if (Rank[i] != Rank[j]) return Rank[i] < Rank[j];
	else {
		int r1 = (i + k <= n ? Rank[i + k] : -1);
		int r2 = (j + k <= n ? Rank[j + k] : -1);
		return r1 < r2;
	}
}

//文字列Sの接尾辞配列（全ての接尾辞を辞書順にソートしたもの）を構築
void construct_sa(string s, int *sa) {
	n = s.length();

	//最初は1文字、ランクは文字コードにすればよい
	for (int i = 0; i <= n; i++) {
		sa[i] = i;
		Rank[i] = (i < n ? s[i] : -1);
	}

	//k文字についてソートされているところから2k文字でソートする
	for (k = 1; k <= n; k *= 2) {
		sort(sa, sa + n + 1, compare_sa);

		//いったんtmpに次のランクを計算し、それからRankに移す
		tmp[sa[0]] = 0;
		for (int i = 1; i <= n; i++) {
			tmp[sa[i]] = tmp[sa[i - 1]] + (compare_sa(sa[i - 1], sa[i]) ? 1 : 0);
		}
		for (int i = 0; i <= n; i++) {
			Rank[i] = tmp[i];
		}
	}
}

//文字列検索
bool contain(string s, int *sa, string t) {
	int a = 0, b = s.length();
	while (b - a > 1) {
		int c = (a + b) / 2;
		//sのsa[c]文字目から|T|文字とTを比較
		if (s.compare(sa[c], t.length(), t) < 0)a = c;
		else b = c;
	}
	return s.compare(sa[b], t.length(), t) == 0;//0の時一致を表す
}

int Rank2[MAX_N + 1];

//文字列Sとその接尾辞配列saを受け取り、高さ配列をlcpに計算
void construct_lcp(string s, int *sa, int *lcp) {
	int N = s.length();
	for (int i = 0; i <= N; i++)Rank2[sa[i]] = i;

	int h = 0;
	lcp[0] = 0;
	for (int i = 0; i < N; i++) {
		//文字列中での位置iの接尾辞と、接尾辞配列中でその1つ前の接尾辞のLCPを求める
		int j = sa[Rank2[i] - 1];

		//hを先頭の分1減らし、後ろが一致しているだけ増やす
		if (h > 0)h--;
		for (; j + h < N&&i + h < N; h++) {
			if (s[j + h] != s[i + h])break;
		}
		lcp[Rank2[i] - 1] = h;
	}
}
