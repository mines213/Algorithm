// 6543 그래프의 싱크
#include <bits/stdc++.h>
#define ll long long
#define fastio ios::sync_with_stdio(0), cin.tie(0);
using namespace std;
#define MAX 5001
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

int main() {
  fastio;
  int v, e;
  cin >> v;
  while (v != 0) {
    vector<int> ans;
    id = 0;
    SN = 0;
    memset(sn, 0, sizeof(sn));
    memset(d, 0, sizeof(d));
    memset(finished, 0, sizeof(finished));
    SCC.clear();
    for (int i = 0; i < MAX; i++) {
      graph[i].clear();
    }
    cin >> e;
    for (int i = 0; i < e; i++) {
      int a, b;
      cin >> a >> b;
      graph[a].push_back(b);
    }
    for (int i = 1; i <= v; i++) {
      if (d[i] == 0) dfs(i);
    }
    for (auto it: SCC) {
      bool flag = false;
      for (int it2: it) {
        for (int a: graph[it2]) {
          if (sn[it2] != sn[a]) {
            flag = true;
            break;
          }
        }
        if (flag) {
          break;
        }
      }
      if (flag) {
        continue;
      }
      for (int it2: it) {
        ans.push_back(it2);
      }
    }
    sort(ans.begin(), ans.end());
    for (int it: ans) {
      cout << it << " ";
    }
    cout << "\n";
    cin >> v;
  }
}


















