//Yokohama 2006 / Enjoyable Communication
//O(V^2 * E * K), constant is small

#include <iostream>
#include <queue>
#include <set>
#include <memory.h>
#include <cstdio>
#include <climits>

#define N 51
#define Q 300000

using namespace std;

const int inf = 300000000;

struct Path {
	int p[N];
	int n, heri, len;
} now, next, que[Q];

struct cmp {
	bool operator() (const int &a, const int &b) {
		if (que[a].len != que[b].len) return que[a].len < que[b].len;
		int n = que[a].n;
		if (que[a].n > que[b].n) n = que[b].n;
		for (int i = 0; i < n; i ++) if (que[a].p[i] != que[b].p[i]) return que[a].p[i] < que[b].p[i];
		return que[a].n < que[b].n;
	}
};

int val[N];
set<int, cmp> arr;
set<int, cmp>::iterator it;
int con[N][N], cn[N];
int dis[N][N];
int prev[N];
int chk[N];
int vis[N], vn;
int n, m, K, ST, EN, chknum, minv, lim;
int extn;

int dijkstra(int st, int en) {
	int idx, sel, maxd, i, u;
	memset(val, 31, sizeof(val));
	val[st] = 0;
	idx = st;
	chk[idx] = chknum;
	memset(prev, 0xff, sizeof(prev));
	if (st == en) return 0;
	while (true) {
		maxd = inf;
		for (i = 1; i <= n; i ++) if (chk[i] != chknum) {
			if (val[i] > val[idx] + dis[i][idx]) {
				val[i] = val[idx] + dis[i][idx];
				prev[i] = idx;
			} else if (val[i] == val[idx] + dis[i][idx]) {
				if (prev[i] == -1 || prev[i] > idx) prev[i] = idx;
			}
			if (maxd > val[i]) {
				maxd = val[i];
				sel = i;
			}
		}
		idx = sel;
		if (maxd > lim) return -1;
		if (idx == en) return val[en];
		chk[idx] = chknum;
	}
}

bool Solve() {
	int u, v, i, j, d, k;
	minv = lim = inf - 1;
	arr.clear();
	++ chknum;
	d = dijkstra(EN, ST);
	if (d == -1) return false;
	now.len = d;
	now.n = 0;
	for (i = ST; i >= 0; i = prev[i]) now.p[now.n ++] = i;
	now.heri = 0;
	extn = 0;
	que[extn ++] = now;
	arr.insert(0);
	int step, tot, sum;
	for (step = 0; step < K - 1; step ++) {
		if (arr.empty()) break;
		now = que[*arr.begin()];
		arr.erase(arr.begin());
		for (i = now.heri; i < now.n - 1; i ++) {
			u = now.p[i];
			next.heri = i + 1;
			int tmptot = 0, tmpsum = 0;
			vn ++;
			for (k = 0; k <= i; k ++) {
				next.p[tmptot ++] = now.p[k];
				vis[now.p[k]] = vn;
				if (k > 0) tmpsum += dis[now.p[k - 1]][now.p[k]];
			}
			for (j = 0; j < cn[u]; j ++) {
				v = con[u][j];
				if (v == now.p[i + 1]) continue;
				if (vis[v] == vn) continue;
				chknum ++;
				for (k = 0; k <= i; k ++) chk[now.p[k]] = chknum;
				tot = tmptot;
				sum = tmpsum + dis[u][v];
				lim = minv - sum;
				d = dijkstra(EN, v);
				if (d == -1) continue;
				sum += d;
				for (k = v; k >= 0; k = prev[k]) next.p[tot ++] = k;
				next.len = sum;
				next.n = tot;
				que[extn ++] = next;
				arr.insert(extn - 1);
				while (arr.size() >= K - step) {
					it = arr.end();
					it --;
					arr.erase(it);
					int tp = que[(*it)].len;
					if (minv > tp) minv = tp;
				}
			}
		}
	}
	if (arr.empty()) return false;
	now = que[*arr.begin()];
	for (i = 0; i < now.n; i ++) {
		if (i) cout << "-";
		cout << now.p[i];
	}
	cout << endl;
	return true;
}

int main(){
	int i, a, b, c;
	while (true) {
		scanf("%d %d %d %d %d ", &n, &m, &K, &ST, &EN);
		if (!n) break;
		memset(cn, 0, sizeof(cn));
		memset(dis, 31, sizeof(dis));
		for (i = 0; i < m; i ++) {
			scanf("%d %d %d", &a, &b, &c);
			con[a][cn[a] ++] = b;
			dis[a][b] = c;
		}
		if (!Solve()) cout << "None"<< endl;
	}
	return 0;
}
