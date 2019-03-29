inline int sgn(double a) { return (a > ep) - (a < -ep); }

inline double simpson(double a, double b) {
	return (f(a) + 4 * f((a + b) / 2) + f(b)) * (b - a) / 6;
}

double integrate(double a, double b) {
	double c = (a + b) / 2;
	double l = simpson(a, c);
	double r = simpson(c, b);
	double t = simpson(a, b);
	return sgn(l + r - t) ? integrate(a, c) + integrate(c, b) : t;
}
