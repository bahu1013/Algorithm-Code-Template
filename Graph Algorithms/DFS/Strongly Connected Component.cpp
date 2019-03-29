#include <cstdio>
#include <vector>
#include <memory.h>

#define N 10010

using namespace std;

vector <int> V[N], RV[N];

bool vis[N];
int ord[N], ftime;

int col[N], C;

int n, m;

void Init() {
	for (int i = 1; i <= n; i ++) {
		V[i].clear();
		RV[i].clear();
		vis[i] = 0;
		col[i] = 0;
	}
}

void DFS(int u) {
	vis[u] = 1;
	for (int i = 0; i < V[u].size(); i ++) {
		int v = V[u][i];
		if (!vis[v]) DFS(v);
	}
	ord[ftime --] = u;
}

void DFS_(int u) {
	vis[u] = 1;
	col[u] = C;
	for (int i = 0; i < RV[u].size(); i ++) {
		int v = RV[u][i];
		if (!vis[v]) DFS_(v);
	}
}

int main() {
	while (scanf("%d %d", &n, &m)>0) {
		Init();

		for (int k = 1; k <= m; k ++) {
			int i, j;
			scanf("%d %d", &i, &j);
			V[i].push_back(j);
			RV[j].push_back(i);
		}

		ftime = n;
		for (int i = 1; i <= n; i ++) if (!vis[i]) DFS(i);
		for (int i = 1; i <= n; i ++) vis[i] = 0;

		C = 0;
		for (int i = 1; i <= n; i ++) if (!vis[ord[i]]) {
			C ++;
			DFS_(ord[i]);
		}
	}
	return 0;
}

//Simple
int visit(int u){
	int m, mn;

	sign[u] = mn = ++ count;
	S[++ top] = u;

	int sz = V[u].size();
	for (int i = 0; i < sz; i ++){
		int v = V[u][i];
		if (!sign[v]) m = visit(v);
		else m = sign[v];
		if (m < mn) mn = m;
	}

	if (mn == sign[u]){
		C ++;
		int x;
		do {
			x = S[top --];
			col[x] = C;
			sign[x] = N + 1;
		} while (x != u);
	}

	return mn;
}
