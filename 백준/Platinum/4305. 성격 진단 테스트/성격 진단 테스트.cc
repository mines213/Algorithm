#pragma GCC optimize("O3")
#pragma GCC target("avx2")
#include <bits/stdc++.h>
#define ll long long
#define fastio ios::sync_with_stdio(0), cin.tie(0);
using namespace std;
#define MAX 26
#define X first
#define Y second

int id;
int SN; //scc의 개수
int sn[MAX]; //sn[i] = i가 속한 SCC의 번호
int d[MAX];
bool finished[MAX];
vector<int> graph[MAX];
vector<vector<int> > SCC;
stack<int> s;

int dfs(int x) {
  d[x] = ++id;
  s.push(x);
  int parent = d[x];
  for (int nxt: graph[x]) {
    if (d[nxt] == 0) parent = min(parent, dfs(nxt));
    else if (!finished[nxt]) parent = min(parent, d[nxt]);
  }
  if (parent == d[x]) {
    vector<int> scc;
    while (1) {
      int t = s.top();
      s.pop();
      scc.push_back(t);
      finished[t] = true;
      sn[t] = SN;
      if (t == x) break;
    }
    sort(scc.begin(), scc.end());
    SCC.push_back(scc);
    SN++;
  }
  return parent;
}

void solve(int N) {
  id = 0;
  SN = 0;
  memset(d, 0, sizeof(d));
  memset(finished, 0, sizeof(finished));
  for (int i = 0; i < MAX; i++) {
    graph[i].clear();
  }
  SCC.clear();
  bool isok[26] = {0};
  int arr[5];
  char numt;
  int num;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < 5; j++) {
      char tmp;
      cin >> tmp;
      arr[j] = tmp - 'A';
      isok[arr[j]] = true;
    }
    cin >> numt;
    num = numt - 'A';
    for (int j = 0; j < 5; j++) {
      if (arr[j] != num) {
        graph[num].push_back(arr[j]);
      }
    }
  }
  for (int i = 0; i < 26; i++) {
    if (isok[i] && d[i] == 0) dfs(i);
  }
  sort(SCC.begin(), SCC.end());
  for (auto it: SCC) {
    for (int it2: it) {
      cout << (char) ('A' + it2) << " ";
    }
    cout << "\n";
  }
}

int main() {
  fastio;
  int N;
  cin >> N;
  while (N != 0) {
    solve(N);
    cout << "\n";
    cin >> N;
  }
}














