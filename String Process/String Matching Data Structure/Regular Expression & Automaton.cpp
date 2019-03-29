//NEERC 2012 / Problem D / Disjoint Regular Expressions
//Coded by BAHU

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

typedef vector <int> VI;

const int L = 101;			// string's length
const int CN = L << 2;		// number of Vertexes
const int maxS = L << 2;	// number of states in automaton

struct Vertex {
	enum { ALPHA, KLEENESTAR, ALTERNATION, CONCATENATION };
	int type, l, r;
};

struct RegularExpression {
	Vertex ver[CN];

	int cn, pos;
	char s[L];

	void init() {
		cn = 0;
		pos = 0;
	}

	int newVertex(int type, int l, int r) {
		assert(cn < CN);
		ver[cn].type = type;
		ver[cn].l = l;
		ver[cn].r = r;
		return cn ++;
	}

	int KleeneStar() {
		int res;
		if (s[pos] == '(') {
			pos ++;	//'('
			res = Expr();
			pos ++; //')'
		} else res = newVertex(Vertex::ALPHA, s[pos ++], -1);
		while (s[pos] == '*') {
			pos ++;
			res = newVertex(Vertex::KLEENESTAR, res, -1);
		}
		return res;
	}

	int Concatenation() {
		int v = KleeneStar();
		while (s[pos] && s[pos] != ')' && s[pos] != '|')
			v = newVertex(Vertex::CONCATENATION, v, KleeneStar());
		return v;
	}

	int Expr() {
		int v = Concatenation();
		while (s[pos] == '|') {
			pos ++;
			v = newVertex(Vertex::ALTERNATION, v, Concatenation());
		}
		return v;
	}

	int build(char *S) {
		init();
		strcpy(s, S);
		return Expr();
	}
};

struct Automaton {
	struct Node {
		VI next;
		VI chr;
	};
	int size;
	Node node[maxS];

	void init() {
		for (int i = 0; i < size; i ++) {
			node[i].next.clear();
			node[i].chr.clear();
		}
		size = 0;
	}

	void insert(int s, int e, char c) {
		node[s].next.push_back(e);
		node[s].chr.push_back(c);
	}

	void extend(RegularExpression R, int v) {
		int st = size ++;
		if (R.ver[v].type == Vertex::ALPHA) insert(st, size, R.ver[v].l);
		else if (R.ver[v].type == Vertex::KLEENESTAR) {
			extend(R, R.ver[v].l);
			insert(st, st + 1, -1);
			insert(st, size, -1);
			insert(size - 1, st, -1);
		} else if (R.ver[v].type == Vertex::CONCATENATION) {
			insert(st, st + 1, -1);
			extend(R, R.ver[v].l);
			insert(size - 1, size, -1);
			extend(R, R.ver[v].r);
			insert(size - 1, size, -1);
		} else {
			extend(R, R.ver[v].l);
			int mid = size;
			extend(R, R.ver[v].r);
			insert(st, st + 1, -1);
			insert(st, mid, -1);
			insert(mid - 1, size, -1);
			insert(size - 1, size, -1);
		}
		size ++;
	}

	void build(char *s) {
		init();
		RegularExpression R;
		extend(R, R.build(s));
	}

	void print() {
		puts("Automaton Print");
		for (int i = 0; i < size; i ++) {
			printf("Node #%d:\n", i);
			for (int j = 0; j < node[i].next.size(); j ++) {
				int c = node[i].chr[j];
				if (c == -1) printf("	next[-1] = %d\n", node[i].next[j]);
				else printf("	next[%c] = %d\n", c, node[i].next[j]);
			}
		}
		puts("---------------\n");
	}
} a[2];

const int maxQ = maxS * maxS * 2;

#define S [maxS][maxS][2]
#define I [x][y][z]
#define forn(i, n) for (int i = 0; i < (int)(n); i++)

int qst = maxQ, qen = maxQ;
int qx[maxQ * 2], qy[maxQ * 2], qz[maxQ * 2];
int d S, px S, py S, pz S, pc S;
int rn, r[maxQ];

void AddQ(int x, int y, int D, int PX, int PY, int PZ, int PC) {
	int add = (PC != -1), z = PZ || add;
	D += add;
	if (d I > D) {
		d I = D;
		px I = PX, py I = PY, pz I = PZ, pc I = PC;
		if (add) qx[qen] = x, qy[qen] = y, qz[qen ++] = z;
		else qx[-- qst] = x, qy[qst] = y, qz[qst] = z;
	}
}

char s[L];

int main() {
	freopen ("disjoint.in", "r", stdin);
	freopen ("out.txt", "w", stdout);
	while (gets(s) > 0) {
		a[0].build(s);
		gets(s), a[1].build(s);

		memset(d, 0x70, sizeof(d));
		qst = qen = maxQ;
		AddQ(0, 0, 0, 0, 0, 0, -1);

		while (qst < qen) {
			int x = qx[qst], y = qy[qst], z = qz[qst++], D = d I;
			forn(i, a[0].node[x].next.size())
				forn(j, a[1].node[y].next.size())
					if (a[0].node[x].chr[i] == a[1].node[y].chr[j])
						AddQ(a[0].node[x].next[i], a[1].node[y].next[j], D, x, y, z, a[0].node[x].chr[i]);
			forn(i, a[0].node[x].next.size())
				if (a[0].node[x].chr[i] == -1)
					AddQ(a[0].node[x].next[i], y, D, x, y, z, -1);
			forn(j, a[1].node[y].next.size())
				if (a[1].node[y].chr[j] == -1)
					AddQ(x, a[1].node[y].next[j], D, x, y, z, -1);
		}

		int x = a[0].size - 1, y = a[1].size - 1, z = 1;
		if (d I > maxQ) puts("Correct");
		else {
			rn = 0;
			puts("Wrong");
			while (x || y) {
				int x1 = px I, y1 = py I, z1 = pz I, c = pc I;
				if (c != -1) r[rn ++] = c;
				x = x1, y = y1, z = z1;
			}
			while (rn --) putchar(r[rn]);
			puts("");
		}
	}
	return 0;
}
