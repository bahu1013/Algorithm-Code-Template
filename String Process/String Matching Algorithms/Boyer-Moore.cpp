#include <cstdio>
#include <cstring>
#include <algorithm>

#define L 100100
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

using namespace std;

char p[L];
int m;

int g[L], next[L], skip[L];

void compile() {
	fill(g, g + m, m);
	for (int i = 0; i < m; i ++) skip[p[i]] = m - i - 1;
	for (int i = 0; i < m; i ++) next[i] = (m << 1) - i - 1;
	int j = m;
	for (int k = m - 1; k >= 0; k --, j --) {
		g[k] = j;
		while (j < m && p[j] != p[k]) {
			next[j] = min(next[j], m - k - 1);
			j = g[j];
		}
	}
	for (int k = 0, s = j; k < m; k ++) {
		next[k] = min(next[k], s + m - k);
		if (k >= s) s = g[s];
	}
}

int match(char *t) {
	int ret = 0, n = strlen(t);
	for (int i = m - 1; i < n; ) {
		int j = m - 1;
		while (j >= 0 && t[i] == p[j]) i --, j --;
		if (j < 0) {
		//	match at t[i+1 ... i+m]
			ret ++;
			i += m + 1;
		} else i += max(skip[t[i]], next[j]);
	}
	return ret;
}

char t[L];

int main() {
	strcpy(p, "aaba");
	m = strlen(p);
	compile();

	strcpy(t, "aabaabababbaabaabaaba");
	printf("%d\n", match(t));
}
