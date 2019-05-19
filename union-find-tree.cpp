#include "bits/stdc++.h"
using namespace std;
template<class T>constexpr T INF() { return ::std::numeric_limits<T>::max(); }
template<class T>constexpr T HINF() { return INF<T>() / 2; }

//経路圧縮なし、サイズを求めるとき以外はあまり使わないほうが良い、ならしO(log N)
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

//部分永続、経路圧縮無し、ならしO(log N)
struct UnionFind {
	UnionFind(size_t size){
        for(int i = 0;i < (int)size;i++){
            par.emplace_back(-1);
            time.emplace_back(HINF<int>());
        }
        now = 0;
    }
	vector<int> par, time;
    int now;

    int find(int t, int x){
        if(time[x] > t)return x;
        else if(par[x] < 0)return x;
        else return find(t, par[x]);
    }

    bool same(int t, int x, int y){
        return find(t, x) == find(t, y);
    }

    int unite(int x, int y){
        ++now;
        x = find(now, x);
        y = find(now, y);
        if(x == y)return now;
        if(par[x] < par[y])swap(x, y);
        par[x] += par[y];
        par[y] = x;
        time[y] = now;
        return now;
    }
};

//経路圧縮あり、O(α(N))
struct UnionFind {
	UnionFind(size_t size){
        for(int i = 0;i < (int)size;i++){
            par.emplace_back(i);
            rnk.emplace_back(0);
        }
    }
	vector<int> par, rnk;

    int find(int x){
        if(par[x] == x)return x;
        else return par[x] = find(par[x]);
    }

    void unite(int x, int y){
        x = find(x);
        y = find(y);
        if(x == y)return;
        if(rnk[x] < rnk[y]){
            par[x] = y;
        }else{
            par[y] = x;
            if(rnk[x] == rnk[y])rnk[x]++;
        }
    }
    bool same(int x,int y){
        return find(x) == find(y);
    }
};
