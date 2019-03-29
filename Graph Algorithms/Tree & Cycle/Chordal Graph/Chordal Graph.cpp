#include <cstdio>
#include <memory.h>

#define N 1010

int n, deg[N];
bool con[N][N], chk[N];
int PEO[N];

bool Chordal() {
	memset(chk, 0, sizeof(chk));
	memset(deg, 0, sizeof(chk));

	for (int k = 1; k <= n; k ++) {
		int u = 0, j = 0;

		for (int i = 1; i <= n; i ++)
			if (!chk[i] && (!j || deg[i] > deg[j])) j = i;

		PEO[k] = j;
		chk[j] = true;

		for (int i = k - 1; i >= 1; i --) if (con[j][PEO[i]]) {
			if (!u) u = PEO[i];
			else if (!con[PEO[i]][u]) return false;
		}

		for (int i = 1; i <= n; i ++)
			if (!chk[i] && con[j][i]) deg[i] ++;
	}

	return true;
}

main() {
	int m;

	while (scanf("%d %d", &n, &m) && n) {

		for (int i = 1; i <= n; i ++)
			for (int j = 1; j <= n; j ++)
				con[i][j] = 0;

		while (m --) {
			int i, j;
			scanf("%d%d", &i, &j);
			con[i][j] = con[j][i] = 1;
		}

		if (Chordal()) printf("This is Chordal.\n\n");
		else printf("This isn't Chordal.\n\n");
	}
}
