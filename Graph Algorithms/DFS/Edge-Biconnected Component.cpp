#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>

#define N 100100
#define M 100100

using namespace std;

typedef pair <int, int> pii;

int n, m;
int to[M << 1], next[M << 1];
int head[N];

int dtime, dt[N], low[N];
int S[N], top;
pii Bridge[M];
int ArtP[N];
int cA, cB;
vector <int> Ebcc[N];
int cnt;

bool vis[M];

inline int EID(int e) { return e > m ? e - m : e; }

void Init() {
	cA = cB = cnt = 0;
	for (int i = 1; i <= n; i ++) head[i] = 0;
	for (int i = 1; i <= n; i ++) dt[i] = low[i] = 0;
	for (int i = 1; i <= m; i ++) vis[i] = 0;
}

void AddEdge(int s, int e, int u) {
	to[u] = e;
	next[u] = head[s], head[s] = u;
}

void DFS(int u) {
	dt[u] = low[u] = ++ dtime;
	S[++ top] = u;
	int sz = 0;
	bool Artic = 0;
	for (int i = head[u]; i; i = next[i]) {
		int v = to[i];
		if (vis[EID(i)]) continue;
		vis[EID(i)] = 1;
		if (dt[v]) low[u] = min(low[u], dt[v]);
		else {
			DFS(v);
			low[u] = min(low[u], low[v]);

			Artic |= low[v] >= dt[u], sz ++;						//ArtPoint
			if (low[v] > dt[u]) Bridge[++ cB] = make_pair(u, v);	//Bridge
		}
	}

	if (dt[u] == 1) Artic = sz > 1;		//ArtPoint
	if (Artic) ArtP[++ cA] = u;			//ArtPoint

	if (low[u] == dt[u]) {				//EBCC
		Ebcc[++ cnt].clear();
		int x;
		do {
			x = S[top --];
			Ebcc[cnt].push_back(x);
		} while (x != u);
	}
}

void Tarjan() {
	for (int i = 1; i <= n; i ++) if (!dt[i]) {
		dtime = top = 0;
		DFS(i);
	}
}

int main() {
//	freopen ("in.txt", "r", stdin);
	while (scanf("%d %d", &n, &m) > 0) {
		Init();
		for (int i = 1; i <= m; i ++) {
			int j, k;
			scanf("%d %d", &j, &k);
			AddEdge(j, k, i);
			AddEdge(k, j, i + m);
		}

		Tarjan();
		printf("ArtPoints are: %d\n", cA);
		sort(ArtP + 1, ArtP + cA + 1);
		for (int i = 1; i <= cA; i ++) printf("%d ", ArtP[i]); puts("\n");
		printf("Bridges are: %d\n", cB);
		for (int i = 1; i <= cB; i ++) printf("{%d,%d}\n", Bridge[i].first, Bridge[i].second); puts("\n");
		printf("BCC count: %d\n", cnt);
		for (int i = 1; i <= cnt; i ++) {
			for (int j = 0; j < Ebcc[i].size(); j ++) printf("%d ", Ebcc[i][j]); puts("");
		}
		puts("");
	}
}
