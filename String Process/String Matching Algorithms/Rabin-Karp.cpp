#include <cstdio>
#include <memory.h>

typedef __int64 INT;

const int L = 100010;
const int SZ = 238829;
const int ModA = 984847773;	//505843009213693951LL, 586543
const int ModB = 984847771;	//505843009213693973LL, 473457

const int SIGMA = 26;

INT powA[L], powB[L];

int hchk[SZ];
int hlen[SZ];
INT hvalA[SZ], hvalB[SZ];

void init() {
	memset(hchk, 0, sizeof(hchk));
}

void preprocess() {
	powA[0] = powB[0] = 1;
	for(int i = 1; i < L; i ++) {
		powA[i] = powA[i - 1] * SIGMA % ModA;
		powB[i] = powB[i - 1] * SIGMA % ModB;
	}
}

inline int findpos(int n, INT vA, INT vB) { return (234524352LL * n + vA % SZ * 63345 + vB) % SZ; }

void insert(int id, int n, INT vA, INT vB) {
	int i;
	for (i = findpos(n, vA, vB); hchk[i] && (hlen[i] != n || hvalA[i] !=vA || hvalB[i] != vB); ) {
		i ++;
		if (i == SZ) i = 0;
	}
	hchk[i] = id + 1;
	hlen[i] = n;
	hvalA[i] = vA;
	hvalB[i] = vB;
}

int find(int n, INT vA, INT vB){
	int i;
	for(i = findpos(n, vA, vB); hchk[i] && (hlen[i] != n || hvalA[i] != vA || hvalB[i] != vB); ) {
		i ++;
		if (i == SZ) i = 0;
	}
	return hchk[i];
}

void insert(int id, char *t) {
	int n = strlen(t);
	INT tmpA = 0, tmpB = 0;
	for (int i = 0; i < n; i ++) {
		tmpA = (tmpA * SIGMA + t[i] - 'a') % ModA;
		tmpB = (tmpB * SIGMA + t[i] - 'a') % ModB;
	}
	insert(id, n, tmpA, tmpB);
}

int find(char *t, int len, int *cnt) {
	int n = strlen(t);
	int ret = 0;
	INT sumA = 0, sumB = 0;
	for (int i = 0; i + len <= n; i ++) {
		if (!i) {
			for (int j = 0; j < len; j ++) {
				sumA = (sumA * SIGMA + t[j] - 'a') % ModA;
				sumB = (sumB * SIGMA + t[j] - 'a') % ModB;
			}
		} else {
			sumA -= powA[len - 1] * (t[i - 1] - 'a') % ModA; if (sumA < 0) sumA += ModA;
			sumB -= powB[len - 1] * (t[i - 1] - 'a') % ModB; if (sumB < 0) sumB += ModB;
			sumA = (sumA * SIGMA + t[i + len - 1] - 'a') % ModA;
			sumB = (sumB * SIGMA + t[i + len - 1] - 'a') % ModB;
		}
		int id = find(len, sumA, sumB);
		if (id) {
		//	(id-1)th pattern exists in the range t[i, ... , i+len-1]
			cnt[id - 1] ++;
			ret ++;
		}
	}
	return ret;
}

int cnt[L];
char P[L];
char T[L];

int main() {
	int n;
	preprocess();
	while (scanf("%d", &n) > 0) {
		init();
		for (int i = 0; i < n; i ++) {
			scanf("%s", P);
			insert(i, P);
			cnt[i] = 0;
		}
		scanf("%s", T);
		find(T, 3, cnt);
		for (int i = 0; i < n; i ++) {
			printf("Pattern %d occurs in the text %d times.\n", i, cnt[i]);
		}
		puts("");
	}
}
