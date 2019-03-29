vector <int> v[N];
queue <int> q;
int n, deg[N];
int cnt, ord[N];

void Topological_sort() {
	cnt = 0;
	while (!q.empty()) q.pop();
	for (int i = 0; i < n; i ++) if (!deg[i]) q.push(i);
	while (!q.empty()) {
		int j = q.front(), q.pop();
		ord[++ cnt] = j;
		for (int i = 0; i < v[j].size(); i ++) {
			int k = v[j][i];
			deg[k] --;
			if (!deg[k]) q.push(k);
		}
	}
}
