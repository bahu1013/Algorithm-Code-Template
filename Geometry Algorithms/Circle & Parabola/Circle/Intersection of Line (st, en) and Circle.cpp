bool intersect_circle_line(pnt cp, double r, pnt st, pnt en) {
	double len = dist(en - st);
	double d = fabs(cp - st ^ en - st) / len;
	if (d >= r) return 0;
	double dx =sqrt(r * r - d * d);
	double x = (cp - st & en - st) / len;
	double a = (x - dx) / len, b = (x + dx) / len;
//	pa = st * (1 - a) + en * a;
//	pb = st * (1 - b) + en * b;
	return 1;
}
