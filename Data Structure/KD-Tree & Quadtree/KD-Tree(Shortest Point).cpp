//Shortest Point
#include <stdio.h>
#include <algorithm>
#include <climits>
#include <vector>
#include <iostream>
using namespace std;
#define M 110000
#define inf 2000000000
#define Min(a,b)(a<b?a:b)
#define Max(a,b)(a>b?a:b)
typedef __int64 ll;
typedef pair<int,int>pii;
typedef vector<pii>vpii;

int tx[M],ty[M];
bool divX[M];
int sx[M],ex[M],sy[M],ey[M];

ll closestDist;
int closestNode;

bool cmpX(pii a,pii b) {return a.first<b.first;}
bool cmpY(pii a,pii b) {return a.second<b.second;}

void buildTree(int st,int en,pii pt[]) {
	if(st>=en) return;
	int mid=(st+en)>>1;

	int minx=inf;
	int maxx=-inf;
	int miny=inf;
	int maxy=-inf;
	for(int i=st;i<en;i++) {
		minx=Min(minx,pt[i].first);
		maxx=Max(maxx,pt[i].first);
		miny=Min(miny,pt[i].second);
		maxy=Max(maxy,pt[i].second);
	}
	divX[mid]=((maxx-minx)>=(maxy-miny));

	sx[mid]=minx;ex[mid]=maxx;
	sy[mid]=miny;ey[mid]=maxy;
//	sort(pt+st,pt+en,divX[mid] ? cmpX : cmpY);
	nth_element(pt+st,pt+mid,pt+en,divX[mid]?cmpX:cmpY);
	tx[mid]=pt[mid].first;
	ty[mid]=pt[mid].second;

	if(st+1==en) return;
	buildTree(st,mid,pt);
	buildTree(mid+1,en,pt);
}

void findNearestNeighbour(int st,int en,int x,int y) {
	if(st>=en || !closestDist) return;
	int mid=(st+en)>>1;
	int dx=x-tx[mid];
	int dy=y-ty[mid];
	ll d=(ll)dx*dx+(ll)dy*dy;
	if(closestDist>d) {
		closestDist=d;
		closestNode=mid;
	}
	if(st+1==en) return;
/*
	int t1=0,t2=0;
	if(sx[mid]>x) t1+=sx[mid]-x;else if(ex[mid]<x) t1+=x-ex[mid];
	if(sy[mid]>y) t2+=sy[mid]-y;else if(ey[mid]<y) t2+=y-ey[mid];
	if((ll)t1*t1+(ll)t2*t2>=closestDist) return;
*/
	int delta=divX[mid]?dx:dy;
	ll delta2=(ll)delta*delta;

	int l1=st;
	int r1=mid;
	int l2=mid+1;
	int r2=en;
	if(delta >0) swap(l1,l2),swap(r1,r2);

	findNearestNeighbour(l1,r1,x,y);
	if(delta2<closestDist) findNearestNeighbour(l2,r2,x,y);
}

void findNearestNeighbour(int n,int x,int y) {
	closestDist= LLONG_MAX;
	findNearestNeighbour(0,n,x,y);
}

vpii p;
int x[M],y[M];

int main() {
	int i,j,k,n,q;
	while(scanf("%d",&n) && n>0) {
		for(i=0;i<n;i++) scanf("%d %d",&x[i],&y[i]);
		p.resize(n);
		for(i=0;i<n;i++) p[i].first=x[i],p[i].second=y[i];
		sort(p.begin(),p.end());
		p.resize(n=unique(p.begin(),p.end())-p.begin());

		buildTree(0,n,&(vpii(p)[0]));

		scanf("%d",&q);
		while(q--) {
			int X,Y;
			scanf("%d %d",&X,&Y);
			findNearestNeighbour(n,X,Y);
			printf("%I64d\n",closestDist);
		}
	}
	return 0;
}
