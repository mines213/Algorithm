#include <bits/stdc++.h>
#define ll long long
#define X first
#define Y second
#define pii pair<int,int>
#define fastio ios::sync_with_stdio(0), cin.tie(0);
using namespace std;

deque<pii > q;

int main() {
    fastio;
    int N, L;
    cin >> N >> L;
    for (int i = 0; i < N; i++) {
        int tmp;
        cin >> tmp;
        while (!q.empty() && q.back().Y >= tmp) q.pop_back();
        q.push_back({i, tmp});
        if (q.front().X < i - L + 1) q.pop_front();
        cout << q.front().Y << " ";
    }
    return 0;
}
