//relative prime
int lcm(int a, int b) {return a / gcd(a, b) * b;}
int chinese_remainder(int r[], int w[], int len) {
	int ret = 0, ww = 1;
	for (int i = 0; i < len; i ++) ww *= w[i];
	for (int i = 0; i < len; i ++) {
		int m = ww / w[i], x, y;
		extended_euclid(w[i], m, x, y);
		ret = (ret + y * m * r[i]) % ww;
	}
	return (ww + ret % ww) % ww;
}

//other
int chinese_remainder2(int r[],int w[],int len) {
	int ret = r[0], ww = w[0];
	for (int i = 1; i < len; i ++)	{
		int x = modular_linear_equation(ww, r[i] - ret, w[i]);
		if(x == -1) return -1;
		ret = x * ww + ret;
		ww = lcm(ww, w[i]);
	}
	return (ww + ret % ww) % ww;
}
