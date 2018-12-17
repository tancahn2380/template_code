#include "bits/stdc++.h"
using namespace std;

struct UnionFind {
	UnionFind(size_t size) : v(size, -1) {}
	vector<int> v;

int root(int x) {
    return (v[x] < 0 ? x : v[x] = root(v[x]));
}

bool is_root(int x) {
    return x == root(x);
}

bool same(int x, int y) {
    return root(x) == root(y);
}

void unite(int x, int y) {
    x = root(x);
    y = root(y);
    if (x != y) {
		if (v[x] > v[y]) swap(x, y);
		v[x] += v[y];
		v[y] = x;
    }
}

int size(int x) {
    	return -v[root(x)];
	}
};