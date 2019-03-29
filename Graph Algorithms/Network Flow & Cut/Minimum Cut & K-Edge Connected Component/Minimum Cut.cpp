//Stoer-Wagner Algorithm
//O(n ^ 3)

#include <cstdio>
#include <vector>
#include <memory.h>

#define N 110

using namespace std;

typedef vector <int> VI;

const int inf = (1 << 30);

int G[N][N];
bool vis[N], C[N], chkA[N];
int dis[N];
int node[N], S[N];
int cnt, s, t;
VI VS[N];
VI A, B;

int Prim(int n) {

	memset(vis, 0, sizeof(vis));
	memset(dis, 0, sizeof(dis));
	int minCut = 0, top = 0;

	for (int i = 0; i < cnt; i ++) {
		int Max = -inf, p;
		for (int j = 0; j < cnt; j ++) {
			int u = node[j];
			if (!C[u] && !vis[u] && dis[u] > Max) {
				p = u;
				Max = dis[u];
			}
		}
		S[top ++] = p;
		vis[p] = true;
		if (i == cnt - 1) minCut = dis[p];
		for (int j = 0; j < cnt; j ++) {
			int u = node[j];
			if (!C[u] && !vis[u]) dis[u] += G[p][u];
		}
	}

	s = S[top - 2];
	t = S[top - 1];
	for (int i = 0; i < top; i ++) node[i] = S[i];

	return minCut;
}

int Stoer_Wagner(int n) {
/*
	Node :	0, 1, ... , n - 1;
	Edge :	if (i and j are adjacent with weight w) then g[i][j] = w;
			else if (i and j are not adjacent) g[i][j] = 0;
*/
	for (int i = 0; i < n; i ++) {
		VS[i].clear();
		VS[i].push_back(i);
	}

	int rlt = inf;
	memset(C, 0, sizeof(C));
	for (int i = 0; i < n; i ++) node[i] = i;

	for (int i = 1; i < n; i ++) {
		cnt = n - i + 1;
		int cur = Prim(n);
		if (cur < rlt){
			rlt =cur;
			for (int j = 0; j < n; j ++) chkA[j] = 0;
			for (int j = 0; j < VS[t].size(); j ++) chkA[VS[t][j]] = 1;
		}
		C[t] = true;

		//merge s and t
		for (int j = 0; j < VS[t].size(); j ++) VS[s].push_back(VS[t][j]);
		for (int j = 0; j < n; j ++) {
			if (j == s) continue;
			if (!C[j]) {
				G[s][j] += G[t][j];
				G[j][s] += G[j][t];
			}
		}
	}

	A.clear();
	B.clear();
	for (int i = 0; i < n; i ++) {
		if (chkA[i]) A.push_back(i);
		else B.push_back(i);
	}
	return rlt;
}

int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) > 0) {
		memset(G, 0, sizeof(G));
		while (m --) {
			int u, v, w;
			scanf("%d %d %d", &u, &v, &w);
			u --, v --;
			G[u][v] += w;
			G[v][u] += w;
		}
		printf("%d\n", Stoer_Wagner(n));
	}
	return 0;
}
