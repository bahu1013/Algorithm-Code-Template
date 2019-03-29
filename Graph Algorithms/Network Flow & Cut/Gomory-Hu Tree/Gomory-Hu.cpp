#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define clr(u) memset(u, 0, sizeof(u))
#define FOR(i,s,e) for (int i=(s); i<(e); i++)
#define N 205
#define M 2005
using namespace std;

struct node{
	int x, s;
	bool operator < (node const &T) const{return s < T.s;}
};

int n, m, ed, x, y, z, S, T, V;
int flag[N], g[N], p[N], l[N];
int qd[M], qn[M], qc[M], qr[M];
int flow[N][N], Tree[N][N];
priority_queue<node> q;

void add(int x, int y, int c){
	qd[++ed] = y, qn[ed] = l[x], l[x] = ed, qc[ed] = qr[ed] = c;
}

int ISAP(int x, int y){
	int mn = V - 1, F = 0, R = y, t;
	if (x == T) return y;
	for (int i=l[x]; i; i=qn[i]){
		if (qc[i] > 0){
			if (flag[x] == flag[qd[i]]+1){
				t = ISAP(qd[i], min(qc[i], R));
				qc[i] -= t;
				qc[i^1] += t;
				R -= t;
				F += t;
				if (flag[S] >= V) return F;
				if (!R) break;
			}
			mn = min(mn, flag[qd[i]]);
		}
	}
	if (!F){
		g[flag[x]]--;
		if (!g[flag[x]]) flag[S] = V;
		flag[x] = mn+1;
		g[flag[x]]++;
	}
	return F;
}

int MaxFlow(){
	for(int i=1; i<=ed; i++)qc[i] = qr[i];
	clr(flag), clr(g);
	int ret = 0;
	g[0] = V;
	while (flag[S] < V) ret += ISAP(S, 1<<30);
	return ret;
}

void FC(int x){
	flag[x] = 1;
	for(int i=l[x]; i; i=qn[i]) if (qc[i] && !flag[qd[i]]) FC(qd[i]);
}

void solve(){
	int ret = 0;
	for(int i=1; i<=n; i++)p[i] = 1;
	for(int i=2; i<=n; i++){
		for (int j=2; j<=ed; j++) qc[j] = qr[j];
		S = i, T = p[i], V = n;
		int F = MaxFlow();
		clr(flag);
		FC(i);
		for (int j=i+1; j<=n; j++)
			if (flag[j] && p[j] == p[i]) p[j] = i;
		Tree[p[i]][i] = F;
		ret += F;
	}

	printf("%d\n", ret);
	clr(flag);
	printf("1 ");
	flag[1] = 1;
	for(int i=1; i<=n; i++)if(Tree[1][i]) q.push((node){i, Tree[1][i]});
	while (!q.empty()){
		node t = q.top(); q.pop();
		printf("%d ", t.x);
		flag[t.x] = 1;
		for(int i=1; i<=n; i++)if (Tree[t.x][i] && !flag[i]) q.push((node){i, Tree[t.x][i]});
	}
}

int main(){
	scanf("%d%d", &n, &m);
	ed = 1;
	while (m--) scanf("%d%d%d", &x, &y, &z), add(x, y, z), add(y, x, z);
	solve();
	return 0;
}
