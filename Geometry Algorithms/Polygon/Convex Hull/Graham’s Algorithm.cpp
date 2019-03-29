bool cmp(pnt a, pnt b) {
	if (fabs(a.x - b.x) > ep) return a.x < b.x;
	return a.y < b.y;
}

bool cmp1(pnt a, pnt b) {
	double tmp = a - p[0] ^ b - p[0];
	if (fabs(tmp) > ep) return tmp > 0;
	double u = a - p[0] & a - p[0], v = b - p[0] & b - p[0];
	return u < v;
}

int main() {
	sort(p, p + n, cmp);
	sort(p + 1, p + n, cmp1);
	int k = 0;
	for (int i = 0; i < n; i ++) {
		while (k > 1 && (con[k - 1] - con[k - 2] ^ p[i] - con[k - 2]) <= 0) k --;
		con[k ++] = p[i];
	}
}

//Faster
typedef vector <pnt> Poly;

inline double CrossProduct(pnt a, pnt b) { return a ^ b; }

Poly ConvexHull(Poly &p) {
	sort(p.begin(), p.end());
	p.erase(unique(p.begin(), p.end()), p.end());

	int n = p.size();
	int m = 0;
	vector <pnt> ch(n + 1);
	for (int i = 0; i < n; i ++) {
		while (m > 1 && CrossProduct(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2]) <= 0) m --;
		ch[m ++] = p[i];
	}
	int k = m;
	for (int i = n - 2; i >= 0; i --) {
		while (m > k && CrossProduct(ch[m - 1] - ch[m - 2], p[i] - ch[m - 2]) <= 0) m --;
		ch[m ++] = p[i];
	}
	if (n > 1) m --;
	ch.resize(m);
	return ch;
}
