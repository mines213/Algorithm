#pragma GCC optimize("O3")
#pragma GCC target("avx2")
#include <bits/stdc++.h>
#define ll long long
#define fastio ios::sync_with_stdio(0), cin.tie(0);
#define X first
#define Y second
using namespace std;

//구간합 활용 1. kth
//구간합 활용 2. Inversion counting
//걍 무조건 long long 써라
int tree_size, base;
vector<pair<int, int> > seg_tree; //최소, 최대

void init(int size) {
    tree_size = size;
    seg_tree.clear();
    seg_tree.resize(tree_size << 2, {0x7f7f7f7f, 0});
    for (base = 1; base < tree_size; base <<= 1);
}

void update(int i, int x) {
    i += base;
    seg_tree[i].X = x;
    seg_tree[i].Y = x;
    for (i = i >> 1; i > 0; i = i >> 1) {
        seg_tree[i].X = min(seg_tree[i << 1].X, seg_tree[i << 1 | 1].X);
        seg_tree[i].Y = max(seg_tree[i << 1].Y, seg_tree[i << 1 | 1].Y);
    }
}

void seg_swap(int a, int b) {
    int tmp = seg_tree[b + base].X;
    update(b, seg_tree[a + base].X);
    update(a, tmp);
}

pair<int, int> query(int p, int q) {
    // [p,q]
    p += base, q += base;

    pair<int, int> ret = {0x7f7f7f7f, 0};
    while (p < q) {
        if (p & 1) {
            ret.X = min(ret.X, seg_tree[p].X);
            ret.Y = max(ret.Y, seg_tree[p++].Y);
        }
        if (~q & 1) {
            ret.X = min(ret.X, seg_tree[q].X);
            ret.Y = max(ret.Y, seg_tree[q--].Y);
        }
        p = p >> 1, q = q >> 1;
    }
    if (p == q) {
        ret.X = min(ret.X, seg_tree[p].X);
        ret.Y = max(ret.Y, seg_tree[p].Y);
    }
    return ret;
}


int main() {
    fastio;
    int T;
    cin >> T;
    while (T--) {
        int N, K;
        cin >> N >> K;
        init(N);
        for (int i = 0; i < N; i++) {
            update(i, i);
        }
        while (K--) {
            int flag, a, b;
            cin >> flag >> a >> b;
            if (flag == 0) {
                seg_swap(a, b);
            } else {
                int MIN, MAX;
                tie(MIN, MAX) = query(a, b);
                if (a == MIN && b == MAX) {
                    cout << "YES\n";
                } else {
                    cout << "NO\n";
                }
            }
        }
    }

    return 0;
}



























