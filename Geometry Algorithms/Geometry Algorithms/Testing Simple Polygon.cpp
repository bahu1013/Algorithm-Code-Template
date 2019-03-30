//CTU Open Contest 2011 Simple Polygon
#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>
#include <cmath>

using namespace std;

typedef pair <int, int> pii;
typedef __int64 INT;

const double ep = 1e-7;

struct pnt {
	int x, y;
	pnt (int x = 0, int y = 0) : x(x), y(y) {}
	pnt operator - (pnt a) { return pnt(x - a.x, y - a.y); }
	INT operator ^ (pnt a) { return 1LL * x * a.y - 1LL * y * a.x; }
	bool operator < (const pnt &o) const {
		if (x != o.x) return x < o.x;
		return y < o.y;
	}
	bool operator == (const pnt &o) const {
		return x == o.x && y == o.y;
	}
};

inline INT cross(pnt a, pnt b, pnt c) { return b - a ^ c - a; }

class segment {
public:
	pnt a, b;
	int id;
	segment(pnt A, pnt B, int ID) {
		id = ID;
		if (A < B) a = A, b = B;
		else a = B, b = A;
	}
	segment() {}
	bool operator < (const segment &o) const {
		pnt A = a, B = b;
		pnt AA = o.a, BB = o.b;
		if (B == AA) return 1;
		if (A == BB) return 0;
		double y1, y2;
		int pos = max(A.x, AA.x);
		if (B.x - A.x) y1 = 1.0 * (B.y - A.y) * (pos - A.x) / (B.x - A.x) + A.y;
		else y1 = 1.0 * min(A.y, B.y);
		if (BB.x - AA.x) y2 = 1.0 * (BB.y - AA.y) * (pos - AA.x) / (BB.x - AA.x) + AA.y;
		else y2 = 1.0 * min(AA.y, BB.y);
		if (fabs(y1 - y2) > ep) return y1 < y2;
		INT s = B - A ^ AA - A;
		INT t = B - A ^ BB - A;
		if (!s && !t) {
			int y1 = max(A.y, B.y);
			int y2 = max(AA.y, BB.y);
			return y1 < y2;
		}
		if (!s) return t > 0;
		if (!t) return s > 0;
		return 0;
	}
};

bool intersect(segment s1, segment s2) {
	int x1 = s1.a.x, y1 = s1.a.y, x2 = s1.b.x, y2 = s1.b.y;
	int x3 = s2.a.x, y3 = s2.a.y, x4 = s2.b.x, y4 = s2.b.y;
	if (max(x1, x2) < min(x3, x4) || max(x3, x4) < min(x1, x2) ||
		max(y1, y2) < min(y3, y4) || max(y3, y4) < min(y1, y2)) {
		return false;
	}
	INT z1 = s2.a - s1.a ^ s1.b - s1.a;
	INT z2 = s2.b - s1.a ^ s1.b - s1.a;
	if (z1 < 0 && z2 < 0 || z1 > 0 && z2 > 0) return false;
	INT z3 = s1.a - s2.a ^ s2.b - s2.a;
	INT z4 = s1.b - s2.a ^ s2.b - s2.a;
	if (z3 < 0 && z4 < 0 || z3 > 0 && z4 > 0) return false;
	return true;
}

class event {
public:
	pnt p;
	int id;
	int type;
	event(pnt p, int id, int type) : p(p), id(id), type(type) {}
	bool operator < (const event &o) const {
		return p.x < o.p.x || p.x == o.p.x && (type > o.type || type == o.type && p.y < o.p.y);
	}
};

bool nei(int a, int b, int n) {
	if (a == b + 1 || b == a + 1) return 1;
	if (!a && b == n - 1) return 1;
	if (!b && a == n - 1) return 1;
	return 0;
}

pii findIntersection(vector <segment> a) {
	int n = a.size();
	vector <event> e;
	for (int i = 0; i < n; ++i) {
		if (a[i].b < a[i].a) swap(a[i].a, a[i].b);
		e.push_back(event(a[i].a, i, 1));
		e.push_back(event(a[i].b, i, -1));
	}
	sort(e.begin(), e.end());

	set <segment> q;
	bool flag = 0;

	for (int i = 0; i < n * 2; ++i) {
		int id = e[i].id;
		if (e[i].type == 1) {
			set<segment>::iterator it = q.lower_bound(a[id]);
			if (it != q.end() && !nei(it->id, a[id].id, n) && intersect(*it, a[id])) return make_pair(it->id, a[id].id);
			if (it != q.begin()) {
				it --;
				if (!nei(it->id, a[id].id, n) && intersect(*it, a[id])) return make_pair(it->id, a[id].id);
			}
			q.insert(a[id]);
		} else {
			set<segment>::iterator it = q.lower_bound(a[id]), next = it, prev = it;
			if (it != q.begin() && it != --q.end()) {
				++next, --prev;
				if (!nei(next->id, prev->id, n) && intersect(*next, *prev)) return make_pair(next->id, prev->id);
			}
			q.erase(it);
		}
	}
	return make_pair(-1, -1);
}

#define N 40010

vector <segment> v;
typedef vector <pnt> poly;

poly p;

bool SimplePolygon(poly p) {
	int n = p.size();
	if (n < 3) return 0;
	if (n == 3) {
		INT area = p[1] - p[0] ^ p[2] - p[0];
		if (area) return 1;
		return 0;
	}
	v.clear();
	v.resize(n);
	for (int i = 0; i < n; i ++) v[i] = segment(p[i], p[(i + 1) % n], i);
	pii ans = findIntersection(v);
	if (ans.first == -1) return 1;
	return 0;
}

int main() {
	int n;
	while (scanf("%d", &n) && n) {
		p.clear();
		p.resize(n);
		for (int i = 0, x, y; i < n; i ++) {
			scanf("%d %d", &x, &y);
			p[i] = pnt(x, y);
		}
		if (SimplePolygon(p)) puts("YES");
		else puts("NO");
	}
}
