//2004 Beijing Preliminary A. Paper Cut
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <memory.h>

#define N 20

using namespace std;

struct pnt {
	double x, y;
	int link;
	pnt (double x = 0, double y = 0) : x(x), y(y), link(-1) {}
	pnt operator - (pnt a) { return pnt(x - a.x, y - a.y); }
	pnt operator + (pnt a) { return pnt(x + a.x, y + a.y); }
	pnt operator * (double a) { return pnt(x * a, y * a); }
	double operator ^ (pnt a) { return x * a.y - y * a.x; }
	double operator & (pnt a) { return x * a.x + y * a.y; }
	void input() { x = y = 0, scanf("%lf %lf", &x, &y); }
	void print() { printf("(%lf,%lf,%d)\n", x, y, link); }
};

typedef vector <pnt> poly;
typedef vector <poly> pSet;
pSet Set;
const double ep = 1e-7;
bool vis[1 << N];

void Init() {
	Set.clear();
	poly a(4);
	a[0] = pnt(0, 0);
	a[1] = pnt(1, 0);
	a[2] = pnt(1, 1);
	a[3] = pnt(0, 1);
	Set.push_back(a);
}

inline int sgn(double a) { return a > ep ? 1 : (a < -ep ? -1 : 0); }
inline bool isleft(pnt a, pnt b, pnt c) { return sgn(c - b ^ a - b) > 0; }
inline bool isright(pnt a, pnt b, pnt c) { return sgn(c - b ^ a - b) < 0; }

pnt sym(pnt a, pnt b, pnt c) {
	double tp = (c - a & b - a) / (b - a & b - a);
	pnt p = a * (1 - tp) + b * tp;
	return p * 2 - c;
}

bool intersect(pnt a, pnt b, pnt c, pnt d, pnt &res) {
	double den = a - b ^ c - d;
	if (fabs(den) < ep) return 0;
	double x = (a - d ^ c - d) / den;
	res = a * (1 - x) + b * x;
	return 1;
}

void doit(poly p, pnt a, pnt b, poly &q, poly &r, int num) {
	q.clear();
	r.clear();
	int i, j, n = p.size();
	for (i = 0; i < n; i ++) if (isleft(p[i], a, b)) break;
	if (i == n) {
		q.resize(n);
		for (int i = 0; i < n; i ++) {
			q[i] = p[i];
			q[i].link <<= 1;
		}
		return;
	}
	for (j = i; j < i + n; j ++) if (isright(p[j % n], a, b)) break;
	if (j == i + n) {
		r.resize(n);
		for (int k = 0; k < n; k ++) {
			r[k] = sym(a, b, p[k]);
			r[k].link = p[k].link << 1 | 1;
		}
		int tp = r[n - 1].link;
		for (int k = n - 1; k; k --) r[k].link = r[k - 1].link;
		r[0].link = tp;
		reverse(r.begin(), r.end());
		return;
	}
	for (i = j; i < j + n; i ++) if (isleft(p[i % n], a, b)) break;

	int left = i % n, right = j % n;
	pnt u, v;
	intersect(a, b, p[(left + n - 1) % n], p[left], u);
	intersect(a, b, p[(right + n - 1) % n], p[right], v);
	v.link = p[(right + n - 1) % n].link << 1;
	q.push_back(v);
	for (i = right; i < left + n; i ++) {
		if (!isright(p[i % n], a, b)) break;
		pnt tp = p[i % n];
		tp.link = p[i % n].link << 1;
		q.push_back(tp);
	}
	u.link = num << 1 | 1;
	q.push_back(u);
	u.link = p[(left + n - 1) % n].link << 1 | 1;
	r.push_back(u);
	for (i = left; i < right + n; i ++) {
		if (!isleft(p[i % n], a, b)) break;
		pnt tp = sym(a, b, p[i % n]);
		tp.link = p[i % n].link << 1 | 1;
		r.push_back(tp);
	}
	v.link = num << 1;
	r.push_back(v);
	int sz = r.size();
	int tp = r[sz - 1].link;
	for (int k = sz - 1; k; k --) r[k].link = r[k - 1].link;
	r[0].link = tp;
	reverse(r.begin(), r.end());
}

pSet FoldAndCut(pSet s, pnt a, pnt b, bool Fold) {
	pSet ret;
	ret.clear();
	int sz = s.size();
	for (int i = 0; i < sz; i ++) {
		poly p = s[i], q, r;
		int bf = Fold ? i : -1;
		doit(p, a, b, q, r, bf);
		ret.push_back(q);
		ret.push_back(r);
	}
	return ret;
}

int DFS(int u) {
	vis[u] = 1;
	for (int i = 0; i < Set[u].size(); i ++) {
		int v = Set[u][i].link;
		if (v >= 0 && !vis[v]) DFS(v);
	}
}

int Count() {
	int cnt = Set.size();
	memset(vis, 0, sizeof(bool) * cnt);
	int ret = 0;
	for (int i = 0; i < cnt; i ++) if (Set[i].size() > 2 && !vis[i]) ret ++, DFS(i);
	return ret;
}

int main() {
	int T, n;
	pnt a, b;
	for (scanf("%d", &T); T --; ) {
		Init();
		scanf("%d", &n);
		while (n --) {
			a.input();
			b.input();
			Set = FoldAndCut(Set, a, b, 1);
		}
		a.input();
		b.input();
		Set = FoldAndCut(Set, a, b, 0);
		printf("%d\n", Count());
	}
}
