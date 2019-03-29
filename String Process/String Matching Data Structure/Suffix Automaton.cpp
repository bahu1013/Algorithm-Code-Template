#include <cstdio>
#include <cstring>

using namespace std;

const int N = 100100;
const int C = 256;

struct SuffixAutomaton {
	#define SZ (N << 1)

	struct Node {
		int link, deep;
		int next[C];
		void clear() {
			link = -1;
			deep = 0;
			memset(next, -1, sizeof(next));
		}
	};
	Node node[SZ];
	int size, last;

	void init() {
		node[0].clear();
		size = 1;
		last = 0;
	}

	void insert(int c) {
		int cur = size ++;
		node[cur].clear();
		node[cur].deep = node[last].deep + 1;

		int p = last;

		while (p != -1 && node[p].next[c] == -1) {
			node[p].next[c] = cur;
			p = node[p].link;
		}

		if (p == -1) node[cur].link = 0;
		else {
			int q = node[p].next[c];
			if (node[q].deep == node[p].deep + 1) node[cur].link = q;
			else {
				int clone = size ++;
				node[clone] = node[q];
				node[clone].deep = node[p].deep + 1;
				node[cur].link = node[q].link = clone;

				while (p != -1 && node[p].next[c] == q) {
					node[p].next[c] = clone;
					p = node[p].link;
				}
			}
		}

		last = cur;
	}

	int cnt[SZ], ord[SZ];

	int build(char *a, int len = 0) {
		len = strlen(a);
		for (int i = 0; i < len; i ++) insert(a[i]);
		for (int i = 0; i <= len; i++) cnt[i] = 0;
		for (int i = 0; i < size; i ++) cnt[node[i].deep] ++;
		for (int i = 1; i <= len; i ++) cnt[i] += cnt[i - 1];
		for (int i = 0; i < size; i ++) ord[-- cnt[node[i].deep]] = i;
	}
} SAM;

char s[N];

int main() {
	strcpy(s, "aabbabb");

	SAM.init();
	SAM.build(s);

	printf("Size = %d, Last = %d\n\n", SAM.size, SAM.last);
	for (int i = 0; i < SAM.size; i ++) {
		printf("Node[%d]\n", i);
		printf("  link: %d, deep: %d\n", SAM.node[i].link, SAM.node[i].deep);
		printf("  next['a'] = %d, next['b'] = %d\n", SAM.node[i].next['a'], SAM.node[i].next['b']);
		puts("\n");
	}

	return 0;
}

// Code 2
#include <cstdio>
#include <memory.h>

#define N 100010

const int SZ = N << 1;
const int SIGMA = 26;

struct Node {

	Node *next[SIGMA], *link;
	int len;

	void init() {
		memset(next, NULL, sizeof(next));
		link = NULL;
		len = 0;
	}
};

struct SuffixAutumaton {

	Node sam[SZ], *head, *last;
	int size;

	void init() {
		sam[0].init();
		head = last = &sam[0];
		size = 1;
	}

	void insert(int x) {
		Node *p = &sam[size ++], *u = last;
		p->init();
		p->len = last->len + 1;
		last = p;
		for (;u && !u->next[x]; u = u->link) u->next[x] = p;
		if (!u) p->link = head;
		else if (u->next[x]->len == u->len + 1) p->link = u->next[x];
		else {
			Node *r = &sam[size ++], *q = u->next[x];
			*r = *q;
			r->len = u->len + 1;
			p->link = q->link = r;
			for (; u && u->next[x] == q; u = u->link) u->next[x] = r;
		}
	}

	Node *ord[N];
	int d[SZ];

	void build(char *s) {
		int len = strlen(s);
		for (int i = 0; i < len; i ++) insert(s[i] - 'a');
		//Sort nodes by deep...
		for (int i = 0; i <= len; i ++) d[i] = 0;
		for (int i = 0; i < size; i ++) d[sam[i].len] ++;
		for (int i = 1; i <= len; i ++) d[i] += d[i - 1];
		for (int i = 0; i < size; i ++) ord[-- d[sam[i].len]] = &sam[i];
	}
} SAM;

char s[N];

int main() {
	strcpy(s, "aabbabb");

	SAM.init();
	SAM.build(s);

	printf("Size = %d, Last = %X\n\n", SAM.size, SAM.last);

	for (int i = 0; i < SAM.size; i ++) {
		printf("Node[%d]\n", i);
		printf("  link: %X, deep: %d\n", SAM.sam[i].link, SAM.sam[i].len);
		printf("  next['a'] = %X, next['b'] = %X\n", SAM.sam[i].next[0], SAM.sam[i].next[1]);
		puts("\n");
	}

	return 0;
}
