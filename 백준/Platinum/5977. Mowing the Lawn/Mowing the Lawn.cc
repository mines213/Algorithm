#include <bits/stdc++.h>
#define ll long long
#define X first
#define Y second
#define pii pair<int,ll>
#define fastio ios::sync_with_stdio(0), cin.tie(0);
using namespace std;

deque<pii > q;

int main() {
    fastio;
    int N, L;
    ll minus = 100000000000000;
    ll hap = 0;
    cin >> N >> L;
    q.push_back({-1, 0});
    for (int i = 0; i < N; i++) {
        ll tmp;
        cin >> tmp;
        hap += tmp;
        tmp += q.front().Y;
        if (N - L - 1 <= i)
            minus = min(minus, tmp);
        while (!q.empty() && q.back().Y >= tmp) q.pop_back();
        q.push_back({i, tmp});
        if (q.front().X <= i - L - 1) q.pop_front();
    }
    cout << hap - minus;
    return 0;
}
