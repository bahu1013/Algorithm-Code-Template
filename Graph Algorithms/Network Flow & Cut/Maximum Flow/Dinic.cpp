#include <stdio.h>
#include <memory.h>
#include <vector>
#include <algorithm>
using namespace std;
#define M 5000
#define inf 1000000000

int nodes,src,dest;
int dist[M],q[M],work[M];

struct Edge {
	int to,rev;
	int f,cap;
};

vector<Edge>g[M];

void Init() {
	for(int i=0;i<M;i++) g[i].clear();
}

void addEdge(int s,int t,int cap){
	Edge a={t,g[t].size(),0,cap};
	Edge b={s,g[s].size(),0,cap};///0
	g[s].push_back(a);
	g[t].push_back(b);
}

bool dinic_bfs() {
	fill(dist,dist+nodes,-1);
	dist[src]=0;
	int qt=0;
	q[qt++]=src;
	for(int qh=0;qh<qt;qh++) {
		int u=q[qh];
		for(int j=0;j<g[u].size();j++) {
			Edge e=g[u][j];
			int v=e.to;
			if(dist[v]<0 && e.f<e.cap) {
				dist[v]=dist[u]+1;
				q[qt++]=v;
			}
		}
	}
	return dist[dest]>=0;
}

int dinic_dfs(int u,int f) {
	if(u==dest) return f;
	for(int &i=work[u];i<g[u].size();i++) {
		Edge &e=g[u][i];
		if(e.cap<=e.f) continue;
		int v=e.to;
		if(dist[v]==dist[u]+1) {
			int df=dinic_dfs(v,min(f,e.cap-e.f));
			if(df>0) {
				e.f+=df;
				g[v][e.rev].f-=df;
				return df;
			}
		}
	}
	return 0;
}

int maxFlow(int _src,int _dest,int _nodes) {
	src=_src;
	dest=_dest;
	nodes=_nodes;
	int result=0;
	while(dinic_bfs()) {
		fill(work,work+nodes,0);
		while(int delta=dinic_dfs(src,inf)) result+=delta;
	}
	return result;
}

int main() {
	int i,j,k,src,dst,n;
	n=400;src=0;dst=2*n+1;
	int K=40*n;
	Init();
	for(i=1;i<=n;i++) addEdge(src,i,K),addEdge(i+n,dst,K);
	for(i=1;i<=n;i++) for(j=1;j<=n;j++) addEdge(i,j+n,40);
	printf("%d\n",maxFlow(src,dst,dst+1));
}
