inline pnt rot(pnt p) { return pnt(-p.y, p.x); }

int intersect_circles(pnt c, double r, pnt cc, double rr, pnt p[]) {
	double d = dist(c - cc);
	if (r + rr < d || r + d < rr || rr + d < r) return 0;
	double x = (r * r - rr * rr + d * d) / (d * 2);
	pnt cp = (c * (d - x) + cc * x) / d;
	if (r + rr == d || r + d == rr || rr + d == r){
		p[0] = cp;
		return 1;
	}
	double h = sqrt(r * r - x * x);
	pnt dv = rot(cc - c) * h / d ;
	p[0] = cp - dv;
	p[1] = cp + dv;
	return 2;
}
