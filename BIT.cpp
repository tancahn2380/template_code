# include "bits/stdc++.h"
using LL = long long;
using namespace std;
struct BIT {
	vector<LL> bit;
	BIT(LL n) {
		bit.resize(n + 10);
	}

	//[0, i)
	LL sum(int i) {
		LL s = 0;
		for (int x = i - 1; x >= 0; x = (x&(x + 1)) - 1) {
			s += bit[x];
		}
		return s;
	}

    //[l, r)
    LL sum(int l, int r){
        return sum(r) - sum(l);
    }

    //[0, i]
    LL sum_open(int i) {
		LL s = 0;
		for (int x = i; x >= 0; x = (x&(x + 1)) - 1) {
			s += bit[x];
		}
		return s;
	}

    //[l, r]
    LL sum_open(int l, int r){
        return sum_open(r) - sum_open(l - 1);
    }
	void add(int a, LL w) {
		for (int x = a; x < (int)bit.size(); x |= x + 1) {
			bit[x] += w;
		}
	}

    //indexを返す
    int lower_bound(LL x){
        int l = -1, r = (int)bit.size();
        while(r - l > 1){
            int mid = (l + r)/2;
            if(sum_open(mid) < x){
                l = mid;
            }else{
                r = mid;
            }
        }
        return r;
    }

    //indexを返す
    int upper_bound(LL x){
        int l = -1, r = (int)bit.size();
        while(r - l > 1){
            int mid = (l + r)/2;
            if(sum_open(mid) <= x){
                l = mid;
            }else{
                r = mid;
            }
        }
        return r;
    }
};