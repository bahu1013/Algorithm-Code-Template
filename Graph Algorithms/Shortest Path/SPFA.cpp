#include <stdio.h>
#include <vector>
#include <bitset>
#include <memory.h>
#include <queue>
using namespace std;
#define inf 1000000000
#define N 1000100

struct node {
	int e, v;
	node (int a = 0,int b = 0): e(a), v(b){}
};

vector <vector<node> > path;
int n,p,q;
int dist[N];

bool SPFA(int src) {
	int i,j,k,now,l;
	node next;
	bitset <N> vis;
	queue <int> SQ;
	for (i=0; i<n; i++) dist[i]=inf;
	SQ.push(src);
	vis[src]=true, dist[src]=0;
	for (i=0;i<=n;i++) {
		l=SQ.size();
		if (l==0) break;
		while (l--) {
			now=SQ.front(), SQ.pop();
			vis[now]=false;
			for (j=path[now].size()-1; j>=0; j--) {
				next=path[now][j];
				if (dist[next.e]>dist[now]+next.v) {
					dist[next.e]=dist[now]+next.v;
					if (!vis[next.e]) {
						SQ.push(next.e);
						vis[next.e]=true;
					}
				}
			}
		}
	}
	return SQ.empty();	//return 1 mean there is negative cycle.
}

int main() {
	int m, i, j, k, src;
	scanf("%d %d", &n, &m);
	path.resize(n+1);
	for (i=0; i<n; i++) path[i].clear();
	while (m--) {
		scanf ("%d %d %d", &i, &j, &k);
		path[i].push_back(node(j, k));
	}
	scanf("%d", &src);
	SPFA(src);
	for (i=0; i<n; i++) printf("Distance %d->%d: %d.\n", src, i, dist[i]);
}
