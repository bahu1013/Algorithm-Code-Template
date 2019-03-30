poly Cut(pnt a, pnt b, const poly &p) {
	int sz = p.size();
	poly ret;
	for (int i = 0; i < sz; i ++) {
		double chk = b - a ^ p[i] - a;
		if (chk < ep) ret.push_back(p[i]);
		double chk2 = b - a ^ p[(i + 1) % sz] - a;
		if ((chk < -ep && chk2 > ep) || (chk > ep && chk2 < -ep)) {
			pnt tp = p[i] + (p[(i + 1) % sz] - p[i]) * chk / (chk - chk2);
			ret.push_back(tp);
		}
	}
	return ret;
}
