#include "bits/stdc++.h"
using LL = long long;
using namespace std;
template<class T>constexpr T INF() { return ::std::numeric_limits<T>::max(); }


const int MAX_V=10; 
LL d[MAX_V][MAX_V];//d[i][j]はe={u,v}のコスト
int V;

void warshall_floyd(){
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			d[i][j] = INF;
		}
	}
	for(int k=0;k<V;k++){
		for(int i=0;i<V;i++){
			for(int j=0;j<V;j++){
				d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
			}
		}
	}
}