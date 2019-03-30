double common_circles(pnt c, double r, pnt cc, double rr){
	if (r<rr){
		swap(c,cc);
		swap(r,rr);
	}
	double d=dist(c-cc);
	if (rr+d<=r) return pi*rr*rr;
	if (r+rr<=d) return 0;
	double x=(r*r-rr*rr+d*d)/(d*2);
	double xx=d-x;
	double res1=acos(x/r)*r*r-x*sqrt(r*r-x*x);
	double res2=acos(xx/rr)*rr*rr-xx*sqrt(rr*rr-xx*xx);
	return res1+res2;
}
