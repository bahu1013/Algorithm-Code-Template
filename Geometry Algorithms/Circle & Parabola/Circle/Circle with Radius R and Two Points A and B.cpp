int circle2ptsRad(pnt a, pnt b, double r, pnt p[]) {
	pnt c = (a + b) / 2;
	double d = r * r - (a - b & a - b) / 4;
	if (d < -ep) return 0;
	d = sqrt(d);
	pnt dv = rot(b - a) * d / dist(a - b);
	p[0] = c + dv;
	p[1] = c - dv;
}
