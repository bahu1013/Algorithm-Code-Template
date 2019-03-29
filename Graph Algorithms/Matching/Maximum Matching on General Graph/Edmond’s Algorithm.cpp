#include <stdio.h>
#include <queue>
#include <vector>
#include <memory.h>
#include <algorithm>
using namespace std;

#define M 2001

bool g[M][M],inq[M],inpath[M],inblo[M];
int n,Match[M],start,finish,newbase,father[M],base[M];
queue<int> q;

int lca(int u,int v){
	memset(inpath,0,sizeof(inpath));
	while(1){
		u=base[u];
		inpath[u]=1;
		if(u==start)break;
		u=father[Match[u]];
	}
	while(1){
		v=base[v];
		if(inpath[v]) break;
		v=father[Match[v]];
	}
	return v;
}
void reset_trace(int u){
	while(base[u]!=newbase){
		int v=Match[u];
		inblo[base[u]]=inblo[base[v]]=1;
		u=father[v];
		if(base[u]!=newbase)father[u]=v;
	}
}
void blossom_contract(int u,int v){
	newbase=lca(u,v);
	memset(inblo,0,sizeof(inblo));
	reset_trace(u);reset_trace(v);
	if(base[u]!=newbase)father[u]=v;
	if(base[v]!=newbase)father[v]=u;
	for(int i=1; i<=n; i++)if(inblo[base[i]]){
		base[i]=newbase;
		if(!inq[i])q.push(i);
	}
}
void find_augmenting_path(){
	memset(inq,0,sizeof(inq));
	memset(father,0,sizeof(father));
	for(int i=1; i<=n; i++)base[i]=i;
	while(!q.empty())q.pop();q.push(start);
	finish=0;
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int i=1; i<=n; i++)
		if(g[x][i] && base[i]!=base[x] && Match[x]!=i)
		if(i==start || Match[i]>0 && father[Match[i]]>0)
			blossom_contract(x,i);
		else if(father[i]==0){
			father[i]=x;
			if(Match[i]>0)q.push(Match[i]);
			else{
				finish=i;
				return;
			}
		}
	}
}
void augment(){
	int u=finish;
	while(u>0){
		int v=father[u],w=Match[v];
		Match[v]=u;Match[u]=v;
		u=w;
	}
}

int edmonds(){
	memset(Match,0,sizeof(Match));
	for(int k=1; k<=n; k++)if(Match[k]==0){
		start=k;
		find_augmenting_path();
		if(finish>0)augment();
	}
	int k=0;
	for(int i=1;i<=n;i++) k+=(Match[i]>0);
	return k/2;
}

int main() {
	int i,j,k;
	while(scanf("%d",&n)>0) {
		for(i=1;i<=n;i++) for(j=1;j<=n;j++) scanf("%d",&g[i][j]);
		printf("%d\n",edmonds());
	}
}
