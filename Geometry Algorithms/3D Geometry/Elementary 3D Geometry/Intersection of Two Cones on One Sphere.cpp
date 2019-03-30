int intercone(pnt3 ci, double A, pnt3 cj, double B, pnt3 &q, pnt3 &qq) {
	pnt3 nor = ci ^ cj;
	pnt3 p = ci * B - cj * A;
	pnt3 pp;
	if (fabs(nor.x) > ep) pp = pnt3(0, -p.z, p.y) / nor.x;
	else if (fabs(nor.y) > ep) pp = pnt3(p.z, 0, -p.x) / nor.y;
	else if (fabs(nor.z) > ep) pp = pnt3(-p.y, p.x, 0) / nor.z;
	else return -1;
	double a,b,c,d,t1,t2;
	a = nor & nor;
	b = nor & pp;
	c = (pp & pp) - 1;
	d = b * b - a * c;
	if (d < 0) return 0;
	t1 = (-b + sqrt(d)) / a;
	t2 = (-b - sqrt(d)) / a;
	q = nor*t1 + pp;
	qq = nor*t2 + pp;
	return 2;
}
