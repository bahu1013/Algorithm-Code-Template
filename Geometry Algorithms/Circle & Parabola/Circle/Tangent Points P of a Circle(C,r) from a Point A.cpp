int TangentPoint(pnt c, double r, pnt a, pnt p[]){
	double d = dist(c - a);
	if (d < r - ep) return 0;
	if (fabs(d - r) < ep) {
		p[0] = a;
		return 1;
	}
	double x = r * r / d; 				
	pnt cp = (c * (d - x) + a * x) / d;	
	double h = sqrt(r * r - x * x); 	
	pnt dv = rot(c - a) * h / d;		
	p[0] = cp + dv;
	p[1] = cp - dv;
	return 2;
}
