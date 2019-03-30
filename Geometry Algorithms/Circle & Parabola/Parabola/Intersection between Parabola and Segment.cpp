int interpara(pnt u, pnt v, double a, double b, double c, pnt tp[]) {
	double A, B, C;
	double ta, tb, tc, del, x[2], y;
	bool f0, f1;
	get_equation(u, v, A, B, C);
	if (fabs(B) > ep) {
		A /= -B, C /= -B;
		ta = a, tb = b - A, tc = c - C;
		del = tb * tb - 4 * ta * tc;
		if (del < -ep) return 0;
		if (del < 0) del = 0;
		x[0] = (-tb + sqrt(del)) / 2 / ta;
		x[1] = (-tb - sqrt(del)) / 2 / ta;
		tp[0] = pnt(x[0], A * x[0] + C);
		tp[1] = pnt(x[1], A * x[1] + C);
		return 2;
	} else {
		x[0] = -C/A;
		y = a * x[0] * x[0] + b * x[0] + c;
		tp[0] = pnt(x[0], y);
		return 1;
	}
}
