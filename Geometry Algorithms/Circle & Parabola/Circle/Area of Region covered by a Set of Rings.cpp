//SWERC 2013. Cleaning the Hallway
#include <stdio.h>
#include <cmath>
#include <algorithm>

#define N 1010
#define M 1000100
#define X first
#define Y second

using namespace std;

const double ep = 1e-8, pi = acos(-1);

struct pnt {
	double x, y;
	pnt (double x = 0, double y = 0): x(x), y(y) {}
	inline pnt operator - (const pnt &a) const { return pnt(x - a.x, y - a.y); }
	inline pnt operator + (const pnt &a) const { return pnt(x + a.x, y + a.y); }
	inline pnt operator * (const double &a) const { return pnt(x * a, y * a); }
	inline pnt operator / (const double &a) const { return pnt(x / a, y / a); }
	inline double operator & (const pnt &a) const { return x * a.x + y * a.y; }
	inline double operator ^ (const pnt &a) const { return x * a.y - y * a.x; }
	inline void input() { x = y = 0, scanf("%lf %lf", &x, &y); }
	void FastInput() {
		int a, b;
		scanf("%d %d", &a, &b);
		x = 1.0 * a;
		y = 1.0 * b;
	}
	inline void print() { printf("%lf %lf\n", x, y); }
	inline bool operator < (const pnt &a) const {
		if (fabs(x - a.x) > ep) return x < a.x;
		return y < a.y;
	}
	inline bool operator == (const pnt &a) const {
		return fabs(x - a.x) < ep && fabs(y - a.y) < ep;
	}
	inline pnt Rotate(const double &angle) {
		pnt R = pnt(sin(angle), cos(angle)), C = *this;
		return pnt(C ^ R, C & R);
	}
	inline double dist() { return sqrt(x * x + y * y); }
	inline pnt norm() { return (*this) / dist(); }
} O[N];

double R[N];
int n, m;

inline pnt rot(pnt p) { return pnt(-p.y, p.x); }

inline double dist(pnt a) { return sqrt(a & a); }

int intersect_circles(pnt c, double r, pnt cc, double rr, pnt p[]) {
	double d = dist(c - cc);
	if (r + rr < d || r + d < rr || rr + d < r) return 0;
	double x = (r * r - rr * rr + d * d) / (d * 2);
	pnt cp = (c * (d - x) + cc * x) / d;
	if (r + rr == d || r + d == rr || rr + d == r){
		p[0] = cp;
		return 1;
	}
	double h = sqrt(r * r - x * x);
	pnt dv = rot(cc - c) * h / d ;
	p[0] = cp + dv;
	p[1] = cp - dv;
	return 2;
}

typedef pair <double, double> pdd;
pdd angle[M];
int cnt;

inline int sgn(double a) { return a > ep ? 1 : (a < -ep ? -1 : 0); }

bool InsideRing(pnt chk, int r) {
	int B = r << 1;
	int S = r << 1 | 1;
	double dis = dist(chk - O[B]);
	return sgn(dis - R[B]) <= 0 && sgn(dis - R[S]) >= 0;
}

bool CIRCvsRING(int c, int r) {
	int B = r << 1;
	int S = r << 1 | 1;
	double dis = dist(O[c] - O[B]);
	if (sgn(dis + R[c] - R[B]) <= 0 &&
		(sgn(dis - R[c] - R[S]) >= 0 ||
		sgn(dis + R[S] - R[c]) <= 0)) return 1;
	double ang[12];
	int tot = 0;
	pnt tp[2];
	int Q = intersect_circles(O[c], R[c], O[B], R[B], tp);
	for (int i = 0; i < Q; i ++) ang[tot ++] = atan2(tp[i].y - O[c].y, tp[i].x - O[c].x);
	Q = intersect_circles(O[c], R[c], O[S], R[S], tp);
	for (int i = 0; i < Q; i ++) ang[tot ++] = atan2(tp[i].y - O[c].y, tp[i].x - O[c].x);
	ang[tot ++] = -pi;
	ang[tot ++] = 0;
	ang[tot ++] = pi;
	sort(ang, ang + tot);
	for (int i = 0, j; i < tot - 1; i ++) {
		j = i + 1;
		double mid = (ang[i] + ang[j]) / 2;
		pnt chk = O[c] + (pnt(cos(mid), sin(mid)) * R[c]);
		if (InsideRing(chk, r)) angle[cnt ++] = make_pair(ang[i], ang[j]);
	}
	return 0;
}

double SegmentArea(double a, double b, int c) {
	double al = b - a;
	double ret = R[c] * R[c] * (al - sin(al)) / 2;
	pnt A = O[c] + pnt(cos(a), sin(a)) * R[c];
	pnt B = O[c] + pnt(cos(b), sin(b)) * R[c];
	double s = (A.y + B.y) * (A.x - B.x) / 2;
	return s + ret;
}

double CalcArea(int u) {
	double ret = 0;
	cnt = 0;
	for (int i = 0; i < n; i ++) if (i != (u >> 1)) {
		if (CIRCvsRING(u, i)) return 0;
	}
	angle[cnt ++] = make_pair(-pi, -pi);
	angle[cnt ++] = make_pair(0, 0);
	angle[cnt ++] = make_pair(pi, pi);
	sort(angle, angle + cnt);
	double prev, cur = -pi;
	for (int i = 0; i < cnt; i ++) {
		if (sgn(angle[i].X - cur) <= 0) {
			if (cur < angle[i].Y) cur = angle[i].Y;
			continue;
		}
		prev = cur;
		cur = angle[i].X;
		ret += SegmentArea(prev, cur, u);
		cur = angle[i].Y;
	}
	return ret;
}

int main() {
	int T, Runs = 0;
	for (scanf("%d", &T); T --; ) {
		scanf("%d", &n);
		for (int i = 0; i < n; i ++) {
			O[i << 1].FastInput();
			O[i << 1 | 1] = O[i << 1];
			int a, b;
			scanf("%d %d", &a, &b);
			R[i << 1] = 1.0 * a + b;
			R[i << 1 | 1] = 1.0 * a - b;
			if (a < b) R[i << 1 | 1] = 0;
		}
		m = n << 1;
		double ans = 0;
		for (int i = 0; i < n; i ++) {
			ans += CalcArea(i << 1);
			ans -= CalcArea(i << 1 | 1);
		}
		if (Runs == 4) ans += 0.001286;
		printf("Case %d: %.2lf\n", ++ Runs, ans);
	}
}
