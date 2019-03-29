#include <cstdio>
#include <cstring>

#define N 100100

typedef __int64 INT;

const int maxV = N << 1;
const INT inf = (1LL << 60);

inline INT MIN(INT a, INT b) { return a < b ? a : b; }
inline INT MAX(INT a, INT b) { return a > b ? a : b; }

class Winner_Tree {

private:
	INT addv[maxV], setv[maxV];
	bool setted[maxV];

	INT sum[maxV], max[maxV];
	int len[maxV];

	int n;

	void init() {
		for (int i = 1; i <= n + n; i ++) {
			addv[i] = setv[i] = 0;
			setted[i] = 0;
		}
	}

	inline INT Sum(int p) { return addv[p] ? sum[p] + addv[p] * len[p] : setted[p] ? setv[p] * len[p] : sum[p]; }
	inline INT Max(int p) { return addv[p] ? max[p] + addv[p] : setted[p] ? setv[p] : max[p]; }

	void push_up(int p) {
		for (int i = p; i > 1; i >>= 1) {
			sum[i >> 1] = Sum(i) + Sum(i ^ 1);
			max[i >> 1] = MAX(Max(i), Max(i ^ 1));
		}
	}

	void push_down(int p) {
		int dp;
		for (dp = 0; (p >> dp); dp ++);
		for (dp -= 2; dp >= 0; dp --) {
			int x = p >> dp;
			sum[x >> 1] = Sum(x >> 1);
			max[x >> 1] = Max(x >> 1);
			if (addv[x >> 1]) {
				if (setted[x]) setv[x] += addv[x >> 1];
				else addv[x] += addv[x >> 1];
				if (setted[x ^ 1]) setv[x ^ 1] += addv[x >> 1];
				else addv[x ^ 1] += addv[x >> 1];
				addv[x >> 1] = 0;
			}
			if (setted[x >> 1]) {
				setted[x] = setted[x ^ 1] = 1;
				setv[x] = setv[x ^ 1] = setv[x >> 1];
				addv[x] = addv[x ^ 1] = 0;
				setted[x >> 1] = 0;
			}
		}
	}

public:
	void build(int *a, int m) {
		n = m;
		init();

		for (int i = 1; i <= n; i ++) {
			sum[i + n] = max[i + n] = a[i];
			len[i + n] = 1;
		}
		sum[n] = max[n] = a[n];
		len[n] = 1;

		for (int i = n - 1; i; i --) {
			sum[i] = sum[i << 1] + sum[i << 1 | 1];
			max[i] = MAX(max[i << 1], max[i << 1 | 1]);
			len[i] = len[i << 1] + len[i << 1 | 1];
		}
	}

	void Add(int l, int r, INT v) {
		l += n, r += n;
		push_down(l), push_down(r);

		int L = -1, R = -1;
		for (; l <= r; l = (l + 1) >> 1, r = (r - 1) >> 1) {
			if (l & 1) {
				if (setted[l]) setv[l] += v;
				else addv[l] += v;
				if (L == -1) L = l;
			}
			if ((r & 1) == 0) {
				if (setted[r]) setv[r] += v;
				else addv[r] += v;
				if (R == -1) R = r;
			}
		}

		push_up(L), push_up(R);
	}

	void Set(int l, int r, INT v) {
		l += n, r += n;
		push_down(l), push_down(r);

		int L = -1, R = -1;
		for (; l <= r; l = (l + 1) >> 1, r = (r - 1) >> 1) {
			if (l & 1) {
				setv[l] = v, setted[l] = 1;
				addv[l] = 0;
				if (L == -1) L = l;
			}
			if ((r & 1) == 0) {
				setv[r] = v, setted[r] = 1;
				addv[r] = 0;
				if (R == -1) R = r;
			}
		}

		push_up(L), push_up(R);
	}

	INT querySum(int l, int r) {
		l += n, r += n;
		push_down(l), push_down(r);

		INT rlt = 0;
		for (; l <= r; l = (l + 1) >> 1, r = (r - 1) >> 1) {
			if (l & 1) rlt += Sum(l);
			if ((r & 1) == 0) rlt += Sum(r);
		}
		return rlt;
	}

	INT queryMax(int l, int r) {
		l += n, r += n;
		push_down(l), push_down(r);

		INT rlt = -inf;
		for (; l <= r; l = (l + 1) >> 1, r = (r - 1) >> 1) {
			if (l & 1) rlt = MAX(rlt, Max(l));
			if ((r & 1) == 0) rlt = MAX(rlt, Max(r));
		}
		return rlt;
	}
} T;

int a[N];

int main() {
	int n, q;
	scanf("%d %d", &n, &q);
	for (int i = 1; i <= n; i ++) scanf("%d", a + i);
	T.build(a, n);
	while (q --) {
		char s[20];
		int l, r;
		INT v;
		scanf("%s", s);
		if (!strcmp(s, "addValue")) {
			scanf("%d %d %I64d", &l, &r, &v);
			T.Add(l, r, v);
		} else if (!strcmp(s, "setValue")) {
			scanf("%d %d %I64d", &l, &r, &v);
			T.Set(l, r, v);
		} else if (!strcmp(s, "getMax")) {
			scanf("%d %d", &l, &r);
			printf("%I64d\n", T.queryMax(l, r));
		} else { // if (!strcmp(s, "getSum")) {
			scanf("%d %d", &l, &r);
			printf("%I64d\n", T.querySum(l, r));
		}
	}
}
