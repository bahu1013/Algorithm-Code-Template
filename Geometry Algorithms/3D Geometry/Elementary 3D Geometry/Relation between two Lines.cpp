int intersect(pnt a, pnt b, pnt c, pnt d, pnt &res) {
/*
	Relation between Line ab and Line cd...
		return 0: Pass by each other.
		return 1: Parallel but not identical.
		return 2: Intersect.
		return 3: Identical.
*/
	pnt dr = b - a ^ d - c;
	double chk = dr & c - a;
	if (fabs(chk) < ep) {
		double area = dist(dr);
		if (area < ep) {
			double dd = dist(c - a ^ b - a);
			if (dd < ep) {
				res = c;
				return 3;
			}
			return 1;
		}
		pnt DR = c - a ^ d - a;
		double Ratio = (dr & DR) / (dr & dr);
		res = a + ((b - a) * Ratio);
		return 2;
	}
	return 0;
}
