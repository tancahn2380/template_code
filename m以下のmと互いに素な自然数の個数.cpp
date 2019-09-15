# include "bits/stdc++.h"
using namespace std;

//オイラー関数
//m以下のmと互いに素な自然数の個数

//オイラー関数の値を求める(O√N)
int euler_phi(int n){
    int res = n;
    for(int i = 2;i*i <= n;i++){
        if(n % i == 0){
            res = res/i*(i - 1);
            for(;n % i == 0; n /= i);
        }
    }
    if(n != 1)res = res/n*(n - 1);
    return res;
}

const int max_n = 101010;

int euler[max_n];

//オイラー関数のテーブルを作成(O(MAX_N))
void euler_phi2(){
    for(int i = 0;i < max_n;i++)euler[i] = i;
    for(int i = 2;i < max_n;i++){
        if(euler[i] == i){
            for(int j = i;j < max_n;j += i)euler[j] = euler[j]/i*(i - 1);
        }
    }
}