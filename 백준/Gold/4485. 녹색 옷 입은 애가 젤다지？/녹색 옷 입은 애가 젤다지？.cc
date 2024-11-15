#include <bits/stdc++.h>
#define ll long long
#define X first
#define Y second
using namespace std;
int arr[130][130];
int d[130][130];
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

void solve(int tc, int N) {
    for (int i = 0; i < 130; i++) {
        fill(d[i], d[i] + 130, 0x3f3f3f3f);
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> arr[i][j];
        }
    }
    d[0][0] = arr[0][0];
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int> >, greater<tuple<int, int, int> > > pq;
    pq.push({arr[0][0], 0, 0});
    while (!pq.empty()) {
        int w, x, y;
        tie(w, x, y) = pq.top();
        pq.pop();
        if (d[y][x] != w) continue;
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (0 <= nx && nx < N && 0 <= ny && ny < N) {
                if (d[ny][nx] > w + arr[ny][nx]) {
                    d[ny][nx] = w + arr[ny][nx];
                    pq.push({d[ny][nx], nx, ny});
                }
            }
        }
    }
    cout << "Problem " << tc << ": " << d[N - 1][N - 1] << "\n";
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie();
    int tc = 1;
    int N;
    cin >> N;
    while (N != 0) {
        solve(tc, N);
        tc++;
        cin >> N;
    }
}
