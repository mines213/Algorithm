#include <bits/stdc++.h>
#define ll long long
#define X first
#define Y second
#define fastio ios::sync_with_stdio(0), cin.tie(0);
using namespace std;

int failure(string &p) {
    int n = p.size();
    vector<int> f(n);
    f[0] = 0;
    int j = 0;
    for (int i = 1; i < n; i++) {
        while (j > 0 && p[i] != p[j]) j = f[j - 1];
        if (p[i] == p[j]) {
            f[i] = ++j;
        }
    }
    return f[n - 1];
}

int main() {
    fastio;
    string N, M;
    cin >> N >> M;
    bool flag = true;
    bool fla;
    for (int i = 0; i < N.length() && flag; i++) {
        fla = true;
        for (int j = 0; j < N.length(); j++) {
            if (N[j] != M[(j + i) % N.length()]) {
                fla = false;
                break;
            }
        }
        if (fla) {
            flag = false;
            break;
        }
    }
    if (flag) {
        cout << 0;
        return 0;
    }
    int ans = N.length() - failure(N);
    if (N.length() % ans != 0) {
        cout << 1;
    } else {
        cout << N.length() / ans;
    }
    return 0;
}















