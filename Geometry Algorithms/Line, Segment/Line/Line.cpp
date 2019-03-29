// Common Equation of Line crossing Point A and Point B

void get_equation(pnt a, pnt b, double &A, double &B, double &C) {
	A = b.y - a.y;
	B = a.x - b.x;
	C = -A * a.x - B * a.y;
}

// Intersection of two Lines

bool intersect(pnt a, pnt b, pnt c, pnt d, pnt &res) {
	double den = a - b ^ c - d;
	if (fabs(den) < ep) return 0;		//The two lines are parallel...
	double x = (a - d ^ c - d) / den;
	res = a * (1 - x) + b * x;
	return 1;						//The two lines are intersect...
}


// Distance from Point P to Line ax+by+c=0

inline double dist_eqn(pnt p, double a, double b, double c) {
	return (a * p.x + b * p.y + c) / sqrt(a * a + b * b);
}

// Distance from Point A to Line BC

inline double dist_line(pnt a, pnt b, pnt c) {
	return fabs(a - b ^ c - b) / dist(b - c);
}

// Reflection of Vector AB(A->B) Crashed into Line CD

double cross(pnt a, pnt b, pnt c, pnt d, pnt &res) {
	double s1 = b - a ^ d - c;
	if (fabs(s1) < ep) return -1;
	double s2 = b - c ^ a  - c, s = s2 / s1;
	if (0 <= s && s <= 1) {
		res = c + (d - c) * s;
		if ((res - a & b - a) < -ep) return -1;
		return dist(res - a);
	}
	return -1;
}

void reflex(pnt a, pnt b, pnt c, pnt d, pnt &st, pnt &dir) {
	pnt tp;
	double A, B, C, H, P;
	cross(a, b, c, d, st);
	pnt vec=pnt(d.y - c.y, c.x - d.x);
	A = dist(c - d);
	B = dist(a - c);
	C = dist(a - d);
	P = (A + B + C)/2;
	H = 2 * sqrt(P * (P - A) * (P - B) * (P - C)) / A;
	tp = st + (vec * (H / dist(vec)));
	if ((d - c ^ a - c) * (d - c ^ tp - c) < 0) tp = st - (vec * (H / dist(vec)));
	dir = (tp * 2) - a - st;
}
