#pragma GCC optimize("O3")
#pragma GCC target("avx2")
#include <bits/stdc++.h>
#define ll long long
#define fastio ios::sync_with_stdio(0), cin.tie(0);
using namespace std;
#define X first
#define Y second

struct node {
	int x, y, state;
};

int N, M;
int sx, sy;
char board[55][55];
int visited[55][55][1 << 6];
int dx[4] = {0, 0, 1, -1};
int dy[4] = {-1, 1, 0, 0};

int main() {
	fastio;
	int ans = 0x7f7f7f7f;
	memset(visited, -1, sizeof(visited));
	cin >> N >> M;
	cin.ignore();
	for (int i = 0; i < N; i++) {
		string temp;
		getline(cin, temp);
		for (int j = 0; j < M; j++) {
			board[i][j] = temp[j];
			if (temp[j] == '0') {
				sy = i;
				sx = j;
			}
		}
	}
	queue<node> Q;
	visited[sy][sx][0] = 0;
	Q.push({sx, sy, 0});
	while (!Q.empty()) {
		node cur = Q.front();
		Q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = cur.x + dx[i];
			int ny = cur.y + dy[i];
			if (nx < 0 || nx >= M || ny < 0 || ny >= N) continue;
			if (visited[ny][nx][cur.state] != -1 || board[ny][nx] == '#') continue;
			if ('A' <= board[ny][nx] && board[ny][nx] <= 'F' && !(cur.state & (1 << (board[ny][nx] - 'A')))) continue;
			visited[ny][nx][cur.state] = visited[cur.y][cur.x][cur.state] + 1;
			int ns = cur.state;
			if ('a' <= board[ny][nx] && board[ny][nx] <= 'f') {
				ns |= 1 << (board[ny][nx] - 'a');
				visited[ny][nx][ns] = visited[cur.y][cur.x][cur.state] + 1;
			} else if (board[ny][nx] == '1') {
				ans = min(ans, visited[ny][nx][cur.state]);
			}
			Q.push({nx, ny, ns});
		}
	}
	if (ans == 0x7f7f7f7f) {
		cout << -1;
	} else {
		cout << ans;
	}

	return 0;
}
