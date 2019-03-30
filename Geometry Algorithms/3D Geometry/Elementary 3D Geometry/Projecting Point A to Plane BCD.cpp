pnt3 project(pnt3 a, pnt3 b, pnt3 c, pnt3 d) {
	pnt3 tp = c - b ^ d - b;
	return a - (tp * (tp & a - b) / (tp & tp));
}
