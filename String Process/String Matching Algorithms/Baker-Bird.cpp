#include <cstdio>
#include <queue>
#include <memory.h>

using namespace std;

const int N = 2000, M = 200;
const int SIGMA = 256, SZ = M * M * SIGMA;

struct baker_bird {

	int size, *next[SZ];
	int link[SZ];

	int t[N][N], p[M][M];
	int fail[M];

	int ph, pw;

	int add_node(){
		next[size] = new int[SIGMA];
		fill(next[size], next[size] + SIGMA, -1);
		link[size] = -1;
		return size ++;
	}

	#define TRANSFORM(t, h, w) { \
		for (int q = 0; q < h; q ++) { \
			int cur = 0; \
			for (int i = 0; i < w; ++i) { \
				int a = t[q][i]; \
				while (next[cur][a] < 0) cur = link[cur]; \
				cur = next[cur][a]; \
				t[q][i] = cur; \
			} \
		} \
	}

	void init() {
		size = 0;
		add_node();
	}

	void PatternProcess() {
	//	Horizontal Aho-Corasick, Vertical Knuth-Morris-Pratt
		for (int i = 0; i < ph; i ++) {
			int cur = 0;
			for (int j = 0; j < pw; j ++) {
				int c = p[i][j];
				if (next[cur][c] < 0) next[cur][c] = add_node();
				cur = next[cur][c];
			}
		}

		queue <int> Q;
		for (int a = 0; a < SIGMA; a ++) {
			if (next[0][a] >= 0) {
				link[next[0][a]] = 0;
				Q.push(next[0][a]);
			} else next[0][a] = 0;
		}

		while (!Q.empty()) {
			int cur = Q.front(); Q.pop();
			for (int a = 0; a < SIGMA; a ++) {
				if (next[cur][a] >= 0) {
					Q.push(next[cur][a]);
					int r = link[cur];
					while (next[r][a] < 0) r = link[r];
					link[next[cur][a]] = next[r][a];
				}
			}
		}

		TRANSFORM(p, ph, pw);

		fill(fail, fail + ph + 1, -1);
		for (int i = 0, j = -1; i < ph; ) {
			while (j >= 0 && p[i][pw - 1] != p[j][pw - 1]) j = fail[j];
			i ++, j ++;
			if (i < ph && j < ph && p[i][pw - 1] == p[j][pw - 1]) fail[i] = fail[j];
			else fail[i] = j;
		}
	}

	int Run(int h, int w) {
		TRANSFORM(t, h, w);
		int ret = 0;
		for (int j = 0; j < w; j ++) {
			for (int i = 0, k = 0; i < h; i ++) {
				while (k >= 0 && p[k][pw - 1] != t[i][j]) k = fail[k];
				if (++ k >= ph) {
					ret ++;
				//	Pattern occurs in the range [i-ph+1, j-pw+1] ~ [i, j]
					k = fail[k];
				}
			}
		}
		return ret;
	}

	void build(char P[][M], int h, int w) {
		init();
		for (int i = 0; i < h; i ++)
			for (int j = 0; j < w; j ++) p[i][j] = P[i][j];
		ph = h, pw = w;
		PatternProcess();
	}

	int find(char T[][N], int h, int w) {
		for (int i = 0; i < h; i ++)
			for (int j = 0; j < w; j ++) t[i][j] = T[i][j];
		return Run(h, w);
	}
} base;

char T[N][N], P[M][M];

int main() {
	int h, w;

	scanf("%d %d", &h, &w);
	for (int i = 0; i < h; i ++) scanf("%s", P[i]);
	base.build(P, h, w);

	while (scanf("%d %d", &h, &w) > 0) {
		for (int i = 0; i < h; i ++) scanf("%s", T[i]);
		printf("%d\n", base.find(T, h, w));
	}
}
