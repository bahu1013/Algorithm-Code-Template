#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

struct node
{
	int v,next;
};

struct Node
{
	__int64 hash,ans;
};

const __int64 mod=1000000007;
const __int64 P=10003;
const __int64 Q=100000037;
node edges[200005];
Node q[50005];
int head[50005],e,E,M,MMM,C,ff[50005],dp[50005],n;
__int64 hash[100005],ans[100005],p[100005],son[50005];

void Add(int u,int v)
{
	edges[e].v=v;
	edges[e].next=head[u];
	head[u]=e++;
}

__int64 POW(__int64 a,__int64 b)
{
	__int64 ans=1;
	while(b)
	{
		if(b&1) ans=(ans*a)%mod;
		a=(a*a)%mod;
		b>>=1;
	}
	return ans;
}

__int64 cal(int n,int m)
{
	if(n==m) return 1;
	__int64 n1=1,n2=p[m],i;
	for(i=1;i<=m;i++) n1=n1*(n-i+1)%mod;
	return n1*POW(n2,mod-2)%mod;
}

int cmp(Node a,Node b)
{
	return a.hash<b.hash;
}


void init()
{
	int i;
	p[1]=1;
	for(i=2;i<=100000;i++) p[i]=p[i-1]*i%mod;
}


int DFS(int u,int pre)
{
	int m1=0,m2=0,i,v,t;
	for(i=head[u];i!=-1;i=edges[i].next)
	{
		v=edges[i].v;
		if(v==pre) continue;
		t=DFS(v,u);
		if(t>m1) m2=m1,m1=t,ff[u]=i;
		else if(t>m2) m2=t;
	}
	if(M<m1+m2) MMM=u,M=m1+m2;
	dp[u]=m1;
	return dp[u]+1;
}


void DFS1(int u,int pre)
{
	int i,j,v;
	son[u]=0;

	for(i=head[u];i!=-1;i=edges[i].next)
	{
		v=edges[i].v;
		if(v==pre||i==E||i==(E^1)) continue;
		ans[v]=C;
		DFS1(v,u);
		son[u]++;
	}
	if(!son[u])
	{
		hash[u]=1;
		return;
	}
	for(j=0,i=head[u];i!=-1;i=edges[i].next)
	{
		v=edges[i].v;
		if(v==pre||i==E||i==(E^1)) continue;
		q[j].hash=hash[v];
		q[j++].ans=ans[v];
	}
	sort(q,q+son[u],cmp);
	hash[u]=977872;
	for(i=0;i<son[u];i++)
	{
		for(j=i;j<son[u]&&q[i].hash==q[j].hash;j++)
		{
			hash[u]*=P;
			hash[u]^=q[j].hash;
			hash[u]%=mod;
		}
		j--;
		ans[u]*=cal(q[i].ans+j-i,j-i+1);
		ans[u]%=mod;
		i=j;
	}
}

int main()
{
	init();
	while(scanf("%d%d",&n,&C)!=-1)
	{
		memset(head,-1,sizeof(head));
		e=2;
		int i,u,v;
		for(i=1;i<n;i++)
		{
			scanf("%d%d",&u,&v);
			Add(u,v);
			Add(v,u);
		}
		M=-1;DFS(1,-1);
		printf("%d %d\n", M, MMM);
		///printf("%d %d\n", M, MMM);\
        M is diameter, MMM is already core.
		if(M&1)
		{
			while(dp[MMM]*2>M+1) MMM=edges[ff[MMM]].v;
			E=ff[MMM];
			Add(MMM,n+1);
			Add(n+1,MMM);
			Add(edges[ff[MMM]].v,n+1);
			Add(n+1,edges[ff[MMM]].v);
			MMM=n+1;
			ans[MMM]=1;
		}
		else
		{
			E=0;
			while(dp[MMM]*2>M) MMM=edges[ff[MMM]].v;
			ans[MMM]=C;
		}
		printf("MMM = %d\n", MMM);
		DFS1(MMM,-1);
		printf("%I64d\n",ans[MMM]);
	}
	return 0;
}
