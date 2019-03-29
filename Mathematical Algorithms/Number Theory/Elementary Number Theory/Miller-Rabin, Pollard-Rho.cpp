#include<stdio.h>
#include<algorithm>
#include<stdlib.h>
#include<time.h>
#include<math.h>
using namespace std;

typedef __int64 int64;

const char * pformat = "%I64d";

int64 big_rand(int64 m) {
	int64 x = rand(); x *= rand();
	if (x < 0) x = -x;
	return x %= m;
}// x*y % n

int64 mod_mul(int64 x, int64 y, int64 n) {
	if (x == 0 || y == 0) return 0;
	return (((x & 1) * y) % n + (mod_mul(x >> 1, y, n) << 1) % n) % n;
}// x^y % n

int64 mod_exp(int64 x, int64 y, int64 n) {
	int64 ret = 1;
	while (y) {
		if (y & 1) ret = mod_mul(ret, x, n);
		x = mod_mul(x, x, n);
		y >>= 1;
	}
	return ret;
}

bool Miller_Rabbin(int64 n) {// O(times * (log N)^3)
	if (n == 2) return true;
	if (n < 2 || !(n & 1)) return false;
	int64 m = n - 1, k = 0;
	while (!(m & 1)) m >>= 1, k ++;// binary scan
	for (int i = 0, j; i < 4; i ++) {// test times
		int64 x = big_rand(n - 2) + 2;
		x = mod_exp(x, m, n);
		if (x == 1) continue;
		for (j = 0; j < k; j ++) {
			if (x == n - 1) break;
			x = mod_mul(x, x, n);
		}
		if (j >= k) return false;
	}
	return true;
}

int64 gcd(int64 x, int64 y) {
	while (x) {int64 t = y % x; y = x; x = t;}
	return y;
}

int64 func(int64 x, int64 m) {
	return (mod_mul(x, x, m) + 1) % m;
}

int64 Pollard(int64 n) {
	if (Miller_Rabbin(n)) return n;
	if (!(n & 1)) return 2;
	int64 i = 1;
	while (true) {
		int64 x = i ++, y = func(x, n), ret = gcd(y - x, n);
		while (ret == 1) {
			x = func(x, n);
			y = func(func(y, n), n);
			ret = gcd((y - x + n) % n, n) % n;
		}
		if (0 < ret && ret < n) return ret;
	}
}

int64 factor[100], nfac, minfac;

void cal_factor(int64 n) {
	int64 x = Pollard(n);
	if (x == n) {//factor[nfac ++] = x;
		minfac = min(minfac, x);
		return;
	}
	cal_factor(x);
	cal_factor(n / x);
}

void print_factor(int64 n) {
	nfac = 0;
	cal_factor(n);
	std::sort(factor, factor + nfac);
	for (int i = 0; i < nfac; i ++) {
		if (i > 0) putchar(' ');
		printf(pformat, factor[i]);
	}
	puts("");
}

const int64 lim = 100000;

int main() {
	int64 n, t, i;
	srand((unsigned)time(NULL));
	scanf(pformat, &t);
	//t=1;
	while (t --) {
		scanf(pformat, &n);
		//n=.1+(1e9+7);
		n *= n;
		printf("%I64d ", n);
		if (Miller_Rabbin(n)) puts("Prime");
		else {
			if (!(n & 1)) puts("2");
			else {
				for (minfac = 3; minfac < lim && n % minfac; minfac += 2);
				if (minfac >= lim) {
					int64 rn = sqrt(1.0 * n);
					if (rn * rn == n) {
                        minfac = rn;
                        cal_factor(rn);
                    } else {
                        minfac = n;
                        cal_factor(n);
                    }
                }
				printf(pformat, minfac);
				puts("");
			}
		}
	}
}
