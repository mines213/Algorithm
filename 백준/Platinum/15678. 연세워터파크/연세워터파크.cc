#include <bits/stdc++.h>
#define ll long long
#define X first
#define Y second
#define pii pair<int,ll>
#define fastio ios::sync_with_stdio(0), cin.tie(0);
using namespace std;

deque<pii > q;
ll ans;

int main() {
    fastio;
    int N, L;
    cin >> N >> L;
    ll tmp;
    cin >> tmp;
    ans = tmp;
    q.push_back({0, tmp});
    for (int i = 1; i < N; i++) {
        cin >> tmp;
        tmp = max(tmp, tmp + q.front().Y);
        ans = max(ans, tmp);
        while (!q.empty() && q.back().Y <= tmp) q.pop_back();
        q.push_back({i, tmp});
        if (q.front().X <= i - L) q.pop_front();
    }
    cout << ans;
    return 0;
}
