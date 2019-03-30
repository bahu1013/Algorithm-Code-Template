pnt outercenter(pnt a, pnt b, pnt c) {
	double c1 = ((a & a) - (b & b)) / 2, c2 = ((a & a) - (c & c)) / 2;
	double x0 = (c1 * (a.y - c.y) - c2 * (a.y - b.y)) / (a - b ^ a - c);
	double y0 = (c1 * (a.x - c.x) - c2 * (a.x - b.x)) / (a - c ^ a - b);
	return pnt(x0, y0);
}
