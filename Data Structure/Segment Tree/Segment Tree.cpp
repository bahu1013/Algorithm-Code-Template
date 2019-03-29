#include <stdio.h>
#include <algorithm>
#include <string.h>
#define max(a, b) ((a) > (b) ? (a) : (b))
#define N 100100

using namespace std;

typedef __int64 ll;

ll addv[N << 2];
ll Max[N << 2];
ll setv[N << 2];
bool setted[N << 2];
ll a[N];
ll sum[N << 2];
const ll inf = (1LL << 60);

inline int left(int id) { return id << 1; }
inline int right(int id) { return id << 1 | 1; }

void push_up(int id) {
	Max[id] = max(Max[left(id)], Max[right(id)]);
	sum[id] = sum[left(id)] + sum[right(id)];
}

void push_down(int id, int len) {
	if (setted[id]) {
		sum[left(id)] = 1LL * setv[id] * (len - len / 2);
		sum[right(id)] = 1LL * setv[id] * (len / 2);
		Max[left(id)] = setv[id];
		Max[right(id)] = setv[id];
		setv[left(id)] = setv[right(id)] = setv[id];
		setted[left(id)] = setted[right(id)] = 1;
		addv[left(id)] = addv[right(id)] = 0;
		setted[id] = 0;
	} else if (addv[id]) {
		sum[left(id)] += 1LL * addv[id] * (len - len / 2);
		sum[right(id)] += 1LL * addv[id] * (len / 2);
		Max[left(id)] += addv[id];
		Max[right(id)] += addv[id];
		if (setted[left(id)]) setv[left(id)] += addv[id];
		else addv[left(id)] += addv[id];
		if (setted[right(id)]) setv[right(id)] += addv[id];
		else addv[right(id)] += addv[id];
		addv[id] = 0;
	}
}

void build(int l, int r, int id) {
	addv[id] = 0;
	setted[id] = 0;
	if (l == r) {
		sum[id] = Max[id] = a[l];
		setv[id] = a[l];
		setted[id] = 1;
		return;
	}
	int m = (l + r) >> 1;
	build(l, m, left(id));
	build(m + 1, r, right(id));
	push_up(id);
}

void updateAdd(int L, int R, ll v, int l, int r, int id) {
	if (L <= l && r <= R) {
		sum[id] += 1LL * v * (r - l + 1);
		Max[id] += v;
		if (setted[id]) setv[id] += v;
		else addv[id] += v;
		return;
	}
	push_down(id, r - l + 1);
	int m = (l + r) >> 1;
	if (L <= m) updateAdd(L, R, v, l, m, left(id));
	if (m < R) updateAdd(L, R, v, m + 1, r, right(id));
	push_up(id);
}

void updateSet(int L, int R, ll v, int l, int r, int id) {
	if (L <= l && r <= R) {
		sum[id] = 1LL * v * (r - l + 1);
		Max[id] = v;
		setv[id] = v;
		setted[id] = 1;
		addv[id] = 0;
		return;
	}
	push_down(id, r - l + 1);
	int m = (l + r) >> 1;
	if (L <= m) updateSet(L, R, v, l, m, left(id));
	if (m < R) updateSet(L, R, v, m + 1, r, right(id));
	push_up(id);
}

ll getMax(int L, int R, int l, int r, int id) {
	if (L <= l && r <= R) return Max[id];
	push_down(id, r - l + 1);
	int m = (l + r) >> 1;
	ll ret = -inf;
	if (L <= m) {
		ll tp = getMax(L, R, l, m, left(id));
		if (ret < tp) ret = tp;
	}
	if (m < R) {
		ll tp = getMax(L, R, m + 1, r, right(id));
		if (ret < tp) ret = tp;
	}
	return ret;
}

ll getSum(int L, int R, int l, int r, int id) {
	if (L <= l && r <= R) return sum[id];
	push_down(id, r - l + 1);
	int m = (l + r) >> 1;
	ll ret = 0;
	if (L <= m) ret += getSum(L, R, l, m, left(id));
	if (m < R) ret += getSum(L, R, m + 1, r, right(id));
	return ret;
}

int main() {
	int n, q;
	scanf("%d %d", &n, &q);
	for (int i = 1; i <= n; i ++) scanf("%I64d", a + i);
	build(1, n, 1);
	while (q--) {
		char s[10];
		int L, R;
		scanf("%s %d %d", s, &L, &R);
		if (!strcmp(s, "addValue")) {
			ll v;
			scanf("%I64d", &v);
			updateAdd(L, R, v, 1, n, 1);
		} else if (!strcmp(s, "setValue")) {
			ll v;
			scanf("%I64d", &v);
			updateSet(L, R, v, 1, n, 1);
		} else if (!strcmp(s, "getMax")) {
			printf("%I64d\n", getMax(L, R, 1, n, 1));
		} else { // if (!strcmp(s, "getSum")) {
			printf("%I64d\n", getSum(L, R, 1, n, 1));
		}
	}
}
