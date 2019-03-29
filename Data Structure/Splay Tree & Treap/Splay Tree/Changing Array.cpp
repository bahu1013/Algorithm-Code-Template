//POJ 3580
#include <cstdio>
#include <cstring>

#define N 200005
#define min(a, b) ((a) < (b) ? (a) : (b))

int size[N], tot;
int son[N][2], pa[N];
int addv[N], revv[N];
int val[N], min[N];

int a[N];

int new_node(int v = 0) {
	size[++ tot] = 1;
	son[tot][0] = son[tot][1] = pa[tot]=0;
	addv[tot] = revv[tot] = 0;
	val[tot] = min[tot] = v;
	return tot;
}
//--- Start Assistant Functions ---//
inline void Set(int p, int x, int d) {
	if (p) son[p][d] = x;
	if (x) pa[x] = p;
}

inline int Dir(int x) { return x == son[pa[x]][1]; }

void updateP(int p, int x) {
	if (!x) return;
	size[p] += size[x];
	min[p] = min(min[p], min[x]);
}

void push_up(int rt) {
	if (!rt) return;
	size[rt] = 1;
	min[rt] = val[rt];
	updateP(rt, son[rt][0]);
	updateP(rt, son[rt][1]);
}

void Rev(int rt) {
	if (!rt) return;
	int l = son[rt][0], r = son[rt][1];
	son[rt][0] = r;
	son[rt][1] = l;
	revv[rt] ^= 1;
}

void AddDelta(int rt, int v) {
	addv[rt] += v;
	val[rt] += v;
	min[rt] += v;
}

void push_down(int rt) {
	int l = son[rt][0], r = son[rt][1];
	if (addv[rt]) {
		AddDelta(l, addv[rt]);
		AddDelta(r, addv[rt]);
		addv[rt]=0;
	}
	if (revv[rt]) {
		Rev(l);
		Rev(r);
		revv[rt]=0;
	}
}
//--- End Assistant Functions ---//
//--- Start Main Splay Tree ---//
int build(int l, int r) {
	if (l > r) return 0;
	int m = (l + r) >> 1;
	int t = new_node(a[m]);
	Set(t, build(l, m - 1), 0);
	Set(t, build(m + 1, r), 1);
	push_up(t);
	return t;
}

int find(int rt, int pos) {
	if (pos < 0 || pos >= size[rt]) return 0;
	while (1) {
		push_down(rt);
		if (size[son[rt][0]] + 1 == pos) return rt;
		if (pos <= size[son[rt][0]]) rt = son[rt][0];
		else pos -= size[son[rt][0]] + 1, rt = son[rt][1];
	}
	return 0;
}

void rot(int x) {
	int p = pa[x];

	push_down(p);
	push_down(x);

	bool d = Dir(x);
	Set(p, son[x][!d], d);
	Set(pa[p], x, Dir(p));
	Set(x, p, !d);

	push_up(p);
//	if (p == root) root = x;
}

void splay(int x, int p = 0) {
	while (pa[x] != p) {
		if (pa[pa[x]] == p) rot(x);
		else {
			Dir(x) == Dir(pa[x]) ? rot(pa[x]) : rot(x);
			rot(x);
		}
	}
	push_up(x);
}

int pred(int t) {
	splay(t);
	for (t = son[t][0]; son[t][1]; t = son[t][1]);
	return t;
}

int succ(int t) {
	splay(t);
	for (t = son[t][1]; son[t][0]; t = son[t][0]);
	return t;
}
//--- End Main Splay Tree ---//
//--- Start Operations ---//
void print(int rt, int dp = 0) {
	if (!rt) return;
	push_down(rt);
	print(son[rt][0], dp + 1);
	printf("%d ", val[rt]);
	print(son[rt][1], dp + 1);
	if (!dp) puts("");
}

int add(int l, int r, int v, int rt) {
	int tp;
	tp = find(rt, l - 1), splay(tp), rt = tp;
	tp = find(rt, r + 1), splay(tp, rt);

	AddDelta(son[tp][0], v);

	push_up(tp), push_up(rt);
	return rt;
}

int reverse(int l, int r, int rt) {
	int tp;
	tp = find(rt, l - 1), splay(tp), rt = tp;
	tp = find(rt, r + 1), splay(tp, rt);

	Rev(son[tp][0]);

	push_up(tp), push_up(rt);
	return rt;
}

int insert(int l, int v, int rt) {
	int tp;
	tp = find(rt, l), splay(tp), rt = tp;
	tp = find(rt, l + 1), splay(tp, rt);

	Set(tp, new_node(v), 0);

	push_up(tp), push_up(rt);
	return rt;
}

int remove(int l, int r, int &rt) {
	int tp;
	tp = find(rt, l - 1), splay(tp), rt = tp;
	tp = find(rt, r + 1), splay(tp, rt);

	int fuck = son[tp][0];
	Set(tp, 0, 0);

	push_up(tp), push_up(rt);
	return fuck;
}

int revolve(int l, int r, int v, int rt) {
	int t = remove(l, r - v, rt), tp;
	tp = find(rt, v + l - 1), splay(tp, 0), rt = tp;
	tp = find(rt, v + l), splay(tp, rt);

	Set(tp, t, 0);

	push_up(tp), push_up(rt);
	return rt;
}

int query(int l, int r, int &rt) {
	int tp;
	tp = find(rt, l - 1), splay(tp), rt = tp;
	tp = find(rt, r + 1), splay(tp, rt);

	return min[son[tp][0]];
}
//--- End Operations ---//

char s[10];

int main() {
	int n, q;

	scanf("%d", &n);
	for (int i = 1; i <= n; i ++) scanf("%d", a + i);
	tot = 0;
	int rt = build(0, n + 1);
	for (scanf("%d", &q); q --; ) {
		scanf("%s", s);
		int l, r, v;
		if (!strcmp(s, "ADD")) {
			scanf("%d %d %d", &l, &r, &v);
			rt = add(l + 1, r + 1, v, rt);
		} else if (!strcmp(s, "REVERSE")) {
			scanf("%d %d", &l, &r);
			rt=reverse(l + 1, r + 1, rt);
		} else if (!strcmp(s, "REVOLVE")) {
			scanf("%d %d %d", &l, &r, &v);
			v %= r - l + 1;
			rt = revolve(l + 1, r + 1, v, rt);
		} else if (!strcmp(s, "INSERT")) {
			scanf("%d %d", &l, &v);
			rt = insert(l + 1, v, rt);
		} else if (!strcmp(s, "DELETE")) {
			scanf("%d", &l);
			remove(l + 1, l + 1, rt);
		} else {
			scanf("%d %d", &l, &r);
			printf("%d\n", query(l + 1, r + 1, rt));
		}
	}
}
