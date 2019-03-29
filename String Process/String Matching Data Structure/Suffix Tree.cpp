#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int SIGMA = 256;

struct Node {
	int l, r, pardp, chdNum;	//S[l, r)
	Node *par, *sLink;
	Node *chd[SIGMA];

	Node() {
		l = r = pardp = chdNum = 0;
		par = sLink = NULL;
		for (int i = 0; i < SIGMA; i ++) chd[i] = NULL;
	}

	inline int len() { return r - l; }
	inline int depth() { return pardp + len(); }
	inline bool inEdge(int pos) { return pardp <= pos && pos < depth(); }

	void setEdge(Node *child, int l, int r, char *s) {
		chd[s[l]] = child;
		chdNum++;
		child -> par = this;
		child -> pardp = depth();
		child -> l = l, child -> r = r;
	}
};

struct SuffixTree {
	char *S;
	int m, jj;
	bool needWalk;
	Node *root, *cur, *needSLink;
	vector <Node> V;
	int size;

	void assign(char *str) {
		S = str;
		m = strlen(S);
		size = 0;
		V.clear();
		V.reserve(m * 2 + 10);
		root = newNode();
		cur = newNode();
		root -> setEdge(cur, 0, m, S);
		needSLink = NULL;
		jj = 1;
		needWalk = 1;
	}

	Node *newNode() {
		V[size] = Node();
		return &V[size ++];
	}

	void walkDown(int j, int i) {
		if (i < j) return;
		for (int h = j + cur -> depth(); !cur -> inEdge(i - j); h += cur -> len()) cur = cur -> chd[S[h]];
	}

	void addSLink() {
		if (needSLink) needSLink -> sLink = cur;
		needSLink = NULL;
	}

	void extend(int i) {
		int k, pos;
		char c = S[i + 1];
		Node *leaf, *split;

		for (; jj <= i + 1; jj ++) {
			if (needWalk) {
				if (!cur -> sLink && cur -> par) cur = cur -> par;
				cur = (cur -> sLink) ? cur -> sLink : root;
				walkDown(jj, i);
			}
			needWalk = 1;
			k = i - jj + 1;
			if (k == cur -> depth()) {
				addSLink();
				if (cur -> chd[c]) {
					cur = cur -> chd[c];
					needWalk = 0;
					break;
				} else {
					leaf = newNode();
					cur -> setEdge(leaf, i + 1, m, S);
				}
			} else {
				pos = cur -> l + k - cur -> pardp;
				if (S[pos] == c) {
					addSLink();
					if (pos != i + 1) {
						needWalk = 0;
						break;
					}
				} else {
					split = newNode();
					leaf = newNode();
					cur -> par -> setEdge(split, cur -> l, pos, S);
					cur -> par -> chdNum--;
					split -> setEdge(cur, pos, cur -> r, S);
					split -> setEdge(leaf, i + 1, m, S);
					cur = split;
					addSLink();
					if (cur -> depth() == 1) cur -> sLink = root;
					else needSLink = cur;
				}
			}
		}
	}

	void build(char *str) {
		assign(str);
		for (int i = 0; i < m; i ++) extend(i);
	}

	void DFS(Node *p) {
		if (!(p -> chdNum)) return;
		for (int i = 0; i < SIGMA; i ++) {
			if (p -> chd[i]) DFS(p -> chd[i]);
		}
	}

	bool match(Node *p, char *t, int n) {
		int k;
		Node *q = p -> chd[t[0]];

		if (!q) return 0;
		k = min(n, q -> len());
		if (strncmp(S + q -> l, t, k)) return 0;
		if (k == n) return 1;
		return match(q, t + k, n - k);
	}

	void output(Node *p, int dp) {
		int i;
		if (dp == 0) printf("Root");

		for (i = 0; i < dp; i ++) {
			if (i < dp - 1) putchar('\t');
			else {
				putchar('|');
				for (i = 0; i < 7; i ++) putchar('_');
			}
		}
		for (i = p -> l; i < p -> r; i ++) putchar(S[i]);
		if (p -> r == m) putchar('$');
		puts("");
		for (i = 0; i < SIGMA; i ++) {
			if (p -> chd[i]) output(p -> chd[i], dp + 1);
		}
	}
};

const int L = 100100;

char s[L];

int main() {
	strcpy(s, "xabxa");
	SuffixTree STree;
	STree.build(s);
	STree.output(STree.root, 0);
}

//To Queue or not to Queue
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

#define MX 1000005
#define MOD 1000000007
#define SIGMA 26

using namespace std;

struct Node {
	int l, r, pardp, chdNum;
	Node *par, *sLink;
	Node *chd[SIGMA];

	Node() {
		l = r = pardp = chdNum = 0;
		par = sLink = NULL;
		for (int i = 0; i < SIGMA; i++) chd[i] = NULL;
	}
	inline int len() {
		return r - l;
	}
	inline int depth() {
		return pardp + len();
	}
	inline bool inEdge(int pos) {
		return pardp <= pos && pos < depth();
	}
	void setEdge(Node *child, int l, int r, char *s) {
		chd[s[l] - 'a'] = child;
		chdNum++;
		child -> par = this;
		child -> pardp = depth();
		child -> l = l, child -> r = r;
	}
};

struct STree {
	char *S;
	int m, jj, tot;
	bool needWalk;
	long long substr;
	Node *root, *cur, *needSLink;
	vector<Node> V;
	queue<Node *> Q;

	STree(char *str) {
		S = str;
		m = strlen(S);
		tot = 0;
		V.reserve(m * 2 + 10);
		root = newNode();
		cur = newNode();
		root -> setEdge(cur, 0, m, S);
		Q.push(cur);
		needSLink = NULL;
		jj = 1;
		substr = 1;
		needWalk = true;
	}
	Node *newNode() {
		V.push_back(Node());
		return &V[tot++];
	}
	void walk_down(int j, int i) {
		if (i >= j)
			for (int h = j + cur -> depth(); !cur -> inEdge(i - j); h += cur -> len())
				cur = cur -> chd[S[h] - 'a'];
	}
	void addSLink() {
		if (needSLink) {
			needSLink -> sLink = cur;
			needSLink = NULL;
		}
	}
	void extend(int i) {
		int k, pos;
		char c = S[i + 1];
		Node *leaf, *split;

		for (; jj <= i + 1; jj++) {
			if (needWalk) {
				if (!cur -> sLink && cur -> par) cur = cur -> par;
				cur = (cur -> sLink) ? cur -> sLink : root;
				walk_down(jj, i);
			}
			needWalk = true;

			k = i - jj + 1;
			if (k == cur -> depth()) {
				addSLink();
				if (cur -> chd[c - 'a']) {
					cur = cur -> chd[c - 'a'];
					needWalk = false;
					break;
				} else {
					leaf = newNode();
					cur -> setEdge(leaf, i + 1, m, S);
					Q.push(leaf);
				}
			} else {
				pos = cur -> l + k - cur -> pardp;
				if (S[pos] == c) {
					addSLink();
					if (pos != i + 1) {
						needWalk = false;
						break;
					}
				} else {
					split = newNode();
					leaf = newNode();
					cur -> par -> setEdge(split, cur -> l, pos, S);
					cur -> par -> chdNum--;
					split -> setEdge(cur, pos, cur -> r, S);
					split -> setEdge(leaf, i + 1, m, S);
					Q.push(leaf);
					cur = split;
					addSLink();
					if (cur -> depth() == 1) cur -> sLink = root;
					else needSLink = cur;
				}
			}
		}
		substr += Q.size();
	}
	void erase(int i) {
		int k;
		Node *tmp = Q.front();

		Q.pop();
		while (!tmp -> chdNum)
			if (cur != tmp) {
				tmp -> par -> chd[S[tmp -> l] - 'a'] = NULL;
				tmp -> par -> chdNum--;
				substr -= min(tmp -> r, i + 1) - tmp -> l;
				tmp = tmp -> par;
			} else {
				k = (i - jj + 1) - cur -> pardp;
				substr -= min(cur -> r, i + 1) - cur -> l - k;
				cur -> l = i + 1 - k;
				cur -> r = m;
				Q.push(cur);
				break;
			}

		if (!tmp -> chdNum) {
			cur = cur -> par;
			if (cur != root) cur = cur -> sLink;
			walk_down(++jj, i);
			needWalk = false;
		}
	}
};

char s[MX];
bool op[MX];

main() {
	int Q, i, k;
	long long rlt(1);
	char t[2];

	scanf("%d", &Q);
	for (i = k = 0; k < Q; k++) {
		scanf("%s ", t);
		if (t[0] == '+') {
			op[k] = true;
			s[i++] = getchar();
		}
	}

	STree tree(s);
	for (i = 0, k = 1; k < Q; k++) {
		if (op[k]) tree.extend(i++);
		else tree.erase(i);
		rlt = (rlt + tree.substr) % MOD;
	}
	printf("%lld\n", rlt);
}
