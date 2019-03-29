//HDU 4875
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>

#include <list>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

#pragma comment(linker, "/STACK:266777216")

#define make_pair mp
#define X first
#define Y second
#define N 200100
#define min(a, b) ((a) < (b) ? (a) : (b))

using namespace std;

typedef __int64 INT;
typedef pair <int, int> pii;
typedef pair <INT, INT> PII;
typedef vector <int> vi;

const int inf = INT_MAX;
const INT INF = (1LL << 62) - 1;
const double DINF = 1e15;
const double pi = 3.1415926535897932384626433832795;
const double ep = 1e-8;

vi vec[N];
int pnt[N], height[N], dtime, st[N], en[N];
int NODE[N], tot, PNT[N];
int son[N][2], pa[N];
int addv[N], Addv[N];
int MinH[N], CMH[N], H[N];
int cnt[N], CNT[N];
int Size[N];
bool Start[N];

void AddEdge(int s, int e) {
	vec[s].push_back(e);
}

void DFS(int u, int dp, int tot) {
	dtime ++;
	cnt[dtime] = tot;
	pnt[dtime] = u;
	height[dtime] = dp;
	st[u] = dtime;
	int pen = 0;
	for (int i = 0; i < vec[u].size(); i ++) {
		pen ++;
		int v = vec[u][i];
		DFS(v, dp + 1, tot + pen);
	}
	dtime ++;
	cnt[dtime] = tot;
	pnt[dtime] = u;
	height[dtime] = dp;
	en[u] = dtime;
}

int NEW_NODE() {
	Size[++ tot] = 1;
	son[tot][0] = son[tot][1] = pa[tot] = 0;
	addv[tot] = Addv[tot] = 0;
	return tot;
}

void push_up(int rt) {
	Size[rt] = 1;
	MinH[rt] = H[rt];
	CMH[rt] = 1;
	if (son[rt][0]) {
		int ls = son[rt][0];
		Size[rt] += Size[ls];
		if (MinH[rt] == MinH[ls]) CMH[rt] += CMH[ls];
		else if (MinH[rt] > MinH[ls]) MinH[rt] = MinH[ls], CMH[rt] = CMH[ls];
	}
	if (son[rt][1]) {
		int rs = son[rt][1];
		Size[rt] += Size[rs];
		if (MinH[rt] == MinH[rs]) CMH[rt] += CMH[rs];
		else if (MinH[rt] > MinH[rs]) MinH[rt] = MinH[rs], CMH[rt] = CMH[rs];
	}
}

void push_down(int rt) {
	int ls=son[rt][0], rs=son[rt][1];
	if (addv[rt]) {
		if (ls) addv[ls] += addv[rt], H[ls] += addv[rt], MinH[ls] += addv[rt];
		if (rs) addv[rs] += addv[rt], H[rs] += addv[rt], MinH[rs] += addv[rt];
		addv[rt]=0;
	}
	if (Addv[rt]) {
		if (ls) Addv[ls] += Addv[rt], CNT[ls] += Addv[rt];
		if (rs) Addv[rs] += Addv[rt], CNT[rs] += Addv[rt];
		Addv[rt] = 0;
	}
}

void print(int rt) {
	push_down(rt);
	if (son[rt][0]) print(son[rt][0]);
	printf("(%d %d)", rt, PNT[rt]);
	if (son[rt][1]) print(son[rt][1]);
}

int rot(int rt, int c) {
	int y=pa[rt], z=pa[y];
	push_down(y), push_down(rt);
	son[y][!c]=son[rt][c];
	if (son[rt][c]) pa[son[rt][c]]=y;
	pa[rt]=z;
	if (z) {
		if (y==son[z][0]) son[z][0]=rt;
		else son[z][1]=rt;
	}
	son[rt][c]=y, pa[y]=rt;
	push_up(y);
}

int Splay(int x, int to) {
	while (pa[x]!=to) {
		if (pa[pa[x]]==to) rot(x, x==son[pa[x]][0]);
		else {
			if (x==son[pa[x]][0]) {
				if (pa[x]==son[pa[pa[x]]][0]) rot(pa[x], 1), rot(x, 1);
				else rot(x, 1), rot(x, 0);
			} else {
				if (pa[x]==son[pa[pa[x]]][1]) rot(pa[x], 0), rot(x, 0);
				else rot(x, 0), rot(x, 1);
			}
		}
	}
	push_up(x);
}

int build(int l, int r) {
	if (l > r) return 0;
	int m = (l + r) >> 1;
	int tmp = NEW_NODE();
	MinH[tmp] = H[tmp] = height[m];
	CNT[tmp] = cnt[m];
	NODE[m] = tmp;
	PNT[tmp] = pnt[m];
	CMH[tmp] = 1;
	son[tmp][0] = build(l, m - 1);
	son[tmp][1] = build(m + 1, r);
	if (son[tmp][0]) {
		int ls = son[tmp][0];
		pa[ls] = tmp;
		Size[tmp] += Size[ls];
		if (MinH[tmp] == MinH[ls]) CMH[tmp] += CMH[ls];
		else if (MinH[tmp] > MinH[ls]) MinH[tmp] = MinH[ls], CMH[tmp] = CMH[ls];
	}
	if (son[tmp][1]) {
		int rs = son[tmp][1];
		pa[rs] = tmp;
		Size[tmp] += Size[rs];
		if (MinH[tmp] == MinH[rs]) CMH[tmp] += CMH[rs];
		else if (MinH[tmp] > MinH[rs]) MinH[tmp] = MinH[rs], CMH[tmp] = CMH[rs];
	}
	return tmp;
}

int FIND(int x, int k, int &rt) {
	k *= 2;
	int S = NODE[st[x]];
	int E = NODE[en[x]];
	Splay(S, 0);
	rt = S;
	Splay(E, rt);
	int cur = son[E][0], tot = 0;
	if (!cur) return x;
	if (!k || CMH[cur] < k) return x;
	int DP = MinH[cur];
	while (cur) {
		push_down(cur);
		int ls = son[cur][0], rs = son[cur][1];
		if (ls) {
			if (DP == MinH[ls] && tot + CMH[ls] >= k) {
				cur = ls;
				continue;
			}
		}
		if (MinH[ls] == DP) tot += CMH[ls];
		if (H[cur] == DP) tot ++;
		if (tot == k && H[cur] == DP) break;
		cur = rs;
	}
	return PNT[cur];
}

void CHANGE(int x, int p, int c, int y, int q, int &rt) {
	int px, py;
	px = FIND(x, p - 1, rt);
	py = FIND(x, p + c, rt);
	int u, v;
	if (px == x) u = st[x];
	else u = en[px];
	if (py == x) v = en[x];
	else v = st[py];
	if (v != en[x]) {
		Splay(NODE[v], 0);
		rt = NODE[v];
		CNT[NODE[v]] -= c;
		Splay(NODE[en[x]], rt);
		int cur = NODE[en[x]];
		int tp = son[cur][0];
		CNT[tp] -= c;
		Addv[tp] -= c;
	}
	Splay(NODE[u], 0);
	rt = NODE[u];
	Splay(NODE[v], rt);
	int cur = NODE[v];
	int Remove = son[cur][0];
	int Q = CNT[NODE[u]] + 1;
	son[cur][0] = 0;
	push_up(cur);
	push_up(pa[cur]);
	px = FIND(y, q, rt);
	py = FIND(y, q + 1, rt);
	if (px == y) u = st[y];
	else u = en[px];
	if (py == y) v = en[y];
	else v = st[py];
	if (v != en[y]) {
		Splay(NODE[v], 0);
		rt = NODE[v];
		CNT[rt] += c;
		Splay(NODE[en[y]], rt);
		int cur = NODE[en[y]];
		int tp = son[cur][0];
		CNT[tp] += c;
		Addv[tp] += c;
	}
	int QQ = CNT[NODE[u]] + 1;
	Splay(NODE[u], 0);
	rt = NODE[u];
	Splay(NODE[v], rt);
	cur = NODE[v];
	son[cur][0] = Remove;
	pa[Remove] = cur;
	addv[Remove] += H[NODE[st[y]]] - H[NODE[st[x]]];
	H[Remove] += H[NODE[st[y]]] - H[NODE[st[x]]];
	MinH[Remove] += H[NODE[st[y]]] - H[NODE[st[x]]];
	Addv[Remove] += QQ - Q;
	CNT[Remove] += QQ - Q;
	push_up(cur);
	push_up(pa[cur]);
}

int DIST(int x, int y, int &rt) {
	if (x == y) return 0;
	int px = NODE[st[x]];
	int py = NODE[en[y]];
	Splay(px, 0);
	rt = px;
	Splay(py, rt);
	int cur;
	if (py == son[rt][1]) cur = son[py][0];
	if (py == son[rt][0]) cur = son[py][1];
	if (!cur) return 0;
	int nh = min(H[px], H[py]);
	int xh = H[px] + H[py] - nh;
	int hh = MinH[cur];
	if (hh > nh) return xh - nh - 1;
	return nh + xh - hh - hh;
}

int COUNT(int x, int &rt) {
	int px = NODE[st[x]];
	Splay(px, 0);
	rt = px;
	return CNT[px];
}

int main() {
	int rt;

	int n, q, m = 0;
	scanf("%d %d", &n, &q);
	for (int i = 1, j, k; i <= n; i ++) {
		scanf("%d", &j);
		while (j --) {
			scanf("%d", &k);
			AddEdge(i, k);
		}
	}

	dtime = 0;
	DFS(1, 1, 0);

	tot = 0;
	pnt[n << 1 | 1] = n + 1;
	height[0] = height[n << 1 | 1] = N;
	rt = build(0, n << 1 | 1);

	while (q --) {
		int type;
		scanf("%d", &type);
		if (type == 1) {
			int x, p, c, y, q;
			scanf("%d %d %d %d %d", &x, &p, &c, &y, &q);
			CHANGE(x, p, c, y, q, rt);
		} else if (type == 2) {
			int x, y;
			scanf("%d %d", &x, &y);
			printf("%d\n", DIST(x, y, rt));
		} else {
			int x;
			scanf("%d", &x);
			printf("%d\n", COUNT(x, rt));
		}
	}

	return 0;
}
