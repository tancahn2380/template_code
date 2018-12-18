#include "bits/stdc++.h"
using namespace std;

template<int Base>struct Bigint{
    vector<int> a;

    Bigint(){a = vector<int>(0,0);}
    Bigint(long long x){
        while(x > 0){
            a.emplace_back(x%10);
            x /= 10;
        }
        reverse(a.begin(), a.end());
    }
    Bigint(string s){
        for(int i = 0;i < (int)s.size();i++){
            a.emplace_back(s[i] -'0');
        }
    }
    string Bigint_to_string(){
        string ret;
        for(int i = 0;i < (int)a.size();i++){
            ret += to_string(a[i]);
        }
        return ret.empty() ? "0" : ret;
    }

    int size(){
        return a.size();
    }
    //0-indexed
    int nth_digit(int n){
        return a[n];
    }
    //怪しい
    Bigint& shift(){
        for(int i = 0;i < (int)a.size() - 1;i++){
            if(a[i] >= 0){
                a[i + 1] += a[i] / Base;
                a[i] %= Base;
            }
            else{
                int x = (-a[i] + Base - 1) / Base;
                a[i] += x * Base;
                a[i + 1] -= x;
            }
        }
        while(a.back() >= Base){

        }
    }
    bool operator==(const Bigint& b) const {
        return a == b.a;
    }
    bool operator!=(const Bigint& b) const {
        return a != b.a;
    }
    bool operator<(const Bigint& b)const{
        if(a.size() != b.a.size()) return a.size() < b.a.size();
        for(int i = a.size() - 1;i >= 0; i--){
            if(a[i] != b.a[i])return a[i] < b.a[i];
        }
        return false;
    }
    bool operator>(const Bigint& b)const{
        return b < (*this);
    }
    bool operator<=(const Bigint& b) const {
         return !((*this) > b);
    }
	bool operator>=(const Bigint& b) const {
         return !((*this) < b);
    }
    Bigint& operator+=(const Bigint & b){
        if(a.size() < b.a.size()) a.resize(b.a.size(), 0);
        for(int i = 0;i < (int)b.a.size();i++) a[i] += b.a[i];
        return (*this).shift();
    }
};