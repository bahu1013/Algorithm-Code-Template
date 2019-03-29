#include<stdio.h>
#include<memory.h>
using namespace std;
#define M 10000010
#define N 50010
typedef __int64 ll;
#define inf 1<<30
#define mod 1000000007

int tot;
int bL[M],tL[M],bR[M],tR[M];
int sum[M],add[M];

void Add(int &a,int b) {
	a+=b;
	if(a>=mod) a-=mod;
}

void pushdown(int v) {
	if(add[v]) {
		Add(sum[bL[v]],add[v]);
		Add(sum[tL[v]],add[v]);
		Add(sum[bR[v]],add[v]);
		Add(sum[tR[v]],add[v]);

		Add(add[bL[v]],add[v]);
		Add(add[tL[v]],add[v]);
		Add(add[bR[v]],add[v]);
		Add(add[tR[v]],add[v]);
		add[v]=0;
	}
}

void pushup(int v) {
	sum[v] = 0;
	Add(sum[v],sum[bL[v]]);
	Add(sum[v],sum[tL[v]]);
	Add(sum[v],sum[bR[v]]);
	Add(sum[v],sum[tR[v]]);
}

void Init(int tot) {
	sum[tot]=add[tot]=bL[tot]=tL[tot]=bR[tot]=tR[tot]=0;
}

int ans,tmp;

void insert(int v,int ax,int ay,int bx,int by,int x,int y,int X,int Y,int val) {
	if(ax>X || bx<x || ay>Y || by<y) return;
	if(ax>=x && bx<=X && ay>=y && by<=Y) {
		tmp=(ll)val*(bx-ax+1)%mod;
		tmp=(ll)tmp*(by-ay+1)%mod;
		Add(sum[v],tmp);
		Add(add[v],val);
		return;
	}
	int mx=(ax+bx)>>1;
	int my=(ay+by)>>1;

	if(!bL[v]) {
		bL[v]=++tot;Init(tot);
		tL[v]=++tot;Init(tot);
		bR[v]=++tot;Init(tot);
		tR[v]=++tot;Init(tot);
	}
	pushdown(v);
	insert(bL[v],ax,ay,mx,my,x,y,X,Y,val);
	insert(tL[v],ax,my+1,mx,by,x,y,X,Y,val);
	insert(bR[v],mx+1,ay,bx,my,x,y,X,Y,val);
	insert(tR[v],mx+1,my+1,bx,by,x,y,X,Y,val);
	pushup(v);
}

void calc(int v,int ax,int ay,int bx,int by,int x,int y,int X,int Y) {
	if(ax>X || bx<x || ay>Y || by<y) return;
//	printf("%d %d %d\n",v,sum[v],add[v]);
	if(ax>=x && bx<=X && ay>=y && by<=Y) {
		Add(ans,sum[v]);
		return;
	}
	int mx=(ax+bx)>>1;
	int my=(ay+by)>>1;

	if(!bL[v]) {
		bL[v]=++tot;Init(tot);
		tL[v]=++tot;Init(tot);
		bR[v]=++tot;Init(tot);
		tR[v]=++tot;Init(tot);
	}
	pushdown(v);
	calc(bL[v],ax,ay,mx,my,x,y,X,Y);
	calc(tL[v],ax,my+1,mx,by,x,y,X,Y);
	calc(bR[v],mx+1,ay,bx,my,x,y,X,Y);
	calc(tR[v],mx+1,my+1,bx,by,x,y,X,Y);
	pushup(v);
}

int ax[N],ay[N],bx[N],by[N];

int main() {
	freopen("1.in","r",stdin);
	int i,j,k,n;
	while(scanf("%d",&n)>0) {
		for(i=0;i<n;i++) scanf("%d %d %d %d",&ax[i],&ay[i],&bx[i],&by[i]);
		tot=0;Init(tot);
		insert(0,0,0,inf,inf,0,0,inf,inf,1);
		int res=0;
		for(i=0;i<n;i++) {
			ans=0;

			calc(0,0,0,inf,inf,ax[i],ay[i],bx[i],by[i]);
			insert(0,0,0,inf,inf,ax[i],ay[i],bx[i],by[i],ans);
			ans=(ll)ans*(bx[i]-ax[i]+1)%mod;
			ans=(ll)ans*(by[i]-ay[i]+1)%mod;
			Add(res,ans);
		}
		printf("%d\n",res);
	}
    return 0;
}
