pnt PolygonCenter(pnt *p, int n) {
	double area = 0;
	pnt c(0, 0);
	for (int i = 0; i < n; i ++) {
		int j = (i + 1) % n;
		double s = p[i] - p[0] ^ p[j] - p[0];
		pnt cc = (p[0] + p[i] + p[j]) / 3 * s;
		area += s;
		c = c + cc;
	}
	return c / area;
}
