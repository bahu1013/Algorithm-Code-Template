#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <set>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <algorithm>
#include <limits>
using namespace std;
typedef long long LL;
const int MAXN=1e+4;
const int MAXM=1e+5;
const int INF= numeric_limits<int>::max();
const LL LL_INF= numeric_limits<LL>::max();
struct point {
	LL flow,cost;
}cs[6000];
int tcs;
struct Edge
{
	int from,to,ci,cost,next;
	Edge(){}
	Edge(int _from,int _to,int _ci,int _cost,int _next):from(_from),to(_to),ci(_ci),cost(_cost),next(_next){}
}e[MAXM];
int head[MAXN],tot;
int q[MAXM];
int dis[MAXN],pre[MAXN],rec[MAXN],vis[MAXN];
inline void init(){
	memset(head,-1,sizeof(head));
	tot=0;
}
inline void AddEdge1(int u,int v,int ci,int cost){
	e[tot]=Edge(u,v,ci,cost,head[u]);
	head[u]=tot++;
	e[tot]=Edge(v,u,0,-cost,head[v]);
	head[v]=tot++;
}
inline bool spfa(int S,int T,LL &cost,LL &flow){
	int i,h=0,t=0;
	for(i=0;i<=MAXN;i++){
		dis[i]=INF;
		vis[i]=false;
	}
	q[h]=S;
	dis[S]=0;
	vis[S]=true;
	while(h<=t){
		int u=q[h++];
		vis[u]=false;
		for(i=head[u];~i;i=e[i].next){
			int v=e[i].to;
			if(e[i].ci>0&&dis[v]>dis[u]+e[i].cost){
				dis[v]=dis[u]+e[i].cost;
				pre[v]=u;
				rec[v]=i;
				if(!vis[v]){
					vis[v]=1;
					q[++t]=v;
				}
			}
		}
	}
	if(dis[T]==INF)return false;
	int minn=INF;
	for(i=T;i!=S;i=pre[i]){
		if(e[rec[i]].ci<minn)
			minn=e[rec[i]].ci;
	}
	for(i=T;i!=S;i=pre[i]){
		e[rec[i]].ci-=minn;
		e[rec[i]^1].ci+=minn;
	}
	cs[tcs].flow=minn;
	cs[tcs].cost=dis[T];
	++tcs;
	cost+=dis[T]*minn;
	flow+=minn;
	return true;
}

inline void mincostmaxflow(int S,int T,LL &cost,LL &flow){
	while(spfa(S,T,cost,flow));
}
int main()
{
	int n,m,k;
	while(~scanf("%d%d%d",&n,&m,&k)){
		init();
		tcs=0;
		for(int i=0,x,y,v;i<m;i++){
			scanf("%d%d%d",&x,&y,&v);
			AddEdge1(x,y,v,1);
		}
		if(k==0){
		puts("0");continue;
		}
		AddEdge1(n,0,k,0);
		AddEdge1(n-1,n+1,k,0);
		LL cost=0,flow=0;
		mincostmaxflow(n,n+1,cost,flow);

		LL ss=0,tsum=0,tpre=0;
		for(int i=0;i<tcs;i++){
			if(cs[i].cost==tpre){
				ss+=cs[i].flow;
				tsum+=cs[i].flow;
			}
			else if(cs[i].cost==tpre+1){
				ss+=cs[i].flow+tsum;
				tpre=cs[i].cost;tsum+=cs[i].flow;
			}
			else {
				LL t=(cs[i].cost-tpre-1)*tsum;
				if(ss+t>=k){
					tpre+=(k-ss)/tsum+((k-ss)%tsum!=0);
					ss=k;
					break;
				}
				ss+=cs[i].flow+(cs[i].cost-tpre)*tsum;
				tpre=cs[i].cost;tsum+=cs[i].flow;
			}
			if(ss>=k)break;
		}
		if(tcs==0)puts("No solution");
		else if(ss>=k)printf("%I64d\n",tpre);
		else {
			printf("%I64d\n",(k-ss)/tsum+((k-ss)%tsum!=0)+tpre);
		}
	}
	return 0;
}
