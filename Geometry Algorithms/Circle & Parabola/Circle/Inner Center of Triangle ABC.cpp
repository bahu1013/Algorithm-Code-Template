pnt innercenter(pnt a, pnt b, pnt c) {
	double A = (b - c).dist();
	double B = (c - a).dist();
	double C = (a - b).dist();
	return pnt((A * a.x + B * b.x + C * c.x) / (A + B + C), (A * a.y + B * b.y + C * c.y) / (A + B + C));
}
