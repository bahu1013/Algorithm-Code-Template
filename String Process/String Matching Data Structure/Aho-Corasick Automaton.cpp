#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int N = 500100;
const int SIGMA = 2;

#pragma comment(linker, "/STACK:1024000000,1024000000")
#define idx(c) (c - '0')

struct AhoCorasickTrie {
	struct Node {
		int next[SIGMA];
		int val, link;
	};

	Node node[N];
	int sz;

	int newnode() {
		memset(node[sz].next, 0, sizeof(int) * SIGMA);
		node[sz].val = 0;
		node[sz].link = 0;
		sz ++;
		return sz - 1;
	}

	void init() {
		sz = 0;
		newnode();
	}

	int insert(char *s) {
		int u = 0;
		for (int i = 0; s[i]; i ++) {
			int c = idx(s[i]);
			if (!node[u].next[c]) node[u].next[c] = newnode();
			u = node[u].next[c];
		}
		node[u].val = 1;
		return u;
	}

	bool search(char *s) {
		int u = 0;
		for (int i = 0; s[i] ; i ++) {
			int c = idx(s[i]);
			if (!node[u].next[c]) return 0;
			u = node[u].next[c];
		}
		return node[u].val;
	}

	void GetLink() {
		queue <int> Q;

		for(int i = 0; i < SIGMA; i ++) if (node[0].next[i]) Q.push(node[0].next[i]);

		while (!Q.empty()) {
			int r = Q.front(); Q.pop();
			for (int c = 0; c < SIGMA; c ++) {
				int u = node[r].next[c];
				if (!u) continue;
				Q.push(u);
				int v = node[r].link;
				while (v && !node[v].next[c]) v = node[v].link;
				node[u].link = node[v].next[c];
			}
		}
	}

	int find(char *T) {
		int j = 0, ans = 0;
		for(int i = 0; T[i]; i ++) {
			int c = idx(T[i]);

			while (j && !node[j].next[c]) j = node[j].link;
			j = node[j].next[c];

			int tp = j;
			while (tp) { //while (tp && node[tp].val)
				ans += node[tp].val;
				tp = node[tp].link;
			}
		}
		return ans;
	}
};
AhoCorasickTrie ac, buf;

void dfs(int u, int v) {
	for (int i = 0; i < SIGMA; i ++) {
		if (buf.node[v].next[i]) {
			int e2 = buf.node[v].next[i];
			if (!ac.node[u].next[i]) ac.node[u].next[i] = ac.newnode();
			int e1 = ac.node[u].next[i];
			ac.node[e1].val |= buf.node[e2].val;
			dfs(e1, e2);
		}
	}
}

void join() {
	dfs(0, 0);
	buf.init();
	ac.GetLink();
}

#define L 6000000

char s[L], temp[L];

int main(){
	int R = 0, T, n;
	for (scanf("%d", &T); T --; ) {
		scanf("%d", &n);
		printf("Case #%d:\n", ++ R);
		ac.init();
		buf.init();
		int rlt = 0;
		while (n --) {
			scanf("%s", temp);
			int len = strlen(temp + 1);
			s[0] = temp[0];
			for (int i = 0; i < len ; i ++) s[i + 1] = temp[1 + (i +rlt % len + len) % len];
			s[len + 1] = 0;
			if (s[0] == '+') {
				if (buf.search(s + 1) || ac.search(s + 1)) continue;
				buf.insert(s + 1);
				buf.GetLink();
				if (buf.sz > 2000) join();
			} else {
				rlt = buf.find(s + 1) + ac.find(s + 1);
				printf("%d\n", rlt);
			}
		}
	}
	return 0;
}
