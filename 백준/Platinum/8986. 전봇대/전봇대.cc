#include <bits/stdc++.h>
#define ll long long
#define X first
#define Y second
#define fastio ios::sync_with_stdio(0), cin.tie(0);
using namespace std;
int N;
int arr[100005];

ll f(ll distance) {
    ll result = 0;
    for (int i = 1; i < N; i++)
        result += abs(1ll * distance * i - arr[i]);
    return result;
}

int main() {
    fastio;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    ll lo = 0, hi = arr[N - 1];
    while (hi - lo >= 3) {
        ll p = (lo * 2 + hi) / 3, q = (lo + hi * 2) / 3;
        if (f(p) <= f(q)) hi = q;
        else lo = p;
    }

    ll res = 1e18;
    for (int i = lo; i <= hi; i++) {
        res = min(f(i), res);
    }

    cout << res;
}
