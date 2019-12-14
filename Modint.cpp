# include "bits/stdc++.h"
using namespace std;
using LL = long long;

class Modint{
    static LL &mod(){
        static LL mod_ = 0;
        return mod_;
    }
public:
    LL a;

    Modint(const LL x = 0) : a(x % get_mod()) {}
    Modint(const LL x, const LL mod_){
        mod() = mod_;
        a = x % get_mod();
    }
    LL value() {return a;}
    Modint operator+(const Modint rhs) const{
        return Modint(*this) += rhs;
    }
    Modint operator-(const Modint rhs) const{
        return Modint(*this) -= rhs;
    }
    Modint operator*(const Modint rhs) const{
        return Modint(*this) *= rhs;
    }
    Modint operator/(const Modint rhs) const{
        return Modint(*this) /= rhs;
    }
    Modint &operator+=(const Modint rhs){
        a += rhs.a;
        if(a >= get_mod()){
            a -= get_mod();
        }
        return *this;
    }
    Modint &operator-=(const Modint rhs){
        if(a < rhs.a){
            a += get_mod();
        }
        a -= rhs.a;
        return *this;
    }
    Modint &operator*=(const Modint rhs){
        a = a * rhs.a % get_mod();
        return *this;
    }
    Modint &operator/=(Modint rhs){
        LL exp = get_mod() - 2;
        while(exp){
            if(exp % 2){
                 *this *= rhs;
            }
            rhs *= rhs;
            exp /= 2;
        }
        return *this;
    }
    static LL get_mod() {return mod(); }
};