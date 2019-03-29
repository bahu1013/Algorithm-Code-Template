#include <stdio.h>
#include <algorithm>
using namespace std;
const int INF=0x7fffffff;
int pre[105], low[105], con[105][105], f[105][105];
bool mark[105];
int prim(int n){
int i,j,pp,qq,sub,sum=0;
	for(i=0;i<n;i++){
		pre[i]=mark[i]=0;
		low[i]=f[0][i];
	}
	for(i=0;i<n;i++)for(j=0;j<n;j++)con[i][j]=0;
	mark[0]=1;
	for(i=1;i<n;i++){
		pp=-1;qq=INF;
		for(j=0;j<n;j++)
		if(!mark[j]&&low[j]<qq)	{	pp=j;qq=low[j];	}
		sum+=qq;
		for(j=0;j<n;j++){
			if(mark[j]){
				con[pp][j]=qq;
				con[pp][j]=max(con[pp][j], con[pre[pp]][j]);
///con[pp][j]>?=con[pre[pp]][j];
				con[j][pp]=con[pp][j];
			}else if(f[pp][j]!=INF&&low[j]>f[pp][j])	{
				low[j]=f[pp][j];
				pre[j]=pp;
			}
		}
		mark[pp]=1;
	}
	sub=INF;
	for(i=0;i<n;i++)
	    for(j=i+1;j<n;j++) if(f[i][j]!=INF&&pre[i]!=j&&pre[j]!=i){
			if(f[i][j]!=con[i][j])  //加上此行求出的严格的次小生成树
			sub=min(sub, f[i][j]-con[i][j]);///sub<?=f[i][j]-con[i][j];
		}
	if (sub==INF) return -1;
	return sum+sub;
}
int main(){
	int t,cc,i,j,n,m,sum;
	int a,b,c,pp,qq;
	scanf("%d",&t);
	for(cc=1;cc<=t;cc++){
		scanf("%d%d",&n,&m);
		for(i=0;i<n;i++)   for(j=0;j<n;j++)  f[i][j]=INF;
		for(i=0;i<m;i++){
			scanf("%d%d%d",&a,&b,&c);a--;b--;
			f[a][b]=f[b][a]=c;
		}
		sum=prim(n);
		if(sum!=-1)printf("%d\n",sum);
		else printf("Not Unique!\n");
	}
	return 0;
}
