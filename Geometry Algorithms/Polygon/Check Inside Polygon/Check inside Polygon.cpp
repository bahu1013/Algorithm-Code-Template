int insideP(poly &p, pnt q) {
	int cross = 0;
	int n = p.size();
	for (int i = 0; i < n; i ++) {
		int j = (i + 1)%n;
		if (inside(q, p[i], p[j])) return 2;
		if (p[j].y > q.y && p[i].y <= q.y ||
			p[i].y > q.y && p[j].y <= q.y) {
			double x = (p[j] - q ^ p[i] - q) * (p[i].y - p[j].y);
			if (x > ep) cross ++;
		}
	}
	return cross % 2;
}
