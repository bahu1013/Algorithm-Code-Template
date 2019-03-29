#include <stdio.h>
#include <memory.h>
using namespace std;
#define M 4010

int n;
int con[M][M],vis[M],b[M];

int calc(int v) {
	int i;
	for(i=0;i<n;i++) {
		if(!con[v][i] || vis[i]) continue;
		vis[i]=1;
		if(b[i]<0 || calc(b[i])) {
			b[i]=v;
			return 1;
		}
	}
	return 0;
}

int doit() {
	int i,j,k;
	int ans=0;
	memset(b,-1,sizeof(b));
	for(i=0;i<n;i++) {
		memset(vis,0,sizeof(vis));
		ans+=calc(i);
	}
	return ans;
}

int main() {
	int T,q,i,j,k;
	for(scanf("%d",&T);T--;) {
		scanf("%d %d",&n,&q);
		memset(con,0,sizeof(con));
		while(q--) {
			int x,y;
			scanf("%d %d",&x,&y);
			con[x][y]=1;
		}
		printf("%d\n",doit());
	}
	return 0;
}
