#include <stdio.h>
#include <vector>
#include <memory.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define M 25
#define N 400100

char s[M];
int pad[M*M];
vector<int> con[M*M];
int n,flow,index,sink,T,ecnt,npath;
int next[N],to[N],head[N];

void Add(int x,int y) {
	to[ecnt]=y;next[ecnt]=head[x];head[x]=ecnt++;
}

void ADD(int x,int y,int z) {
	to[z]=y;next[z]=head[x];head[x]=z;
}

int path[N],vis[N];

int Find(int len) {
	if(path[len]==sink) {npath=len;return 1;}
	int v=path[len],u;
	for(int i=head[v];i>=0;i=next[i]) {
		u=to[i];
		if(vis[u]!=T) {
			vis[u]=T;
			path[len+1]=u;
			if(Find(len+1)) return 1;
		}
	}
	return 0;
}

int deleteEdge(int v,int w) {
	int u=-1,i;
	for(i=head[v];i>=0;i=next[i]) {
		if(to[i]==w) break;
		u=i;
	}
	if(i<0) return -1;

	int sto;
	if(u<0) {
		sto=head[v];
		head[v]=next[head[v]];
	}
	else {
		sto=next[u];
		next[u]=next[i];
	}
	return sto;
}

int Mflow(int level) {
	for(int i=0;i<=sink;i++) vis[i]=0;
	T=1;
	while(Find(0)) {
		T++;flow++;
		for(int i=0;i<npath;i++) {
			int v=path[i];
			int w=path[i+1];
			int sto=deleteEdge(v,w);
			if(sto<0) while(1);
			ADD(w,v,sto);
		}
	}
	return flow;
}

int main() {
	int i,j,k,ca=0;
	while(scanf("%d",&n) && n) {
		for(i=0;i<n;i++) {
			scanf("%s",s);
			for(j=0;j<n;j++) pad[j*n+i]=(s[j]=='.');
		}
		for(i=0;i<n*n;i++) {
			con[i].clear();
			int c=i/n,r=i%n;
			if(pad[i]) {
				con[i].push_back(n*n);
				if(c>0 && pad[i-n]) con[i].push_back(n*n-n);
				if(r>0 && pad[i-1]) con[i].push_back(n*n-1);
				if(r<n-1 && pad[i+1]) con[i].push_back(n*n+1);
				if(c<n-1 && pad[i+n]) con[i].push_back(n*n+n);
			}
		}
		int ans=n-1;
		ecnt=0;
		memset(next,-1,sizeof(next));
		memset(head,-1,sizeof(head));

		for(i=n;i>=1;i--) Add(0,i);
		index=flow=0;
		sink=n*n*(ans+1)+1;

		for(i=0;i<ans;i++) for(j=0;j<n*n;j++) {
			index++;
			for(k=0;k<con[j].size();k++) Add(index,index+con[j][k]);
		}
		for(i=1;i<=n;i++) Add(sink-i,sink);
		while(Mflow(ans)<n) {
			ans++;
			head[sink+n*n]=head[sink];
			for(i=1;i<=n;i++) {
				if(head[sink-i]>=0 && to[head[sink-i]]==sink) head[sink-i]=-1;
			}
			head[sink]=-1;
			index=sink-n*n-1;
			sink+=n*n;
			for(j=0;j<n*n;j++) {
				index++;
				if(head[index]>=0 && to[head[index]]==sink-n*n) head[index]=-1;
				for(k=0;k<con[j].size();k++) Add(index,index+con[j][k]);
			}
			for(j=0;j<n*n;j++) head[++index]=-1;
			for(i=1;i<=n;i++) Add(sink-i,sink);
			for(int i=head[sink];i>=0;i=next[i]) {
				int w=to[i];
				to[i]+=n*n;
				int v=to[i];

				int sto;
				sto=deleteEdge(v,sink);
				if(sto<0) while(1);
				sto=deleteEdge(w,v);
				if(sto<0) while(1);
				ADD(v,w,sto);
			}
		}
		printf("Case %d: %d\n",++ca,ans);
	}
}
