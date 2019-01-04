# include "bits/stdc++.h"
using namespace std;
using LL = long long;
template<class T>constexpr T INF() { return ::std::numeric_limits<T>::max(); }
template<class T>constexpr T HINF() { return INF<T>() / 2; }

//node.resizeの初期値に注意する
template <typename T> struct SegmentTree {
private:
    int n;
    vector<T> node;
public:
    SegmentTree(vector<T> v) {
        int sz = v.size();
        n = 1; while(n < sz) n *= 2;
        node.resize(2*n - 1, INF<T>());
        for(int i = 0; i < sz; i++) node[i + n - 1] = v[i];
        for(int i = n - 2; i >= 0; i--) node[i] = min(node[2*i + 1], node[2*i + 2]);
    }

    //xをvalに変更する
    void update(int x, T val) {
        x += (n - 1);
        node[x] = val;
        while(x > 0) {
            x = (x - 1) / 2;
            node[x] = min(node[2*x + 1], node[2*x + 2]);
        }
    }

    //xにvalを加算する
    void add(int x, T val){
        x += (n - 1);
        node[x] += val;
        while(x > 0) {
            x = (x - 1) / 2;
            node[x] = min(node[2*x + 1], node[2*x + 2]);
        }
    }

    //[a,b)の最小値を求める
    T getmin(int a, int b, int k = 0, int l = 0, int r = -1) {
        if(r < 0) r = n;
        if(r <= a || b <= l) return INF<T>();
        if(a <= l && r <= b) return node[k];

        int vl = getmin(a, b, 2*k + 1, l, (l + r)/2);
        int vr = getmin(a, b, 2*k + 2, (l + r)/2, r);
        return min(vl, vr);
    }
};

int n, q;

int main() {
    cin >> n >> q;
    SegmentTree<int> seg( vector<int>(n, INF<int>()) );
    for(int i = 0; i < q; i++) {
        int c, x, y;
        cin >> c >> x >> y;
        if(c == 0) seg.update(x, y);
        else cout << seg.getmin(x, y + 1) << endl;
    }
}