
//https://old.informatics.msk.ru/mod/statements/view3.php?id=257&chapterid=169#1

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

vector<vector<pair<int, int>>> gr;
vector<int> d;
vector<bool> used;
void dijkstra(int s) {
	d[s] = 0;
	set<pair<int, int>> q;
	q.insert({ d[s], s });
	while (!q.empty()) {
		int v = q.begin()->second;
		q.erase(q.begin());
		for (auto it : gr[v]) {
			int to = it.first;
			int len = it.second;
			if (d[v] + len < d[to]) {
				q.erase({ d[to], to });
				d[to] = d[v] + len;
				q.insert({ d[to], to });
			}
		}
	}
}
int main()
{
	int n; cin >> n;
	gr.resize(n), d.resize(n, 2e9), used.resize(n);
	vector<int> vec(n);
	for (int i = 0; i < n; i++)
		cin >> vec[i];
	int m; cin >> m;
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v;
		u--, v--;
		gr[u].push_back({v, vec[u]});
		gr[v].push_back({u, vec[v]});
	}
	dijkstra(0);
	if (d[n - 1] == 2e9)
		d[n - 1] = -1;
	cout << d[n - 1];
}