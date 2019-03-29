#include <cctype>
#include <cstdio>
#include <iostream>
#include <memory.h>
#include <algorithm>

#define N 100010

using namespace std;

const int inf = 1 << 30;

struct LinkCut_Tree {
	typedef int arr [N];

	int ch[N][2], pre[N];
	arr size;

	arr val, addv, setv;
	bool rev[N];

	arr Max1, cnt1;
	arr Max2, cnt2;

	void init() {
		memset(rev, 0, sizeof(rev));
		memset(ch, 0, sizeof(ch));
		memset(addv, 0, sizeof(addv));
		memset(pre, 0, sizeof(pre));
		memset(size, 0, sizeof(size));
		memset(cnt2, 1, sizeof(cnt2));
	}

	void push_up(int x ) {
		size[x] = size[ch[x][0]] + 1 + size[ch[x][1]];

		Max1[x] = val[x], cnt1[x] = 1;
		Max2[x] = -inf, cnt2[x] = 1;

		int ls = ch[x][0], rs = ch[x][1];
		updateMax(Max1[x], cnt1[x], Max2[x], cnt2[x], ls);
		updateMax(Max1[x], cnt1[x], Max2[x], cnt2[x], rs);
	}

	void AddV(int x ,int v) {
		if (x) {
			addv[x] += v ;
			val[x] += v ;
			Max1[x] += v ;
			if (Max2[x] != -inf) Max2[x] += v ;
		}
	}

	void SetV(int x, int v) {
		if (x) {
			addv[x] = 0;
			Max1[x] = v, cnt1[x] = size[x];
			Max2[x] = -inf, cnt2[x] = 1;
			setv[x] = v;
			val[x] = v;
		}
	}

	void push_down(int x) {
		if (setv[x] != inf) {
			SetV(ch[x][0], setv[x]);
			SetV(ch[x][1], setv[x]);
			setv[x] = inf;
		}
		if (addv[x]) {
			AddV(ch[x][0], addv[x]) ;
			AddV(ch[x][1], addv[x]) ;
			addv[x] = 0;
		}
		if (rev[x]) {
			swap(ch[x][0], ch[x][1]);
			rev[ch[x][0]] ^= 1;
			rev[ch[x][1]] ^= 1;
			rev[x] = 0;
		}
	}

	inline bool isroot(int x) { return ch[pre[x]][0] != x && ch[pre[x]][1] != x; }

	inline void down(int x) {
		if (!isroot(x)) down(pre[x]);
		push_down(x);
	}

	void rotate(int x, int f) {
		int y = pre[x], z = pre[y];
		ch[y][!f] = ch[x][f];
		pre[ch[x][f]] = y;
		pre[x] = pre[y];
		if (ch[z][0] == y) ch[z][0] = x;
		else if (ch[z][1] == y) ch[z][1] = x;
		pre[y] = x;
		ch[x][f] = y;
		push_up(y);
	}

	void splay(int x) {
		down(x);
		while (!isroot(x)) {
			if (isroot(pre[x])) rotate(x, ch[pre[x]][0] == x);
			else {
				int y = pre[x], z = pre[y];
				int f = (ch[z][0] == y);
				if (ch[y][f] == x) rotate(x, !f), rotate(x, f);
				else rotate(y, f), rotate(x, f);
			}
		}
		push_up(x);
	}

	void access(int u) {
		for (int f = 0; u; u = pre[u]) {
			splay(u);
			ch[u][1] = f;
			push_up(f = u);
		}
	}

	bool check(int a, int b) {
		int x = a, y = b;
		access(y);
		for (int f = 0; x; x = pre[x]) {
			splay(x);
			if (!pre[x]) break;
			f = x ;
		}
		for (; ch[x][1]; x = ch[x][1]);
		return x == b;
	}

	void make_root(int x) {
		access(x);
		splay(x);
		rev[x] ^= 1;
	}

	void link(int x, int y) {
		make_root(x);
		splay(x);
		pre[x] = y;
	}

	void cut(int x, int y) {
		make_root(x);
		splay(y);
		pre[ch[y][0]] = pre[y];
		pre[y] = ch[y][0] = 0;
	}

	void updateMax(int &m1, int &n1, int &m2, int &n2, int x) {
		if(!x) return;
		if (Max1[x] == m1) {
			n1 += cnt1[x];
			if (Max2[x] > m2) m2 = Max2[x], n2 = cnt2[x];
			else if (Max2[x] == m2) n2 += cnt2[x];
		} else if (Max1[x] > m1) {
			if (m1 == Max2[x]) m2 = m1, n2 = n1 + cnt2[x];
			else if(m1 > Max2[x]) m2 = m1, n2 = n1;
			else m2 = Max2[x], n2 = cnt2[x];
			n1 = cnt1[x];
			m1 = Max1[x];
		} else {
			if (m2 == Max1[x]) n2 += cnt1[x];
			else if (Max1[x] > m2) m2 = Max1[x], n2 = cnt1[x];
		}
	}

	void ADD(int x ,int y ,int add) {
		access(y);
		for (int f = 0; x; x = pre[x]) {
			splay(x);
			if (!pre[x]) {
				val[x] += add;
				Max1[x] += add;
				if (Max2[x] != -inf) Max2[x] += add;
				AddV(f, add);
				AddV(ch[x][1], add);
				return;
			}
			ch[x][1] = f;
			f = x;
			push_up(x);
		}
	}

	void SET(int x, int y, int s) {
		access(y);
		for (int f = 0; x ; x = pre[x]) {
			splay(x);
			if (!pre[x]) {
				val[x] = s;
				setv[x] = inf;
				Max1[x] = s, cnt1[x] = size[x];
				Max2[x] = -inf, cnt2[x] = 1;
				SetV(f, s);
				SetV(ch[x][1], s);
				return;
			}
			ch[x][1] = f;
			f = x;
			push_up(x);
		}
	}

	int QUERY(int x, int y, int &cnt) {
		access(y);
		for (int f = 0 ; x ; x = pre[x]) {
			splay(x);
			if (!pre[x]) {
				int n1 = 1, m1 = val[x], m2 = -inf, n2 = 0;
				updateMax(m1, n1, m2, n2, f);
				updateMax(m1, n1, m2, n2, ch[x][1]);
				cnt = n2;
				return m2;
			}
			ch[x][1] = f;
			f = x;
			push_up(x);
		}
		return -1;
	}
} LCT;

int head[N];
int next[N << 1], to[N << 1];

void AddEdge(int s, int e, int m) {
	to[m] = e;
	next[m] = head[s];
	head[s] = m;
}

void DFS(int u, int p = 0) {
	for (int i = head[u]; i; i = next[i]) {
		int v = to[i];
		if (v == p) continue;
		DFS(v, u);
		LCT.pre[v] = u;
	}
}

int main() {
	int T, R = 0, n, q;
	for (cin >> T; T --; ) {
		scanf("%d %d", &n, &q) ;
		LCT.init();
		for (int i = 1, j; i <= n ;i ++) {
			scanf("%d", &j);
			LCT.val[i] = j;
			LCT.setv[i] = inf;
			LCT.Max2[i] = -inf;
			head[i] = 0;
		}
		for (int m = 0, i = 1; i < n; i ++) {
			int u, v;
			scanf("%d %d", &u, &v);
			AddEdge(u, v, ++ m);
			AddEdge(v, u, ++ m);
		}
		DFS(1);
		printf("Case #%d:\n", ++ R);
		while (q --) {
			int k, u, v, a, b, c;
			int rlt, cnt;
			scanf("%d", &k);
			if (k == 1) {
				scanf("%d %d %d %d", &u, &v, &a, &b);
				LCT.cut(u, v);
				LCT.link(a, b);
			} else if (k == 2) {
				scanf("%d %d %d", &u, &v, &c);
				LCT.SET(u, v, c);
			} else if (k == 3) {
				scanf("%d %d %d", &u, &v, &c);
				LCT.ADD(u, v, c);
			} else{
				scanf("%d %d", &u, &v);
				rlt = LCT.QUERY(u, v, cnt);
				if (rlt == -inf) puts("ALL SAME");
				else printf("%d %d\n", rlt, cnt);
			}
		}
	}
	return 0;
}
