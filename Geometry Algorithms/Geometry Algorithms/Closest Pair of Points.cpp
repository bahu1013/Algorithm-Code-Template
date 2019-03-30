#include <stdio.h>
#include <math.h>
#include <algorithm>
#define N 100010
#define min(a, b) ((a)<(b)?(a):(b))

using namespace std;

struct pnt {
	double x, y;
	pnt (double x=0, double y=0): x(x), y(y) {}
	pnt operator -(pnt a) { return pnt(x-a.x, y-a.y); }
	double operator &(pnt a) { return x*a.x+y*a.y; }
	void input() { x=y=0, scanf("%lf %lf", &x, &y); }
} p[N], tmp1[N], tmp2[N], s, e;

int n;
double ans;
const double inf=1e10;
const double ep=1e-9;
const int P=7; 
double dist(pnt a) { return sqrt(a&a); }

bool cmpX(pnt a, pnt b) {
	if (fabs(a.x-b.x)>ep) return a.x<b.x;
	return a.y<b.y;
}

bool cmpY(pnt a, pnt b) {
	if (fabs(a.y-b.y)>ep) return a.y<b.y;
	return a.x<b.x;
}

void Input(int st, int &en) {
	scanf("%d", &n);
	for (int i=st; i<st+n; i++) p[i].input();
	en=st+n;
}

void Output() {
	printf("The closest pair is (%.4lf, %.4lf)-(%.4lf, %.4lf)\n", s.x, s.y, e.x, e.y);
	printf("Distance is %.4lf\n", ans);
}

void Merge(int l, int m, int r) {
	int i, j, k;

	for (i=l; i<m; i++) tmp1[i-l]=p[i];
	for (i=m; i<r; i++) tmp2[i-m]=p[i];
	tmp1[m-l]=tmp2[r-m]=pnt(0, inf);

	j=k=0;
	for (i=l; i<r; i++) {
		if (cmpY(tmp1[j], tmp2[k])) p[i]=tmp1[j++];
		else p[i]=tmp2[k++];
	}
}

double func(int l, int r, pnt &S, pnt &E) {
	if (r==l+1) return inf;

	int m=(l+r)>>1, cnt=0, i, j;
	double mx=(p[m-1].x+p[m].x)/2, tmp, ret;
	pnt s1, s2, e1, e2;

	double ret1=func(l, m, s1, e1);
	double ret2=func(m, r, s2, e2);

	if (ret1+ep<ret2) ret=ret1, S=s1, E=e1;
	else ret=ret2, S=s2, E=e2;

	Merge(l, m, r);

	for (i=l; i<r; i++) if (fabs(mx-p[i].x)<ret) tmp1[cnt++]=p[i];

	for (i=0; i<cnt; i++)
		for (j=i+1; j<i+P && j<cnt; j++) {
			tmp=dist(tmp1[i]-tmp1[j]);
			if (tmp<ret) ret=tmp, S=tmp1[i], E=tmp1[j];
		}
	return ret;
}

double ClosestPair(int st, int en) {
	sort(p+st, p+en,cmpX);
	return ans=func(st, en, s, e);
}

int main() {
	int st, en;
	st=1;
	Input(st, en);
	ClosestPair(st, en);
	Output();
}
