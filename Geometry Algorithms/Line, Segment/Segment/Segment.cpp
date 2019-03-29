// Relation between Segment and Point

bool inside(pnt a, pnt b, pnt c) {
	//if pnt a is on the segment between pnt b and pnt c, return 1.
	double A = a - b & a - c;
	double B = a - b ^ a - c;
	if (fabs(B) > ep) return 0;
	return A <= 0;
}


// Intersection of two Segments

int intersect(pnt a, pnt b, pnt c, pnt d, pnt &res) {
	double s1 = b - a ^ d - c, s2 = b - c ^ a - c, s;
	double t1 = s1, t2 = c - a ^ d - a;
	if (fabs(s1) < ep) {
		double dd = c - b ^ a - b;
		if (fabs(dd) > ep) return 2;	//parallel
		if (inside(a, c, d) || inside(b, c, d) ||
			inside(c, a, b) || inside(d, a, b)) return 1;	//overlap
		return 2;					//parallel
	}
	if (s1 < 0) s2 *= -1, t2 *= -1, s1 *= -1, t1 *= -1;
	if (-ep < s2 && s2 < s1 + ep && -ep < t2 && t2 < t1 + ep) {
		s = s2 / s1;
		res = c + ((d - c) * s);
		return 1;
	}
	return 0;
}


// Distance from A to Segment BC

double dist_seg(pnt a, pnt b, pnt c) {
	if ((a - b & c - b) < ep) return dist(a - b);
	if ((a - c & b - c) < ep) return dist(a - c);
	return dist_line(a, b, c);
}


// Symetric and Projecting Point of C

pnt sym(pnt a, pnt b, pnt c) {
	double tp = (c - a & b - a) / (b - a & b - a);
	pnt p = a * (1 - tp) + b * tp;
	return p * 2 - c;
}
