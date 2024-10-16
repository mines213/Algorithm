#include <bits/stdc++.h>
#define ll long long
#define X first
#define Y second
#define fastio ios::sync_with_stdio(0), cin.tie(0);
using namespace std;
vector<vector<int>> board;
int N,K;
ll f(int i,int j) {
	ll sum=0;
	for (int y=i; y<i+K; y++) {
		for (int x=j; x<j+K; x++) {
			sum+=board[y][x];
		}
	}
	return sum;
}
void solve() {
	board.clear();
	cin >> N >> K;
	ll ans=0x7f7f7f7f;
	board.resize(N,vector<int>(N));
	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			cin >> board[i][j];
		}
	}
	for (int i=0; i<=N-K; i++) {
		for (int j=0; j<=N-K; j++) {
			ans=min(ans,f(i,j));
		}
	}
	cout << ans << "\n";
	return;
}

int main() {
	fastio;
	int T;
	cin >> T;
	while (T--) {
		solve();
	}
	return 0;
}