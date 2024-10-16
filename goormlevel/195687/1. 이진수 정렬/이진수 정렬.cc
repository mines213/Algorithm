#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ll long long
#define X first
#define Y second
#define fastio ios::sync_with_stdio(0), cin.tie(0);
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update>
using namespace std;
struct s {
	int a;
	int val;
	bool operator<(const s &r) const {
		if (val==r.val) {
			return a>r.a;
		}
		return val>r.val;
	}
};
vector<s> arr;
int main() {
    fastio;
    int N,M;
		cin >> N >> M;
		arr.resize(N);
		for (int i=0; i<N; i++) {
			int tmp;
			int cnt=1;
			cin >> tmp;
			arr[i].a=tmp;
			while (tmp!=1) {
				if (tmp&1)
					cnt++;
				tmp/=2;
			}
			arr[i].val=cnt;
		}
		sort(arr.begin(),arr.end());
		cout << arr[M-1].a;
    return 0;
}
