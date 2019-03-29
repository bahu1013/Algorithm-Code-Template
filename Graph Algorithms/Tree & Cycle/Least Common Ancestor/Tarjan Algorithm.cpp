#include <stdio.h>
#include <math.h>
#define N 200010
#define LOG 21

int head[N];
int next[N << 1], to[N << 1];

int n, rt;
int dt[N], pos[N];
int r[N << 1], Q[LOG][N << 1];

int dtime, cnt;

void DFS(int u) {
	dt[u] = ++ dtime;
	pos[u] = ++ cnt, r[cnt] = u;
	for (int i = head[u]; i; i = next[i]) {
		int v = to[i];
		if (!dt[v]) r[++ cnt] = u, DFS(v);
	}
}

void preLCA() {
	int i, j, a, b;
	for (int i = 1; i <= cnt; i ++) Q[0][i] = r[i];
	for (int i = 1; (1 << i) < cnt; i ++){
		for (int j = 1; j + (1 << i) - 1 <= cnt; j ++){
			a = Q[i - 1][j], b = Q[i - 1][j + (1 << (i - 1))];
			Q[i][j] = dt[a] < dt[b] ? a : b;
		}
	}
}

int LCA(int x, int y){
	x=pos[x], y=pos[y];
	if (x > y) x ^= y ^= x ^= y;
	int d = y - x, i;
	for (i = 0; (1 << (i + 1)) <= d; i ++);
	int a = Q[i][x], b = Q[i][y - (1 << i) + 1];
	return dt[a] < dt[b] ? a : b;
}

void Init() {
	dtime = cnt = 0;
	for (int i = 1; i <= n; i ++) {
		dt[i] = 0;
		head[i] = 0;
	}
}

inline void AddEdge(int s, int e, int m) { to[m] = e, next[m] = head[s], head[s] = m; }

int main() {
	int q;
	scanf("%d", &n);
	Init();
	for (int m = 0, i = 1, j, k; i<n; i++) {
		scanf("%d %d", &j, &k);
		AddEdge(j, k, ++ m);
		AddEdge(k, j, ++ m);
	}
	scanf("%d", &rt);
	DFS(rt);
	preLCA();
	for (scanf("%d", &q); q--; ) {
		int i, j;
		scanf("%d %d", &i, &j);
		printf("%d\n", LCA(i, j));
	}
	return 0;
}
