#include <stdio.h>
#include <vector>
#include <set>

#define N 100100
#define M 100100

using namespace std;

int n, m;
int from[M << 1], to[M << 1], next[M << 1];
int head[N];
bool Artic[N];

int dt[N], low[N], dtime;

int S[M << 1], top;

struct Edge {
	int A, B;
	inline Edge (int a = 0, int b = 0) {
		if (a > b) A = b, B = a;
		else A = a, B = b;
	}
};

bool operator < (Edge a, Edge b) {
	if (a.A != b.A) return a.A < b.A;
	return a.B < b.B;
}

set <Edge> bcc[M];
int cnt;

void Init() {
	cnt = 0;
	for (int i = 1; i <= n; i ++) head[i] = 0;
	for (int i = 1; i <= n; i ++) Artic[i] = 0;

	for (int i = 1; i <= n; i ++) dt[i] = 0;
}

void AddEdge(int s, int e, int u) {
	from[u] = s, to[u] = e;
	next[u] = head[s], head[s] = u;
}

void DFS(int s, int p = 0) {
	dt[s] = low[s] = ++ dtime;
	for (int i = head[s]; i; i = next[i]) {
		int u = to[i];
		if (dt[u] < dt[s]) S[++ top] = i;
		if (!dt[u]) {
			DFS(u, s);
			low[s] = min(low[s], low[u]);
			if ((dt[s] == 1 && dt[u] > 2) ||
				(dt[s] > 1 && low[u] >= dt[s])) Artic[s] = 1;
			if (low[u] >= dt[s]) {
				bcc[++ cnt].clear();
				while (1) {
					int tp = S[top --];
					bcc[cnt].insert(Edge(from[tp], to[tp]));
					if (tp == i) break;
				}
			}
		} else if (u != p) low[s] = min(low[s], dt[u]);
	}
}

void BCC() {
	for (int i = 1; i <= n; i ++) if (!dt[i]) {
		dtime = top = 0;
		DFS(i);
	}
}

int main() {
	freopen ("Graph1.in", "r", stdin);
	freopen ("Graph1.out", "w", stdout);
	scanf("%d %d", &n, &m);
	Init();
	for (int i = 1; i <= m; i ++) {
		int j, k;
		scanf("%d %d", &j, &k);
		AddEdge(j, k, i);
		AddEdge(k, j, i + m);
	}

	BCC();

	printf("Articulation Points:");
	for (int i = 1; i <= n; i ++) if (Artic[i]) printf(" %d", i);
	puts("\n");

	printf("Biconnected Components: %d\n", cnt);
	for (int i = 1; i <= cnt; i ++) {
		for (set <Edge>::iterator it = bcc[i].begin(); it != bcc[i].end(); it ++) {
			Edge e = *it;
			printf("{%d,%d} ", e.A, e.B);
		}
		puts("");
	}
}
