bool INSIDE(pnt a, pnt b, pnt c) {
	pnt dr = a - b ^ a - c;
	if (dist(dr) > ep) return 0;	//A is not on the segment BC
	double d = a - b & a - c;
	return d < ep;
}
