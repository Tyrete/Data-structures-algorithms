
// added task from gate_sic "znakocheredovanue"

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>

using namespace std;

struct segtree {
	vector<int> t;
	int size, ZERO;
	void init(int n) {
		size = n;
		ZERO = 0;
		t.resize(4 * size);
	}
	void build(int v, int l, int r, vector<int>& a) {
		if (r - l == 1) {
			t[v] = a[l] * (l % 2 ? -1 : 1);
			return;
		}
		int m = (l + r) / 2;
		build(2 * v + 1, l, m, a);
		build(2 * v + 2, m, r, a);
		t[v] = t[2 * v + 1] + t[2 * v + 2];
	}
	void build(vector<int>& a) {
		init(a.size());
		build(0, 0, size, a);
	}
	int get(int l, int r, int v, int tl, int tr) {
		if (r <= tl || tr <= l) return ZERO;
		if (l <= tl && tr <= r) {
			return t[v] * (l % 2 ? -1 : 1);
		}
		int tm = (tl + tr) / 2;
		int g1 = get(l, r, 2 * v + 1, tl, tm);
		int g2 = get(l, r, 2 * v + 2, tm, tr);
		return g1 + g2;
	}
	int get(int l, int r) {
		return get(l, r, 0, 0, size);
	}
	void set(int pos, int val, int v, int l, int r) {
		if (r - l == 1) {
			t[v] = val * (l % 2 ? -1 : 1);
			return;
		}
		int m = (l + r) / 2;
		if (pos < m) set(pos, val, 2 * v + 1, l, m);
		else set(pos, val, 2 * v + 2, m, r);
		t[v] = t[2 * v + 1] + t[2 * v + 2];
	}
	void set(int pos, int val) {
		set(pos, val, 0, 0, size);
	}
};

void solve() {
	int n; cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	segtree st;
	st.build(a);
	int q; cin >> q;
	for (int i = 0; i < q; i++) {
		int c; cin >> c;
		if (c == 1) {
			int l, r; cin >> l >> r;
			l--;
			cout << st.get(l, r) << '\n';
		}
		else {
			int pos, val; cin >> pos >> val;
			pos--;
			st.set(pos, val);
		}
	}
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int t = 1; //cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
