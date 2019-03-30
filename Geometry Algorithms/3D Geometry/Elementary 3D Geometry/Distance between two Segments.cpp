double SolveA(pnt A, pnt B, pnt C, pnt D) {
	double ret = 1e10;
	double d = Dist(B, C, D);
	if (d < ret) ret = d;
	d = Dist(A, C, D);
	if (d < ret) ret = d;
	d = Dist(C, A, B);
	if (d < ret) ret = d;
	d = Dist(D, A, B);
	if (d < ret) ret = d;
	return ret;
}

double SolveB(pnt A, pnt B, pnt C, pnt D) {
	pnt DIR = B - A ^ C - D;
	double a, b, c, d;
	GetEquation(A, B, DIR + A, a, b, c, d);
	double u = GetValue(a, b, c, d, C);
	double v = GetValue(a, b, c, d, D);
	if (u * v <= 0) {
		GetEquation(C, D, DIR + C, a, b, c, d);
		u = GetValue(a, b, c, d, A);
		v = GetValue(a, b, c, d, B);
		if (u * v <= 0) {
			GetEquation(C, D, C + A - B, a, b, c, d);
			double ret = GetValue(a, b, c, d, A);
			return fabs(ret) / dist(DIR);
		}
	}
	return SolveA(A, B, C, D);
}

double CalcDis(pnt A, pnt B, pnt C, pnt D) {
	pnt DIR = B - A ^ D - C;
	if (dist(DIR) < ep) return SolveA(A, B, C, D);
	return SolveB(A, B, C, D);
}
