# include "bits/stdc++.h"
using namespace std;
using LL = long long;
LL gcd(LL a, LL b) { if (b == 0)return a; return gcd(b, a%b); };
LL lcm(LL a, LL b) { LL g = gcd(a, b); return a / g*b; };

// a x + b y = gcd(a, b)
LL extgcd(LL a, LL b, LL &x, LL &y) {
    LL g = a; x = 1; y = 0;
    if (b != 0) g = extgcd(b, a % b, y, x), y -= (a / b) * x;
    return g;
}

//a x ≡ m (mod m)
LL mod_inverse(LL a, LL m){
    LL x, y;
    extgcd(a, m, x, y);
    return (m + x%m)%m;
}