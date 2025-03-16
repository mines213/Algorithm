#pragma GCC optimize("O3")
#pragma GCC target("avx2")
#include <bits/stdc++.h>
#define ll long long
#define fastio ios::sync_with_stdio(0), cin.tie(0);
using namespace std;

int N, M, K;
int board[105][105];
int diamond[105][105];
bool visited[105][105][1 << 9][4];
int ans;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};

struct node {
	int x, y, treasure, time;
};

void check(int value, int time) {
	int res = 0;
	for (int i = 0; i <= 9; i++) {
		int a = 1 << i;
		if (value & a) {
			res++;
		}
	}
	if (res == K) {
		ans = min(ans, time);
	}
}

int main() {
	fastio;
	cin >> N >> M;
	while (N != 0 && M != 0) {
		//memset 하기
		ans = 0x7f7f7f7f;
		memset(diamond, 0, sizeof(diamond));
		memset(visited, 0, sizeof(visited));
		cin.ignore();
		for (int i = 0; i < N; i++) {
			string tmp;
			getline(cin, tmp);
			for (int j = 0; j < M; j++) {
				if (tmp[j] == 'N') {
					board[i][j] = 0;
				} else if (tmp[j] == 'E') {
					board[i][j] = 1;
				} else if (tmp[j] == 'S') {
					board[i][j] = 2;
				} else {
					board[i][j] = 3;
				}
			}
		}
		cin >> K;
		for (int i = 0; i < K; i++) {
			int a, b;
			cin >> a >> b;;
			diamond[a - 1][b - 1] = 1 << i;
		}
		queue<node> Q;
		if (diamond[0][0]) {
			visited[0][0][diamond[0][0]][0] = true;
			Q.push({0, 0, diamond[0][0], 0});
		} else {
			visited[0][0][0][0] = true;
			Q.push({0, 0, 0, 0});
		}
		while (!Q.empty()) {
			node cur = Q.front();
			Q.pop();
			int plustime = (cur.time + 1) % 4;
			if (!visited[cur.y][cur.x][cur.treasure][plustime]) {
				visited[cur.y][cur.x][cur.treasure][plustime] = true;
				Q.push({cur.x, cur.y, cur.treasure, cur.time + 1});
			}
			int where = (cur.time + board[cur.y][cur.x]) % 4;
			int ny = cur.y + dy[where];
			int nx = cur.x + dx[where];
			if (nx < 0 || nx >= M || ny < 0 || ny >= N) continue;
			if (visited[ny][nx][cur.treasure][plustime] == true) continue;
			visited[ny][nx][cur.treasure][plustime] = true;
			if (diamond[ny][nx]) {
				cur.treasure |= diamond[ny][nx];
			}
			if (ny == N - 1 && nx == M - 1) {
				check(cur.treasure, cur.time + 1);
			}
			Q.push({nx, ny, cur.treasure, cur.time + 1});
		}
		cout << ans << "\n";
		cin >> N >> M;
	}
	return 0;
}
