void GetEquation(pnt A, pnt B, pnt C, double &a, double &b, double &c, double &d) {
	pnt DIR = B - A ^ C - A;
	a = DIR.x, b = DIR.y, c = DIR.z;
	d = - a * A.x - b * A.y - c * A.z;
}

double GetValue(double a, double b, double c, double d, pnt A) {
	return a * A.x + b * A.y + c * A.z + d;
}
