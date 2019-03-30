double f(double x, double a, double b, double c) {
	double t, tt;
	t = (sqrt((b + 2 * a * x) * (b + 2 * a * x) + 1) + 2 * a * x + b);
	tt = log(t) / (4 * a);
	t = sqrt((b + 2 * a * x) * (b + 2 * a * x) + 1) * (b + 2 * a * x) / (4 * a);
	tt += t;
	return tt;
}

double Len(double x, double xx, double a, double b, double c) {
	return f(xx, a, b, c) - f(x, a, b, c);
}
