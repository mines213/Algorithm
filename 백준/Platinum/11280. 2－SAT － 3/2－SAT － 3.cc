#include <bits/stdc++.h>
#define ll long long
#define fastio ios::sync_with_stdio(0), cin.tie(0);
using namespace std;
#define MAX 20001
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
    SCC.push_back(scc);
    SN++;
  }
  return parent;
}

int opposite(int a) {
  if (a & 1) {
    return a + 1;
  }
  return a - 1;
}

int main() {
  fastio;
  int v, e;
  cin >> v >> e;
  for (int i = 0; i < e; i++) {
    int a, b;
    cin >> a >> b;
    a = (a > 0) ? a * 2 : -a * 2 - 1;
    b = (b > 0) ? b * 2 : -b * 2 - 1;
    graph[opposite(a)].push_back(b);
    graph[opposite(b)].push_back(a);
  }
  for (int i = 1; i <= v * 2; i++) {
    if (d[i] == 0) dfs(i);
  }
  for (int i = 1; i <= v; i++) {
    if (sn[i * 2] == sn[i * 2 - 1]) {
      cout << 0;
      return 0;
    }
  }
  cout << 1;
  return 0;
}













