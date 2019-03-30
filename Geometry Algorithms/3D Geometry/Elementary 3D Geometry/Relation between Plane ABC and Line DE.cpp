bool intersect(pnt a, pnt b, pnt c, pnt d, pnt e, pnt &res) {
/*
	Relation between Plane ABC and Line DE
		return 0: parallel.
		return 1: intersect.
		return 2: Line is on the plain.
*/
	b = b - a;
	c = c - a;
	pnt h = b ^ c;
	double s = a - e & h;
	double t = d - e & h;
	if (fabs(t) < ep) {
		if (fabs(s) < ep) return 2;
		return 0;
	}
	double x = s / t;
	res = d * x + e * (1 - x);
	return 1;
}
