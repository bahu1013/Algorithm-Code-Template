inline int sgn(double a) { return a > ep ? 1 : a < -ep ? -1 : 0; }

bool InsideCP(pnt q, const poly &p) {
	int n = p.size();
	bool ccw = (p[1] - p[0] ^ p[2] - p[1]) > ep;
	int below = sgn(q - p[0] ^ p[n - 1] - p[0]);

	if (ccw && below < 0) return 0;
	if (!ccw && below > 0) return 0;

	int lo = 0, hi = n - 1;
	while (hi - lo > 1) {

		int mid = (hi + lo) >> 1;
		int s1 = sgn(p[mid] - p[lo] ^ q - p[lo]);
		int s2 = sgn(q - p[hi] ^ p[mid] - p[hi]);
		bool f1 = ccw ? (s1 >= 0) : (s1 <= 0);
		bool f2 = ccw ? (s2 >= 0) : (s2 <= 0);
		if (f1 && f2) return 1;
		if (!f1 && !f2) return 0;
		if (f1) lo = mid;
		else hi = mid;
	}
	return 0;
}
