#include<stdio.h>
#include<math.h>
#include<memory.h>
#include<algorithm>
using namespace std;
#define N 110005
#define M 2000000
#define Min(a,b) (a<b?a:b)
#define Max(a,b) (a>b?a:b)

struct Edge {
	int v,w,next;
}edge[N<<1];

int n,q;
int start[N],tot;

void _add(int u,int v,int w) {
	edge[tot].v=v;
	edge[tot].w=w;
	edge[tot].next=start[u];
	start[u]=tot++;
}
void add(int u,int v,int w) {
	_add(u,v,w);
	_add(v,u,w);
}

int depth,b[N<<1],cnt,p[N],f[N];
int m;
int T[M],num[M],sum[M],nodecnt,lson[M],rson[M];

int bulid(int l,int r) {
	int root=nodecnt++;
	num[root]=0;
	sum[root]=0;
	if(l!=r) {
		int mid=(l+r)>>1;
		lson[root]=bulid(l,mid);
		rson[root]=bulid(mid+1,r);
	}
	return root;
}

int update(int root,int l,int r,int pos,int val) {
	int newroot=nodecnt++;
	num[newroot]=num[root]+1;
	sum[newroot]=sum[root]+val;
	if(l!=r) {
		int mid=(l+r)>>1;
		if(pos<=mid) {
			lson[newroot]=update(lson[root],l,mid,pos,val);
			rson[newroot]=rson[root];
		}
		else {
			rson[newroot]=update(rson[root],mid+1,r,pos,val);
			lson[newroot]=lson[root];
		}
	}
	return newroot;
}

int query(int lfrt,int rgrt,int lcart,int l,int r,int k) {
	if(l==r) return l;
	int cal=num[lson[lfrt]]+num[lson[rgrt]]-2*num[lson[lcart]];
	int mid=(l+r)>>1;
	if(cal>=k) return query(lson[lfrt],lson[rgrt],lson[lcart],l,mid,k);
	else return query(rson[lfrt],rson[rgrt],rson[lcart],mid+1,r,k-cal);
}

int query(int lfrt,int rgrt,int lcart,int k) {
	int calcnt=num[lfrt]+num[rgrt]-2*num[lcart];
	int l=1,r=m;
	int nowcnt=0,nowsum=0;
	while(l<r) {
		int tmpcnt=num[lson[lfrt]]+num[lson[rgrt]]-2*num[lson[lcart]];
		int tmpsum=sum[lson[lfrt]]+sum[lson[rgrt]]-2*sum[lson[lcart]];
		int mid=(l+r)>>1;
		int tt=mid*(tmpcnt+nowcnt)-tmpsum-nowsum;
		if(tt && tt>=k) {
			r=mid;
			lfrt=lson[lfrt];rgrt=lson[rgrt];lcart=lson[lcart];
		}
		else {
			l=mid+1;
			nowcnt+=tmpcnt;nowsum+=tmpsum;
			lfrt=rson[lfrt];rgrt=rson[rgrt];lcart=rson[lcart];
		}
	}
	if(k-(nowcnt*l-nowsum)<0) l--;
	return l+(k-(nowcnt*l-nowsum))/calcnt;
}

void dfs(int u,int pre){
	int t=++depth;
	b[++cnt]=t;
	f[t]=u;
	p[u]=cnt;
	for(int i=start[u];i!=-1;i=edge[i].next){
		int v=edge[i].v,w=edge[i].w;
		if(v==pre) continue;
		T[v]=update(T[u],1,m,w,w);
		dfs(v,u);
		b[++cnt]=t;
	}
}

int dp[N<<1][20];
void Init_rmq(int n){
	for(int i=1;i<=n;i++) dp[i][0]=b[i];
	int m=floor(log(n*1.0)/log(2.0));
	for(int j=1;j<=m;j++) for(int i=1;i<=n-(1<<j)+ 1;i++)
		dp[i][j]=Min(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
}

int rmq(int l,int r){
	int k=floor(log((r-l+1)*1.0)/log(2.0));
	return Min(dp[l][k],dp[r-(1<<k)+1][k]);
}

int lca(int a,int b){
	if(p[a]>p[b]) swap(a,b);
	return f[rmq(p[a],p[b])];
}

int main() {
	int Tc,ca=1;
	for(scanf("%d",&Tc);Tc--;) {
		tot=depth=cnt=nodecnt=0;
		memset(start,-1,sizeof(start));
		scanf("%d %d",&n,&q);
		for(int i=1;i<n;i++) {
			int u,v,w;
			scanf("%d %d %d",&u,&v,&w);
			add(u,v,w+1);
		}

		m=10000;T[1]=bulid(1,m);

		dfs(1,0);
		Init_rmq(cnt);

		printf("Case #%d:\n",ca++);
		while(q--) {
			int s,e,k,a,b;
			scanf("%d %d %d %d %d",&s,&e,&k,&a,&b);
			int initial=query(T[s],T[e],T[lca(s,e)],0);
			if(a<=b) printf("%d\n",initial+k/a-1);
			else {
				int ans=initial;
				if(k>=a) ans=ans+1+(k-a)/b;
				int ret=query(T[s],T[e],T[lca(s,e)],k/b);
				printf("%d\n",Max(ans,ret)-1);
			}
		}
	}
	return 0;
}
