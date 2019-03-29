#include <stdio.h>
#include <math.h>
#define max(a, b) ((a)>(b)?(a):(b))
#define N 200010
#define LOG 21

int n, rt;
int head[N];
int next[N << 1], to[N << 1];

int dp[N], p[N];
int P[LOG][N];

void Init() {
	for (int i = 1; i <= n; i ++) {
		p[i] = 0;
		dp[i] = 0;
		head[i] = 0;
	}
}

inline void AddEdge(int s, int e, int m) { to[m] = e, next[m] = head[s], head[s] = m; }

int Q[N], h, t;

void preLCA(int u) {
	h = 1, t = 0;
	dp[u] = 1, Q[++ t] = u;
	while (h <= t) {
		u = Q[h ++];

		for (int i = head[u]; i; i = next[i]) {
			int v = to[i];
			if (!dp[v]) {
				dp[v] = dp[p[v] = u] + 1;
				Q[++ t] = v;
			}
		}
	}

	for (int i = 1; i <= n; i ++) {
		P[0][i] = p[i];
		for (int j = 1; (1 << j) < n; j ++) P[j][i] = 0;
	}
	for (int j = 1; (1 << j) < n; j ++) for (int i = 1; i <= n; i ++) {
		P[j][i] = P[j - 1][P[j - 1][i]];
	}
}

int LCA(int i, int j) {
	int k;
	if (dp[i] < dp[j]) i ^= j ^= i ^= j;
	for (k = 0; (1 << k) <= dp[i]; k ++); k --;
	for (int u = k; u >= 0; u --) if (dp[i] - (1 << u) >= dp[j]) i = P[u][i];
	if (i != j) {
		for (int u = k; u >= 0; u --) if (P[u][i] != P[u][j]) i = P[u][i], j = P[u][j];
		i = p[i];
	}
	return i;
}

int main() {
	int q;
	scanf("%d", &n);
	Init();
	for (int m = 0, i = 1, j, k; i < n; i ++) {
		scanf("%d %d", &j, &k);
		AddEdge(j, k, ++ m);
		AddEdge(k, j, ++ m);
	}
	scanf("%d", &rt);
	preLCA(rt);
	for (scanf("%d", &q); q--; ) {
		int i, j;
		scanf("%d %d", &i, &j);
		printf("%d\n", LCA(i, j));
	}
	return 0;
}
