#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ll long long
#define fastio ios::sync_with_stdio(0), cin.tie(0);
using namespace std;
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type, greater<int>, rb_tree_tag,tree_order_statistics_node_update>
ordered_set OS[100001];
int parent[100001];
int ran[100001]; //rank

int find(int u) {
    if (u == parent[u]) return u;
    return parent[u] = find(parent[u]);
}

void pbds_merge(int u, int v) {
    for (auto it: OS[u]) {
        OS[v].insert(it);
    }
}

void merge(int u, int v) {
    //union
    u = find(u);
    v = find(v);
    if (u == v) return;
    if (ran[u] > ran[v]) {
        parent[v] = u;
        pbds_merge(v, u);
    } else if (ran[u] < ran[v]) {
        parent[u] = v;
        pbds_merge(u, v);
    } else {
        parent[v] = u;
        pbds_merge(v, u);
        ran[u]++;
    }
}

int main() {
    fastio;
    int T;
    cin >> T;
    for (int tc = 0; tc < T; tc++) {
        int N, K;
        cin >> N >> K;
        memset(ran, 0, sizeof ran);
        for (int i = 1; i <= N; i++) {
            OS[i].clear();
            parent[i] = i;
            OS[i].insert(i);
        }
        while (K--) {
            int tmp;
            cin >> tmp;
            if (tmp == 1) {
                int x, y;
                cin >> x >> y;
                merge(x, y);
            } else {
                int j;
                cin >> j;
                cout << OS[find(j)].order_of_key(j) + 1 << "\n";
            }
        }
    }
    return 0;
}
