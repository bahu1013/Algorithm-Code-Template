//O(n^2)
#include<stdio.h>
#include<math.h>
#include<algorithm>

#define ep 1e-7
#define MAXV 6010

using namespace std;

//3D point
struct pnt{
	double x, y, z;
	pnt() {}
	pnt(double _x, double _y, double _z): x(_x), y(_y), z(_z){}
	pnt operator - (const pnt p1) { return pnt(x - p1.x, y - p1.y, z - p1.z); }
	pnt operator ^ (pnt p) { return pnt(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x); }
	double operator & (pnt p) { return x * p.x + y * p.y + z * p.z; }
	void input() { x = y = z = 0, scanf("%lf %lf %lf", &x, &y, &z); }
};

struct _3DCH{
	struct fac{
		int a, b, c;
		bool ok;
	};
	int n;
	pnt P[MAXV]; /// Initial point
	int cnt;	// count of triangle on surface of convexhull
	fac F[MAXV * 8]; // the triangle on the surface of convexhull
	int to[MAXV][MAXV];
	inline double vlen(pnt a) { return sqrt(a.x * a.x + a.y * a.y + a.z * a.z); } // the vector length
	inline double area(pnt a, pnt b, pnt c) { return vlen(b - a ^ c - a); } // 2 * square of triangle
	double volume(pnt a, pnt b, pnt c, pnt d) { return (b - a ^ c - a) & d - a;}

	double pntof(pnt &p, fac &f) {
		pnt m = P[f.b] - P[f.a], n = P[f.c] - P[f.a], t = p - P[f.a];
		return (m ^ n) & t;
	}

	void deal(int p, int a, int b) {
		int f = to[a][b];
		fac add;
		if (F[f].ok) {
			if (pntof(P[p], F[f]) > ep) dfs(p, f);
			else {
				add.a = b, add.b = a, add.c = p, add.ok = 1;
				to[p][b] = to[a][p] = to[b][a] = cnt;
				F[cnt++] = add;
			}
		}
	}

	void dfs(int p, int cur) {
		F[cur].ok = 0;
		deal(p, F[cur].b, F[cur].a);
		deal(p, F[cur].c, F[cur].b);
		deal(p, F[cur].a, F[cur].c);
	}

	bool same(int s, int t) {
		pnt &a = P[F[s].a], &b = P[F[s].b], &c = P[F[s].c];
		return fabs(volume(a, b, c, P[F[t].a])) < ep && fabs(volume(a, b, c, P[F[t].b])) < ep && fabs(volume(a, b, c, P[F[t].c])) < ep;
	}

	void construct() {
		cnt = 0;
		if (n < 4) return;
		bool sb = 1;

		for (int i = 1; i < n; i ++) {
			if (vlen(P[0] - P[i]) > ep) {
				swap(P[1], P[i]);
				sb = 0;
				break;
			}
		}
		if (sb)return;

		sb = 1;
		for (int i = 2; i < n; i ++) {
			if (vlen((P[0] - P[1]) ^ (P[1] - P[i])) > ep) {
				swap(P[2], P[i]);
				sb = 0;
				break;
			}
		}
		if (sb)return;

		sb = 1;
		for (int i = 3; i < n; i ++) {
			if (fabs(((P[0] - P[1]) ^ (P[1] - P[2])) & (P[0] - P[i])) > ep) {
				swap(P[3], P[i]);
				sb = 0;
				break;
			}
		}
		if (sb)return;

		fac add;
		for (int i = 0; i < 4; i ++) {
			add.a = (i + 1) % 4, add.b = (i + 2) % 4, add.c = (i + 3) % 4, add.ok = 1;
			if (pntof(P[i], add) > 0) swap(add.b, add.c);
			to[add.a][add.b] = to[add.b][add.c] = to[add.c][add.a] = cnt;
			F[cnt ++] = add;
		}
		for (int i = 4; i < n; i ++) {
			for (int j = 0; j < cnt; j ++) {
				if (F[j].ok && pntof(P[i], F[j]) > ep) {
					dfs(i, j);
					break;
				}
			}
		}
		int tmp = cnt;
		cnt = 0;
		for (int i = 0; i < tmp; i ++) {
			if (F[i].ok) F[cnt++] = F[i];
		}
	}

	double area() {
		double ret = 0.0;
		for (int i = 0; i < cnt; i ++) {
			ret += area(P[F[i].a], P[F[i].b], P[F[i].c]);
		}
		return ret / 2.0;
	}

	double volume() {
		pnt O(0, 0, 0);
		double ret = 0.0;
		for (int i = 0; i < cnt; i ++) {
			ret += volume(O, P[F[i].a], P[F[i].b], P[F[i].c]);
		}
		return fabs(ret / 6.0);
	}

	int facetCnt_tri() {
		return cnt;
	}

	int facetCnt() {
		int ans = 0;
		for (int i = 0; i < cnt; i ++) {
			bool nb = 1;
			for (int j = 0; j < i; j ++) {
				if (same(i, j)) {
					nb = 0;
					break;
				}
			}
			ans += nb;
		}
		return ans;
	}
	bool input() {
		int bf = scanf("%d", &n);
		if (!n || bf == EOF) return 0;
		for (int i = 0; i < n; i ++) P[i].input();
		return 1;
	}
};

// _3DCH hull;

int main() {
	while (hull.input()) {
		printf("%d: ", hull.n);
		hull.construct();
		printf("%d\n", hull.facetCnt());
	}
	return 0;
}
