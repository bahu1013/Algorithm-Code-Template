#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

#define min(a, b) ((a) < (b) ? (a) : (b))

using namespace std;

const int L = 100100;

struct SuffixArray {
	#define LOG 21

	int wa[L], wb[L], ws[L], wv[L];
	int Rank[L], LCP[L], SA[L];
	int RMQ[LOG][L];

	inline int cmp(int *r, int i, int j, int l) { return r[i] == r[j] && r[i + l] == r[j + l]; }

	void build(int *r, int n, int m) {
		int *x = wa, *y = wb, *t;

		for (int i = 0; i < m; i ++) ws[i] = 0;
		for (int i = 0; i < n; i ++) ws[x[i] = r[i]] ++;
		for (int i = 1; i < m; i ++) ws[i] += ws[i - 1];
		for (int i = n - 1; i >= 0; i --) SA[-- ws[x[i]]] = i;

		for (int j = 1, p = 1; p < n; j <<= 1, m = p) {
			p = 0;
			for (int i = n - j; i < n ; i ++) y[p ++] = i;
			for (int i = 0; i < n; i ++) if (SA[i] >= j) y[p ++] = SA[i] - j;
			for (int i = 0; i < m; i ++) ws[i] = 0;
			for (int i = 0; i < n; i ++) ws[x[i]] ++;
			for (int i = 1; i < m; i ++) ws[i] += ws[i - 1];
			for (int i = n - 1; i >= 0; i --) SA[-- ws[x[y[i]]]] = y[i];
			t = x, x = y, y = t;
			x[SA[0]] = 0, p = 1;
			for (int i = 1; i < n; i ++) x[SA[i]] = cmp(y, SA[i - 1], SA[i], j) ? p - 1 : p ++;
		}

		int k = 0;
		for (int i = 0; i < n; i ++) Rank[SA[i]] = i;
		for (int i = 0; i < n - 1; LCP[Rank[i ++]] = k) {
			if (k) k --;
			for (int j = SA[Rank[i] - 1]; r[i + k] == r[j + k]; k ++);
		}
	}

	void initRMQ(int n) {
		for (int i = 1; i <= n; i ++) RMQ[0][i] = LCP[i];
		for (int i = 1; i < LOG; i ++)
			for (int j = 1; j + (1 << i) - 1 <= n; j ++)
				RMQ[i][j] = min(RMQ[i - 1][j], RMQ[i - 1][j + (1 << (i - 1))]);
	}

	int queryLCP(int l, int r) {
		l = Rank[l], r = Rank[r];
		if (l > r) swap(l, r);
		l ++;
		if (l == r) return RMQ[0][l];
		int k = r - l + 1, log;
		for (log = 0; (1 << log) <= k; log ++); log --;
		return min(RMQ[log][l], RMQ[log][r - (1 << log) + 1]);
	}
} Arr;

char s[L];
int r[L];

int main() {
	strcpy(s, "aabaabab");
	int len = strlen(s);
	for (int i = 0; i <= len; i ++) r[i] = s[i];
	Arr.build(r, len + 1, 256);
	//Suffix Array of string s
	for (int i = 0; i < len + 1; i ++) puts(s + Arr.SA[i]); puts("");
	for (int i = 1; i < len + 1; i ++) printf("LCP[%d] = %d\n", i, Arr.LCP[i]); puts("");
	//Calculate LCP of s[0,1,...,len-1] and s[3,4,...,len-1];
	Arr.initRMQ(len);
	printf("%d\n", Arr.queryLCP(0, 3));
}
