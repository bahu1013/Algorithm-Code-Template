#include <cstdio>
#include <iostream>
#include <memory.h>

using namespace std;

int K;

typedef __int64 INT;

const int L = 100100;
const int SIGMA = 26;
const int MOD = 1000000007;

struct Automaton {

	struct Node {
		int next[SIGMA];
		int link;
	};
	Node node[L];

	int sz, last;

	int init() {
		sz = 1;
		last = 0;
		node[last].link = -1;
		memset(node[last].next, 0, sizeof(node[last].next));
	}

	int insert(int c) {
		int cur = sz ++;
		node[last].next[c] = cur;

	//	make link
		int p = node[last].link;
		while (p != -1 && node[p].next[c] != p + 1) p = node[p].link;
		if (p == -1) node[cur].link = 0;
		else node[cur].link = node[p].next[c];

	//	make next
		for (int t = 0; t < K; t ++) {
			p = node[cur].link;
			while (p != -1 && node[p].next[t] != p + 1) p = node[p].link;
			if (p == -1) node[cur].next[t] = 0;
			else node[cur].next[t] = node[p].next[t];
		}
		last = cur;
	}

	void build(char *s) {
		int len = strlen(s);
		for (int i = 0; i < len; i ++) insert(s[i] - 'a');
	}
} AM;

INT P[L];
char S[L];

int main() {
	int T;
	cin >> T;
	while (T --) {
		scanf("%d%s", &K, S);
		int L = strlen(S);
		AM.init();
		AM.build(S);

		P[0] = 0, P[1] = K;
		for (int i = 1; i < L; i ++) {
			INT rlt = (P[i] * K + K) % MOD;
			for (char c = 0; c < K; c ++) {
				if (AM.node[i].next[c] == i + 1) continue;
				rlt -= P[AM.node[i].next[c]];
				if (rlt < 0) rlt += MOD;
			}
			P[i + 1] = rlt;
		}
		cout << P[L] << endl;
	}
}
