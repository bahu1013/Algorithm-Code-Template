void init() {
	fac[0] = inv[0] = fac[1] = inv[1] = rv[1] = 1;
	for (int i = 2; i < MOD; i ++) {
		rv[i] = (LL)rv[MOD % i] * (MOD - MOD / i) % MOD;
		fac[i] = ((LL)fac[i - 1] * i) % MOD;
		inv[i] = (LL)inv[i - 1] * rv[i] % MOD;
	}
}

LL lucas(LL n, LL m, LL mod, int inv[], int fac[]) {
	if (n == 0 && m == 0) return 1;
	LL a = n % mod, b = m % mod;
	if (b > a) return 0;
	return (((((lucas(n / mod, m / mod, mod, inv, fac) * fac[a]) % mod) * inv[b]) % mod) * inv[a - b]) % mod;
}

LL binomal(int p, int q) {
	return lucas(p + q, q, MOD, inv, fac);
}
