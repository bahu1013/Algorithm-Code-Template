//Solving x^2=a (mod n)
//If there are no solution, return -1
ll expmod(ll a, ll b, ll n) {
	//a^b%n
	ll re = 1, y = a % n;
	for (; b; b >>= 1, y = (y * y) % n)
		if (b & 1) re = (re * y) % n;
	return re;
}

ll sqrtmod(ll a, ll n) {
	ll b, k, i, x;
	if (n == 2) return a % n;
	if (expmod(a, (n - 1) / 2, n) == 1) {
		if (n % 4 == 3) x=expmod(a, (n + 1) / 4, n);
		else{
			for (b = 1; expmod(b, (n - 1) / 2, n) == 1; b ++);
			i=(n - 1) / 2, k = 0;
			do{
				i /= 2, k /= 2;
				if ((expmod(a, i, n) * expmod(b, k, n) + 1) % n == 0) k += (n - 1) / 2;
			} while (i % 2 == 0);
			x=(expmod(a, (i + 1) / 2, n) * expmod(b, k / 2, n)) % n;
		}
		if (x * 2 > n) x = n - x;
		return x;
	}
	return -1;
}

