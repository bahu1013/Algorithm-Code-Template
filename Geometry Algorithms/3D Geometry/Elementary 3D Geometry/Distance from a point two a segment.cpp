double Dist(pnt a, pnt b, pnt c) {	//Distance from A to Segment BC
	double da = b - c & b - c;
	double db = a - c & a - c;
	double dc = a - b & a - b;
	if (db < da + dc + ep && dc < da + db + ep) {
		pnt Area = b - a ^ c - a;
		double area = dist(Area);
		double len = dist(b - c);
		return area / len;
	} else if (da + dc < db) return dist(a - b);
	return dist(a - c);
}
