//Inside Rectangle
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
int sx[M],ex[M],sy[M],ey[M],gas[M];

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
	gas[mid]=en-st;

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

int calc(int st,int en,int x1,int y1,int x2,int y2) {
	if(st>=en) return 0;
	int mid=(st+en)>>1;

	int ax=sx[mid];
	int ay=sy[mid];
	int bx=ex[mid];
	int by=ey[mid];

	if(ax>x2 || x1>bx || ay>y2 || y1>by) return 0;
	if (x1<=ax && bx<=x2 && y1<=ay && by<=y2) return gas[mid];

	int res=0;
	res+=calc(st,mid,x1,y1,x2,y2);
	res+=calc(mid+1,en,x1,y1,x2,y2);
	if(x1<=tx[mid] && tx[mid]<=x2 && y1<=ty[mid] && ty[mid]<=y2) ++res;
	return res;
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
//		p.resize(n=unique(p.begin(),p.end())-p.begin());

		buildTree(0,n,&(vpii(p)[0]));

		scanf("%d",&q);
		while(q--) {
			int a,b,c,d;
			scanf("%d %d %d %d",&a,&b,&c,&d);
			k=calc(0,n,a,b,c,d);
			printf("%d\n",k);
		}
	}
	return 0;
}
