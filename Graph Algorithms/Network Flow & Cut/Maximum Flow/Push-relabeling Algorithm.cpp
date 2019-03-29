#include <stdio.h>
#include <memory.h>
#include <algorithm>
using namespace std;
#define M 810
#define inf 1000000000
#define Min(a,b) (a<b?a:b)

int cap[M][M];
int f[M][M],e[M],h[M],maxh[M];

void Init() {
	memset(cap,0,sizeof(cap));
	memset(h,0,sizeof(h));
	memset(maxh,0,sizeof(maxh));
	memset(e,0,sizeof(e));
	memset(f,0,sizeof(f));
}

void addEdge(int s, int t, int capacity) {
	cap[s][t] += capacity;
}

int maxFlow(int s, int t, int n) {
	h[s]=n-1;
	for(int i=0;i<n;i++) {
		f[s][i]=cap[s][i];
		f[i][s]=-f[s][i];
		e[i]=cap[s][i];
	}
	for(int sz=0;;) {
		if(!sz) {
			for(int i=0;i<n;i++) {
				if(i!=s && i!=t && e[i]>0) {
					if(sz!=0 && h[i]>h[maxh[0]]) sz=0;
					maxh[sz++]=i;
				}
			}
		}
		if(!sz) break;
		while(sz) {
			int i=maxh[sz-1];
			bool pushed=0;
			for(int j=0;j<n && e[i]!=0;j++) {
				if(h[i]==h[j]+1 && cap[i][j]-f[i][j]>0) {
					int df=Min(cap[i][j]-f[i][j],e[i]);
					f[i][j]+=df;
					f[j][i]-=df;
					e[i]-=df;
					e[j]+=df;
					if(e[i]==0) --sz;
					pushed=1;
				}
			}
			if(!pushed) {
				h[i]=inf;
				for(int j=0;j<n;j++) {
					if(h[i]>h[j]+1 && cap[i][j]-f[i][j]>0) h[i]=h[j]+1;
				}
				if(h[i]>h[maxh[0]]) {sz=0;break;}
			}
		}
	}
	int flow=0;
	for(int i=0;i<n;i++) flow+=f[s][i];
	return flow;
}

int main() {
	int i,j,k,src,dst,n;
	n=400;
	src=0;dst=2*n+1;
	int K=40*n;
	Init();
	for(i=1;i<=n;i++) addEdge(src,i,K),addEdge(i+n,dst,K);
	for(i=1;i<=n;i++) for(j=1;j<=n;j++) addEdge(i,j+n,40);
	printf("%d\n",maxFlow(src,dst,dst+1));
}
