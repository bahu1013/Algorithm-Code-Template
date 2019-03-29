int modular_linear_equation(int a,int b,int n) {
	a = (a % n + n) % n, b = (b % n + n) % n;
	int x, y, g = extended_euclid(a, n, x, y);
	if (b % g != 0) {
		puts("no solution");
		//return -1;
	}
	else {
		int x0 = ((x + n) % n * (b / g)) % n;
		for (int i = 0; i < g; i ++) {
			int ans = (x0 + i * (n / g)) % n;
			printf("%d\n", ans);
			//return ans;
		}
	}
}
