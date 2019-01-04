# include "bits/stdc++.h"
using namespace std;
using LL = long long;
template<class T>constexpr T INF() { return ::std::numeric_limits<T>::max(); }
template<class T>constexpr T HINF() { return INF<T>() / 2; }








//正しくないのでRSQ.cppを参照のこと









//node.resizeの初期値に注意する
//getsumの範囲外の値に注意する
template <typename T> struct SegmentTree {
private:
    int n;
    vector<T> node;
public:
    SegmentTree(vector<T> v) {
        int sz = v.size();
        n = 1; while(n < sz) n *= 2;
        node.resize(2*n - 1, 0);
        for(int i = 0; i < sz; i++) node[i + n - 1] = v[i];
        for(int i = n - 2; i >= 0; i--) node[i] = node[2*i + 1] + node[2*i + 2];
    }

    //xをvalに変更する
    void update(int x, T val) {
        x += (n - 1);
        node[x] = val;
        while(x > 0) {
            x = (x - 1) / 2;
            node[x] = node[2*x + 1] + node[2*x + 2];
        }
    }

    //xにvalを加算する
    void add(int x, T val){
        x += (n - 1);
        node[x] += val;
        while(x > 0) {
            x = (x - 1) / 2;
            node[x] = node[2*x + 1] + node[2*x + 2];
        }
    }

    //[a,b)の和を求める
    int getsum(int a, int b, int k = 0, int l = 0, int r = -1) {
        if(r < 0) r = n;
        if(r <= a || b <= l) return 0;
        if(a <= l && r <= b) return node[k];

        int vl = getsum(a, b, 2*k + 1, l, (l + r)/2);
        int vr = getsum(a, b, 2*k + 2, (l + r)/2, r);
        return vl + vr;
    }
};

int n, q;

int main() {
    cin >> n >> q;
    SegmentTree<int> seg( vector<int>(n, 0) );
    for(int i = 0; i < q; i++) {
        int c, x, y;
        cin >> c >> x >> y;
        x--, y--;
        if(c == 0) seg.add(x, y);
        else cout << seg.getsum(x, y + 1) << endl;
    }
}