int CircumscribedLines(pnt c, double r, pnt cc, double rr, pnt p[]) {
	double d = dist(c - cc);
	bool sw = 0;
	if (r > rr) {
		swap(c, cc);
		swap(r, rr);
		sw = 1;
	}
	if (d + r < rr - ep) return 0;
	if (fabs(d + r - rr) < ep){
		if (fabs(r - rr) < ep) return 3;
		pnt cp = (cc * (d - rr) + c * rr) / d;
		p[0] = cp;
		return 1;
	}
	pnt q[4];
	TangentPoint(cc, rr - r, c, q);
	double dr = rr - r;
	double h = r / sqrt(d * d - dr * dr);
	pnt dv = rot(q[0] - c) * h;
	p[0] = c + dv;
	p[2] = q[0] + dv;
	dv = rot(q[1] - c) * h;
	p[1] = c - dv;
	p[3] = q[1] - dv;
	if (sw) {
		swap(p[0], p[2]);
		swap(p[1], p[3]);
	} else {
		swap(p[0], p[1]);
		swap(p[2], p[3]);
	}
	return 2;
}
