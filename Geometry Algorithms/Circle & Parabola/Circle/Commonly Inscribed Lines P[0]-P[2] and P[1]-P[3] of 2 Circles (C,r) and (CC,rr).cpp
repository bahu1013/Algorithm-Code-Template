int InscribedLines(pnt c, double r, pnt cc, double rr, pnt p[]) {
	double d = dist(c - cc);
	if (d < r + rr - ep) return 0;
	pnt cp = (c * rr + cc * r) / (r + rr);
	if (fabs(d - r - rr) < ep) {
		p[0] = cp;
		return 1;
	}
	TangentPoint(c, r, cp, p);
	TangentPoint(cc, rr, cp, p+2);
	return 2;
}
