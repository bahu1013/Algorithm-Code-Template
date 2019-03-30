//O(n^2*logn)
bool Inside(int u, int v) {
	double dis = dist(O[u] - O[v]);
	return dis + R[u] < R[v] + ep && R[u] < R[v] - ep;
}

bool Same(int u, int v) {
	double dis = dist(O[u] - O[v]);
	return dis < ep && fabs(R[u] - R[v]) < ep;
}

struct itv {
	double pos;
	int left;
	itv (double p = 0, int l = 0) : pos(p), left(l) {}
	bool operator < (const itv &p) const {
		if (fabs(pos - p.pos) > ep) return pos < p.pos;
		return left > p.left;
	}
} Itv[N * 5];

int ci;

void Insert(double st, double en) {
	if (st > en + ep) Insert(st, pi), Insert(-pi, en);
	else if (st < -ep && ep < en) Insert(st, 0), Insert(0, en);
	else {
		Itv[ci ++] = itv(st, 1);
		Itv[ci ++] = itv(en, -1);
	}
}

double SegmentArea(int u, double a, double b) {
	double ang = b - a;
	if (fabs(ang) < ep) return 0;
	double ret = R[u] * R[u] * (ang - sin(ang)) / 2;
	pnt A = O[u] + pnt(cos(a), sin(a)) * R[u];
	pnt B = O[u] + pnt(cos(b), sin(b)) * R[u];
	ret += (A.y + B.y) * (A.x - B.x) / 2;
	return ret;
}

double SignedArea(int u) {
	ci = 0;
	Insert(-pi, -pi);
	Insert(0, 0);
	Insert(pi, pi);
	for (int i = 1; i <= n; i ++) if (u != i) {
		pnt tp[2];
		int cnt = intersect_circles(O[u], R[u], O[i], R[i], tp);
		if (cnt != 2) continue;
		double al = atan2(tp[0].y - O[u].y, tp[0].x - O[u].x);
		double be = atan2(tp[1].y - O[u].y, tp[1].x - O[u].x);
		Insert(al, be);
	}

	sort(Itv, Itv + ci);
	double pos = Itv[0].pos, ret = 0;
	int cur = 1;
	for (int i = 1; i < ci; i ++) {
		if (!cur) ret += SegmentArea(u, pos, Itv[i].pos);
		cur += Itv[i].left;
		pos = Itv[i].pos;
	}
	return ret;
}

bool vis[N];

double CircleArea() {
	double ret = 0;
	for (int i = 1; i <= n; i ++) {
		vis[i] = 0;
		for (int j = 1; j < i; j ++) if (Same(i, j) || Inside(i, j)) {
			vis[i] = 1;
			break;
		}
		if (vis[i]) continue;
		for (int j = i + 1; j <= n; j ++) if (Inside(i, j)) {
			vis[i] = 1;
			break;
		}
	}
	int m = 0;
	for (int i = 1; i <= n; i ++) if (!vis[i]) O[++ m] = O[i], R[m] = R[i];
	n = m;
	for (int i = 1; i <= n; i ++) ret += SignedArea(i);
	return ret;
}
