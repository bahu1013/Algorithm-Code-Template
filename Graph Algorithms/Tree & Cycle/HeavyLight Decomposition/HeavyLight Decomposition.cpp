//HDU 5029
#include <stdio.h>
#include <vector>
#include <time.h>
#include <memory.h>
#include <algorithm>
using namespace std;
#define M 100100

vector<int>v[M];
int size[M], hson[M];
int top[M];
int id[M], fid[M], idx, fa[M], dep[M];
int mx[M<<2];
int ans[M];
int n, Q;
vector<int>q[M];

void init(){
	for(int i=0; i<M; i++)v[i].clear();
	for(int i=0; i<M; i++)q[i].clear();
	memset(mx, 0, sizeof(mx));
	idx=0;
	fa[1]=0;
	dep[1]=0;
}

void push_up(int id){
	mx[id] = max(mx[id<<1], mx[id<<1|1]);
}

void update(int id, int st, int en, int z, bool bf){
	if(st==en){
		if(bf)mx[id]++;
		else mx[id]--;
		return;
	}
	int mid=(st+en)>>1;
	if(mid>=z)update(id<<1, st, mid, z, bf);
	else update(id<<1|1, mid+1, en, z, bf);
	push_up(id);
}

int query(int id, int st, int en){
	if(st==en)
		return st;
	int mid=(st+en)>>1;
	if(mx[id<<1]==mx[1])return query(id<<1, st, mid);
	else return query(id<<1|1, mid+1, en);
}

void dfs(int u){
	size[u]=1;
	hson[u]=0;
	for(int j, i=0; i<v[u].size(); i++){
		j=v[u][i];
		if(j==fa[u])continue;
		fa[j]=u;
		dep[j]=dep[u]+1;
		dfs(j);
		size[u]+=size[j];
		if(!hson[u] || size[hson[u]]<size[j])
			hson[u]=j;
	}
}

void DFS(int u, int tp){
	id[u]=++idx;
	fid[idx]=u;
	top[u]=tp;
	if(!hson[u])return;
	DFS(hson[u], tp);
	for(int j, i=0; i<v[u].size(); i++){
		j=v[u][i];
		if(j==fa[u] || j==hson[u])continue;
		DFS(j, j);
	}
}

void decompose(){
	DFS(1, 1);
}

void Update(int a, int b, int z){
	int cnt=0;
	while(top[a]!=top[b]){
		if(dep[top[a]]>dep[top[b]]){
			q[id[a]+1].push_back(-z);
			q[id[top[a]]].push_back(z);
			a=fa[top[a]];
		}else{
			q[id[b]+1].push_back(-z);
			q[id[top[b]]].push_back(z);
			b=fa[top[b]];
		}
	}
	if(dep[a]>dep[b])swap(a, b);
	q[id[a]].push_back(z);
	q[id[b]+1].push_back(-z);
}

void read(int &x){
	x=0;
	char c;
	while(1){
		c=getchar();
		if(c<'0' || c>'9')continue;
		break;
	}
	while(1){
		x=x*10+(c-'0');
		c=getchar();
		if(c<'0' || c>'9')break;
	}
}
void read(int &x, int &y){
	read(x);read(y);
}
void read(int &x, int &y, int &z){
	read(x), read(y), read(z);
}

int main(){
	double result=0;
	while(1){
		read(n, Q);
		if(!n)return 0;
		init();
		for(int a, b, i=1; i<n; i++){
			//scanf("%d %d", &a, &b);
			read(a, b);
			v[a].push_back(b);
			v[b].push_back(a);
		}
		dfs(1);
		decompose();
		int a, b, z;
		double x=clock();
		while(Q--){
			//scanf("%d %d %d", &a, &b, &z);
			read(a, b, z);
			Update(a, b, z);
		}
		for(int i=1; i<=n; i++){
			for(int j=0; j<q[i].size(); j++){
				update(1, 1, n, q[i][j]>0?q[i][j]:-q[i][j], q[i][j]>0);
			}
			if(mx[1])ans[fid[i]]=query(1, 1, n);
			else ans[fid[i]]=0;
		}
		for(int i=1; i<=n; i++)
			printf("%d\n", ans[i]);
		result+=clock()-x;
     }
     fprintf(stderr, "clock=%.3lf\n", result);
	return 0;
}
