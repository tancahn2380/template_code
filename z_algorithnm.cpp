# include "bits/stdc++.h"
using namespace std;

vector<int> z_algorithm(string s){
    vector<int> a((int)s.size());
    a[0] = (int)s.size();
    int i = 1, j = 0;
    while(i < (int)s.size()){
        while(i + j < (int)s.size() && s[j] == s[i + j])j++;
        a[i] = j;
        if(j == 0){
            i++;
            continue;
        }
        int k = 1;
        while(i + k < (int)s.size() && k + a[k] < j)a[i + k] = a[k], k++;
        i += k;
        j -= k;
    }
    return a;
}