//extEuclid(a, b, x, y)=a*x+b*y;
int extEuclid(int a, int b, int &x, int &y) {
	if (!b) {
		x = 1, y = 0;
		return a;
	}
	int d, tmp;
	d = extEuclid(b, a % b, x, y);
	tmp = x, x = y, y = tmp - a / b * y;
	return d;
}
