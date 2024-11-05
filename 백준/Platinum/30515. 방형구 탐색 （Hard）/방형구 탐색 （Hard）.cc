#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ll long long
#define fastio ios::sync_with_stdio(0), cin.tie(0);
using namespace std;
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

int main() {
    fastio;
    unordered_map<int, ordered_set> OS;
    map<int, int> M;
    int N;
    cin >> N;
    for (int i = 1; i <= N; i++) {
        int tmp;
        cin >> tmp;
        OS[tmp].insert(i);
        M[i] = tmp;
    }
    int Q;
    cin >> Q;
    while (Q--) {
        int tmp, l, r;
        cin >> tmp >> l >> r;
        if (tmp == 1) {
            int k;
            cin >> k;
            cout << OS[k].order_of_key(r + 1) - OS[k].order_of_key(l) << "\n";
        } else {
            auto it = M.lower_bound(l);
            while (it != M.end() && (*it).first <= r) {
                OS[(*it).second].erase((*it).first);
                it = M.erase(it);
            }
        }
    }


    return 0;
}
