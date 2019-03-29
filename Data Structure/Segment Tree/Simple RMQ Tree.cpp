#include <cstdio>
#include <cstring>

#define N 100100
#define max(a, b) ((a) > (b) ? (a) : (b))

const int maxV = N << 1;
const int inf = (1 << 30);

class RMQ_Tree {

private:
	int Max[maxV];
	int n;

public:
	void build(int *a, int m) {
		Max[n = m] = a[n];
		for (int i = 1; i <= n; i ++) Max[i + n] = a[i];
		for (int i = n - 1; i; i --) Max[i] = max(Max[i << 1], Max[i << 1 | 1]);
	}

	void update(int p, int v) {
		Max[p += n] = v;
		for (; p > 1; p >>= 1) Max[p >> 1] = max(Max[p], Max[p ^ 1]);
	}

	int queryValue(int p) { return Max[p + n]; }

	int queryMax(int l, int r) {
		l += n, r += n;
		int rlt = -inf;
		for (; l <= r; l = (l + 1) >> 1, r = (r - 1) >> 1) {
			if (l & 1) rlt = max(rlt, Max[l]);
			if ((r & 1) == 0) rlt = max(rlt, Max[r]);
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
		int l, r, x;
		scanf("%s %d", s, &l);
		if (!strcmp(s, "update")) {
			scanf("%d", &x);
			T.update(l, x);
		} else {
			scanf("%d", &r);
			printf("%d\n", T.queryMax(l, r));
		}
	}
}
