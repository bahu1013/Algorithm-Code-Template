void get_sphere(pnt3 pos[], int n, pnt3 &p, double &r){
	double move = 0.5;
	p.x = p.y = p.z = 50.0;
	while (move > ep) {
		for (int t = 0; t < 100; t ++) {
			int k;
			r = 0;
			for (int i = 0; i < n; i ++) {
				if (dist(p - pos[i]) > r) {
					r = dist(p - pos[i]);
					k = i;
				}
			}
			p = p + (pos[k] - p) * move;
		}
		move /= 2;
	}
}
