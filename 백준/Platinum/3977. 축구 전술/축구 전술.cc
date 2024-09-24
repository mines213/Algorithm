#pragma GCC optimize("O3")
#pragma GCC target("avx2")
#include <bits/stdc++.h>
#define ll long long
#define fastio ios::sync_with_stdio(0), cin.tie(0);
using namespace std;
#define MAX 100001
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

void solve() {
  id = 0;
  SN = 0;
  memset(d, 0, sizeof(d));
  memset(finished, 0, sizeof(finished));
  for (int i = 0; i < MAX; i++) {
    graph[i].clear();
  }
  SCC.clear();
  int v, e;
  cin >> v >> e;
  for (int i = 0; i < e; i++) {
    int a, b;
    cin >> a >> b;
    graph[a].push_back(b);
  }
  for (int i = 0; i < v; i++) {
    if (d[i] == 0) dfs(i);
  }
  int SCC_indegree[SN] = {0};
  for (int i = 0; i < v; i++) {
    for (int it: graph[i]) {
      if (sn[i] != sn[it]) {
        SCC_indegree[sn[it]]++;
      }
    }
  }
  vector<int> ans;
  bool flag = false;
  for (int i = 0; i < SN; i++) {
    if (SCC_indegree[i] == 0) {
      if (!flag) {
        for (int it: SCC[i]) {
          ans.push_back(it);
        }
        flag = true;
      } else {
        cout << "Confused\n";
        return;
      }
    }
  }
  sort(ans.begin(), ans.end());
  for (int it: ans) {
    cout << it << "\n";
  }
}

int main() {
  fastio;
  int T;
  cin >> T;
  while (T--) {
    solve();
    cin.ignore();
    string tmp;
    if (T > 0) {
      cout << "\n";
      getline(cin, tmp);
    }
  }
}














