#include <cstdio>
#include <cstring>
#include <cstdlib>

#define N 200100
#define min(a, b) ((a) < (b) ? (a) : (b))

const int inf = 1 << 30;

struct treap {
	int size, prio;
	treap *l, *r;

	int val, Min;
	int addv;
	bool revv;
};

treap node[N];
int nodeC;

int getSize(treap* t) { return t ? t->size : 0; }
int getMin(treap* t) { return t ? t->Min : inf; }

void push_up(treap *t) {
	if (!t) return;
	t->size = getSize(t->l) + 1 + getSize(t->r);
	int lm = getMin(t->l), rm = getMin(t->r);
	t->Min = min(lm, rm), t->Min = min(t->Min, t->val);
}

void Rev(treap *t) {
	if (!t) return;
	treap *l = t->l, *r = t->r;
	t->l = r, t->r = l;
	t->revv ^= 1;
}

void AddDelta(treap *t, int v) {
	if (!t) return;
	t->addv += v;
	t->val += v;
	t->Min += v;
}

void push_down(treap *t) {
	if (!t) return;
	treap *l = t->l, *r = t->r;
	if (t->addv) {
		AddDelta(l, t->addv), AddDelta(r, t->addv);
		t->addv = 0;
	}
	if (t->revv) {
		Rev(l), Rev(r);
		t->revv = 0;
	}
}

treap* new_node(int v = 0) {
	treap *item = &node[nodeC ++];
	item->size = 1;
 	item->prio = (rand() << 15) + rand();

	item->val = v;
	item->Min = v;

	item->addv = item->revv = 0;
 	return item;
}

void merge(treap* &t, treap* l, treap* r) {
	push_down(l), push_down(r);
	if (!l) t = r;
	else if (!r) t = l;
	else if (l->prio < r->prio) merge(l->r, l->r, r), t = l;
	else merge(r->l, l, r->l), t = r;
	push_up(t);
}

void split(treap* t, treap* &l, treap* &r, int k) {
	push_down(t);
	if (!t) l = r = NULL;
	else if (k <= getSize(t->l)) split(t->l, l, t->l, k), r = t;
	else split(t->r, t->r, r, k- getSize(t->l) - 1), l = t;
	push_up(t);
}

void insert(treap* &t, treap* item, int k) {
	push_down(t);
	if (!t) t = item;
	else if (item->prio < t->prio) split(t, item->l, item->r, k), t = item;
	else if (k <= getSize(t->l)) insert(t->l, item, k);
	else insert(t->r, item, k - getSize(t->l) - 1);
	push_up(t);
}

void insert(treap* &root, int k, int v) {
	treap* item = new_node(v);
	insert(root, item, k);
}

void remove(treap* &t, int k) {
	push_down(t);
	if (k == getSize(t->l) + 1) merge(t, t->l, t->r);
	else if (k <= getSize(t->l)) remove(t->l, k);
	else remove(t->r, k - getSize(t->l) - 1);
	push_up(t);
}

void print(treap *t, int dp = 0) {
	if (!t) return;
	push_down(t);
	print(t->l, dp + 1);
	printf("%d ", t->val);
	print(t->r, dp + 1);
	if (!dp) puts("");
}

void add(treap *t, int l, int r, int v) {
	treap *a, *b, *c, *d;
	split(t, a, b, r);
	split(a, c, d, l - 1);

	AddDelta(d, v);

	merge(a, c, d);
	merge(t, a, b);
}

void reverse(treap *t, int l, int r) {
	treap *a, *b, *c, *d;
	split(t, a, b, r);
	split(a, c, d, l - 1);

	Rev(d);

	merge(a, c, d);
	merge(t, a, b);
}

void revolve(treap *t, int l, int r, int v) {
	treap *a, *b, *c, *d;
	split(t, a, b, r);
	split(a, c, d, l - 1);

	int cnt = r - l + 1;
	treap *L, *R;
	split(d, L, R, cnt - v);

	merge(d, R, L);

	merge(a, c, d);
	merge(t, a, b);
}

int query(treap *t, int l, int r) {
	treap *a, *b, *c, *d;
	split(t, a, b, r);
	split(a, c, d, l - 1);

	int rlt = getMin(d);

	merge(a, c, d);
	merge(t, a, b);
	return rlt;
}

int main() {
	treap *t = NULL;
	nodeC = 0;
	int n, q, l, r, v;
	scanf("%d", &n);
	for (int i = 0; i < n; i ++) {
		scanf("%d", &v);
		insert(t, i, v);
	}
	for (scanf("%d", &q); q --; ) {
		char s[10];
		scanf("%s", s);
		if (!strcmp(s, "ADD")) {
			int l, r, v;
			scanf("%d %d %d", &l, &r, &v);
			add(t, l, r, v);
		} else if (!strcmp(s, "REVERSE")) {
			scanf("%d %d", &l, &r);
			reverse(t, l, r);
		} else if (!strcmp(s, "REVOLVE")) {
			scanf("%d %d %d", &l, &r, &v);
			v%=r-l+1;
			revolve(t, l, r, v);
		} else if (!strcmp(s, "INSERT")) {
			scanf("%d %d", &l, &v);
			insert(t, l, v);
		} else if (!strcmp(s, "DELETE")) {
			scanf("%d", &l);
			remove(t, l);
		} else {
			scanf("%d %d", &l, &r);
			printf("%d\n", query(t, l, r));
		}
	}
}
