#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>

using namespace std;

typedef pair <int, int> pii;

struct pnt {
	int x, y;
	pnt (int x = 0, int y = 0) : x(x), y(y) {}
	pnt operator - (pnt a) { return pnt(x - a.x, y - a.y); }
	int operator ^ (pnt a) { return x * a.y - y * a.x; }
	bool operator < (const pnt &o) const {
		if (x != o.x) return x < o.x;
		return y < o.y;
	}
};

inline int cross(pnt a, pnt b, pnt c) { return b - a ^ c - a; }

class segment {
public:
	pnt a, b;
	int id;
	segment(pnt a, pnt b, int id) : a(a), b(b), id(id) {}
	segment() {}
	bool operator < (const segment &o) const {
		if (a.x < o.a.x) {
			int s = cross(a, b, o.a);
			return (s > 0 || s == 0 && a.y < o.a.y);
		} else {
			int s = cross(o.a, o.b, a);
			return (s < 0 || s == 0 && a.y < o.a.y);
		}
		return a.y < o.a.y;
	}
};

bool intersect(segment s1, segment s2) {
	int x1 = s1.a.x, y1 = s1.a.y, x2 = s1.b.x, y2 = s1.b.y;
	int x3 = s2.a.x, y3 = s2.a.y, x4 = s2.b.x, y4 = s2.b.y;
	if (max(x1, x2) < min(x3, x4) || max(x3, x4) < min(x1, x2) ||
		max(y1, y2) < min(y3, y4) || max(y3, y4) < min(y1, y2)) {
		return false;
	}
	int z1 = s2.a - s1.a ^ s1.b - s1.a;
	int z2 = s2.b - s1.a ^ s1.b - s1.a;
	if (z1 < 0 && z2 < 0 || z1 > 0 && z2 > 0) return false;
	int z3 = s1.a - s2.a ^ s2.b - s2.a;
	int z4 = s1.b - s2.a ^ s2.b - s2.a;
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

	for (int i = 0; i < n * 2; ++i) {
		int id = e[i].id;
		if (e[i].type == 1) {
			set<segment>::iterator it = q.lower_bound(a[id]);
			if (it != q.end() && intersect(*it, a[id])) return make_pair(it->id, a[id].id);
			if (it != q.begin() && intersect(*--it, a[id])) return make_pair(it->id, a[id].id);
			q.insert(a[id]);
		} else {
			set<segment>::iterator it = q.lower_bound(a[id]), next = it, prev = it;
			if (it != q.begin() && it != --q.end()) {
				++next, --prev;
				if (intersect(*next, *prev)) return make_pair(next->id, prev->id);
			}
			q.erase(it);
		}
	}
	return make_pair(-1, -1);
}

vector <segment> v;

char* ord(int u) {
	char *r1 = "st", *r2 = "nd", *r3 = "rd", *r4 = "th";
	int r = u % 100, R = u % 10;
	if (!R || R > 3) return r4;
	if (r > 10 && r < 14) return r4;
	if (R == 1) return r1;
	if (R == 2) return r2;
	return r3;
}

int main() {
	int n = 2, a, b;
	v.clear();
	v.resize(n);
	v[0] = segment(pnt(0, 0), pnt(1, 1), 1);
	v[1] = segment(pnt(1, 0), pnt(0, 1), 17);
	pii res = findIntersection(v);
	a = res.first, b = res.second;
	if (a == -1) puts("NO INTERSECTION");
	else printf("%d-%s segment and %d-%s segment are intersect.\n", a, ord(a), b, ord(b));
}
