#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
const int MAXN = 100010;
const int MAXD = 40;
int ccc[MAXN*MAXD];
int *ccc_tail; //记得初始化ccc_tail = ccc
//0-based BinaryIndexTree
struct BIT{
	int *c;
	int n;
	void init(int _n){
		n = _n;
		c = ccc_tail;
		ccc_tail = ccc_tail + n;
		memset(c,0,sizeof(int)*n);
	}
	void add(int i,int val){
		while(i < n){
			c[i] += val;
			i += ~i & i+1;
		}
	}
	int sum(int i){
		i = min(i,n-1);
		int s = 0;
		while(i >= 0){
			s += c[i];
			i -= ~i & i+1;
		}
		return s;
	}
}bits[MAXN<<1];
struct Edge{
	int to,next;
}edge[MAXN*2];
int head[MAXN],tot;
void init(){
	tot = 0;
	memset(head,-1,sizeof(head));
}
inline void addedge(int u,int v){
	edge[tot].to = v;
	edge[tot].next = head[u];
	head[u] = tot++;
}
int size[MAXN],vis[MAXN],fa[MAXN],que[MAXN];
int TTT;
inline int getroot(int u,int &tot){
	int Min = MAXN, root = 0;
	int l,r;
	que[l = r = 1] = u;
	fa[u] = 0;
	for(;l <= r;l++)
		for(int i = head[que[l]];i != -1;i = edge[i].next){
			int v = edge[i].to;
			if(v == fa[que[l]] || vis[v] == TTT)continue;
			que[++r] = v;
			fa[v] = que[l];
		}
	tot = r;
	for(l--;l;l--){
		int x = que[l], Max = 0;
		size[x] = 1;
		for(int i = head[x];i != -1;i = edge[i].next){
			int v = edge[i].to;
			if(v == fa[x] || vis[v] == TTT)continue;
			Max = max(Max,size[v]);
			size[x] += size[v];
		}
		Max = max(Max,r - size[x]);
		if(Max < Min){
			Min = Max, root = x;
		}
	}
	return root;
}
struct Node{
	int root,subtree,dis;
	Node(int _root = 0, int _subtree = 0,int _dis = 0){
		root = _root;
		subtree = _subtree;
		dis = _dis;
	}
};
vector<Node>vec[MAXN];
int id[MAXN];
int dist[MAXN];
int val[MAXN];
int cnt;
inline void go(int u,int root,int subtree){
	int l,r;
	que[l = r = 1] = u;
	fa[u] = 0; dist[u] = 1;
	for(; l <= r;l++){
		u = que[l];
		vec[u].push_back(Node(id[root],subtree,dist[u]));
		for(int i = head[u];i != -1;i = edge[i].next){
			int v = edge[i].to;
			if(v == fa[u] || vis[v] == TTT)continue;
			que[++r] = v;
			fa[v] = u;
			dist[v] = dist[u] + 1;
		}
	}
	bits[subtree].init(r+1);
	for(int i = 1;i <= r;i++){
		u = que[i];
		bits[id[root]].add(dist[u],val[u]);
		bits[subtree].add(dist[u],val[u]);
	}
}
void solve(int u){
	int tot;
	int root = getroot(u,tot);
	vis[root] = TTT;
	id[root] = cnt++;
	vec[root].push_back(Node(id[root],-1,0));
	bits[id[root]].init(tot);
	bits[id[root]].add(0,val[root]);
	for(int i = head[root];i != -1;i = edge[i].next){
		int v = edge[i].to;
		if(vis[v] == TTT)continue;
		go(v,root,cnt);
		cnt++;
	}
	for(int i = head[root];i != -1;i = edge[i].next){
		int v = edge[i].to;
		if(vis[v] == TTT)continue;
		solve(v);
	}
}
int main()
{
    freopen("A.in", "r", stdin);
    int n,m;
	memset(vis,0,sizeof(vis));
	TTT = 0;
	while(scanf("%d%d",&n,&m) == 2){
		init();
		TTT++;
		ccc_tail = ccc;
		cnt = 0;
		for(int i = 1;i <= n;i++)vec[i].clear();
		for(int i = 1;i <= n;i++)scanf("%d",&val[i]);
		int u,v;
		for(int i = 1;i < n;i++){
			scanf("%d%d",&u,&v);
			addedge(u,v);
			addedge(v,u);
		}
		solve(1);
		char op[10];
		int d;
		while(m--){
			scanf("%s%d%d",op,&u,&d);
			if(op[0] == '!'){
				int dv = d - val[u];
				int size = vec[u].size();
				for(int i = 0;i < size;i++){
					Node tmp = vec[u][i];
					bits[tmp.root].add(tmp.dis,dv);
					if(tmp.subtree != -1)
						bits[tmp.subtree].add(tmp.dis,dv);
				}
				val[u] += dv;
			}
			else {
				int ans = 0;
				int size = vec[u].size();
				for(int i = 0;i < size;i++){
					Node tmp = vec[u][i];
					ans += bits[tmp.root].sum(d-tmp.dis);
					if(tmp.subtree != -1)
						ans -= bits[tmp.subtree].sum(d-tmp.dis);
				}
				printf("%d\n",ans);
			}
		}
	}
    return 0;
}
