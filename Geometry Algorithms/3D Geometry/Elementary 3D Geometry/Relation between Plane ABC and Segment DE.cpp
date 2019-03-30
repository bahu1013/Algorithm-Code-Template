int INTERSECT(pnt a, pnt b, pnt c, pnt d, pnt e, pnt &res) {
/*
	Relation between Plain abc and Segment de...
		return 0: Pass by each other.
		return 1: Parallel but not contained.
		return 2: Intersect.
		return 3: Segment is contained on the plain.
*/
	double A, B, C, D;
	GetEquation(a, b, c, A, B, C, D);
	double t1 = Value(A, B, C, D, d);
	double t2 = Value(A, B, C, D, e);
	if (fabs(t1) < ep && fabs(t2) < ep) {
		res = d;
		return 3;
	}
	if (fabs(t1) < ep) {
		res = d;
		return 2;
	}
	if (fabs(t2) < ep) {
		res = e;
		return 2;
	}
	if ((t1 > 0 && t2 > 0) || (t1 < 0 && t2 < 0)) {
		if (fabs(t1 - t2) < ep) return 1;
		return 0;
	}
	double Ratio = t1 / (t1 - t2);
	res = d + ((e - d) * Ratio);
	return 2;
}
