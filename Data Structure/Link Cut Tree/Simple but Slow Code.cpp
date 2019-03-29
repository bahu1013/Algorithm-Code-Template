//HDU 5002
#include <cstdio>
#include <algorithm>

using namespace std;

const int inf = 0x3f3f3f3f;
const int N = 100010;

struct Node *null;

struct Node {
	Node *pa,*son[2];

	int val, size;
	int add, same;
	int rev;

	int mm, mmc;
	int sm, smc;

	void clear(int v) {
		pa = son[0] = son[1] = null;
		val = v, size = 1;
		add = rev = 0, same = -inf;
		mm = v, mmc = 1;
		sm = -inf, smc = 0;
	}

	void add_val(int v, int c){
		if (v == -inf || v < sm) return;
		if (v == sm) smc += c;
		else if (v < mm) sm = v, smc = c;
		else if (v == mm) mmc += c;
		else {
			sm = mm, smc = mmc;
			mm = v, mmc = c;
		}
	}

	void push_up(){
		size = son[0]->size + 1 + son[1]->size;
		mm = sm = -inf;
		mmc = smc = 0;
		add_val(val, 1);
		add_val(son[0]->mm, son[0]->mmc);
		add_val(son[0]->sm, son[0]->smc);
		add_val(son[1]->mm, son[1]->mmc);
		add_val(son[1]->sm, son[1]->smc);
	}

	inline void setc(Node *p, int d) { son[d] = p, p->pa = this; }
	inline bool d() { return pa->son[1] == this; }
	inline bool isroot() { return pa == null || pa->son[0] != this && pa->son[1] != this; }

	void flip() {
		if (this == null) return;
		swap(son[0], son[1]);
		rev ^= 1;
	}

	void update_add(int w) {
		if (this == null) return;
		if (mm != -inf) mm += w;
		if (sm != -inf) sm += w;
		val += w;
		add += w;
	}

	void update_same(int w) {
		if (this == null)return;
		mm = w, mmc = size;
		sm = -inf, smc = 0;
		same = w;
		val = w;
		add = 0;
	}

	void push_down() {
		if (same != -inf){
			son[0]->update_same(same);
			son[1]->update_same(same);
			same = -inf;
		}
		if (add) {
			son[0]->update_add(add);
			son[1]->update_add(add);
			add = 0;
		}
		if (rev) {
			son[0]->flip();
			son[1]->flip();
			rev = 0;
		}
	}

	inline void go() { if (!isroot()) pa->go(); push_down(); }

	void rot() {
		Node *f = pa, *ff = pa->pa;
		int c = d(), cc = pa->d();
		f->setc(son[!c], c);
		this->setc(f, !c);
		if(ff->son[cc] == f) ff->setc(this, cc);
		else this->pa = ff;
		f->push_up();
	}

	Node* splay(){
		go();
		while (!isroot()) {
			if (!pa->isroot()) d() == pa->d() ? pa->rot() : rot();
			rot();
		}
		push_up();
		return this;
	}

	Node* access() {
		for (Node *p = this, *q = null; p != null; q = p, p = p->pa) {
			p->splay()->setc(q,1);
			p->push_up();
		}
		return splay();
	}

	Node* find_root() {
		Node *x;
		for (x = access(); x->push_down(), x->son[0] != null; x = x->son[0]);
		return x;
	}

	inline void make_root() { access()->flip(); }

	void cut() {
		access();
		son[0]->pa = null;
		son[0] = null;
		push_up();
	}

	void cut(Node *x) {
		if (this == x || find_root() != x->find_root()) return;
		else x->make_root(), cut();
	}

	void link(Node *x) {
		if (find_root() == x->find_root())return;
		else make_root(), pa = x;
	}
};

#define CodeShortTimeLong

void SAME(Node *x, Node *y, int w){
#ifdef CodeShortTimeLong
	x->make_root();
	y->access();
	y->splay();
	y->update_same(w);
#else
	x->access();
	for (x = null; y != null; x = y, y = y->pa) {
		y->splay();
		if (y->pa == null) {
			y->son[1]->update_same(w);
			x->update_same(w);
			y->val = w;
			y->push_up();
			return;
		}
		y->setc(x, 1);
		y->push_up();
	}
#endif
}

void ADD(Node *x, Node *y, int w) {
#ifdef CodeShortTimeLong
	x->make_root();
	y->access();
	y->splay();
	y->update_add(w);
#else
	x->access();
	for (x = null; y != null; x = y, y = y->pa) {
		y->splay();
		if (y->pa == null) {
			y->son[1]->update_add(w);
			x->update_add(w);
			y->val += w;
			y->push_up();
			return;
		}
		y->setc(x, 1);
		y->push_up();
	}
#endif
}

int SM, SMC;

#ifndef CodeShortTimeLong
int MM, MMC;
void ADD_VAL(int val, int num) {
	if (val == -inf || val < SM) return;
	if (val == SM) SMC += num;
	else if (val < MM) SM = val, SMC = num;
	else if (val == MM) MMC += num;
	else {
		SM = MM, SMC = MMC;
		MM = val, MMC = num;
	}
}
#endif

void QUERY(Node *x, Node *y) {
#ifdef CodeShortTimeLong
	x->make_root();
	y->access();
	y->splay();
	SM = y->sm, SMC = y->smc;
#else
	x->access();
	for (x = null; y != null; x = y, y = y->pa) {
		y->splay();
		if (y->pa == null) {
			MM = SM = -inf;
			MMC = SMC = 0;
			ADD_VAL(y->val, 1);
			ADD_VAL(y->son[1]->mm, y->son[1]->mmc);
			ADD_VAL(y->son[1]->sm, y->son[1]->smc);
			ADD_VAL(x->sm, x->smc);
			ADD_VAL(x->mm, x->mmc);
			return;
		}
		y->setc(x, 1);
		y->push_up();
	}
#endif
}

Node pool[N], *tail;
Node *node[N];

void init() {
	tail = pool;
	null = tail ++;
	null->pa = null->son[0] = null->son[1] = null;
	null->size = null->rev = 0;
	null->same = -inf, null->add = 0;
	null->mm = null->sm = -inf;
	null->mmc = null->smc = 0;
}

int main() {
	int T, R = 0;
	int iCase = 0;
	int n,m;
	scanf("%d",&T);
	while(T--){
		printf("Case #%d:\n", ++R);
		scanf("%d %d", &n, &m);
		init();
		for (int i = 1;i <= n; i ++) {
			int v;
			scanf("%d", &v);
			node[i] = tail ++;
			node[i]->clear(v);
		}
		int u, v;
		for (int i = 1; i < n; i ++) {
			scanf("%d %d", &u, &v);
			node[u]->link(node[v]);
		}
		int op, x, y, a, b;
		while (m --) {
			scanf("%d", &op);
			if (op == 1) {
				scanf("%d %d %d %d", &x, &y, &a, &b);
				node[x]->cut(node[y]);
				node[a]->link(node[b]);
			} else if (op == 2) {
				scanf("%d %d %d", &a, &b, &x);
				SAME(node[a], node[b], x);
			} else if (op == 3) {
				scanf("%d %d %d", &a, &b, &x);
				ADD(node[a], node[b], x);
			} else {
				scanf("%d %d", &a, &b);
				QUERY(node[a], node[b]);
				if (SM == -inf) printf("ALL SAME\n");
				else printf("%d %d\n", SM, SMC);
			}
		}
	}
    return 0;
}
