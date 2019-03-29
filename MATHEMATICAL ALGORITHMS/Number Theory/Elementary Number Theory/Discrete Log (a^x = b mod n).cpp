/*
	Baby-step sqrt(n)*log n
	input:a b n
	output a^x=b (mod n)
*/
#include <stdio.h>
#include <iostream>
#include <map>
#include <cmath>
using namespace std;

#define int64 long long
#define mod(x,n) (((x) % (n) + (n)) % (n))

int64 expmod(int64 a, int64 b, int64 n) {
	int64 re = 1, y = a % n;
	while (b) {
		if (b % 2) re = (re * y) % n;
		b >>= 1, y = (y * y) % n;
	}
	return re;
}

int64 gcd(int64 a, int64 b, int64 &x, int64 &y) {
	if (!b) {
	   x = 1, y = 0;
	   return a;
	} else {
		int64 tp, bx, by;
		tp = gcd(b, a%b, x, y);
		bx = x, by = y;
		y = bx - (a / b) * by, x = by;
		return tp;
	}
}

int64 inv(int64 a, int64 n) {
	int64 x, y, tp;
	tp = gcd(a, n, x, y);
	if (tp == 1) return mod(x, n);
	else return -1;
}

int64 logmod(int64 a, int64 b, int64 n) {
	int64 up = (int64) ceil(sqrt(n));

	map <int64, int64> mp;
	map <int64, int64>::iterator it;
	mp.clear();

	for(int64 i = 0; i <= up; i ++) {
		int64 k = expmod(a, i, n);
		it = mp.find(k);
		if (it == mp.end()) mp[k] = i;
	}

	int64 inva = inv(expmod(a, up, n), n);
	for(int64 i = 0; i < up; i ++) {
		if (mp.find(b) != mp.end()) return i * up + mp[b];
		b = (b * inva) % n;
	}

	return -1;
}

//-----------Here is the special deal-----------------------

int64 gcd(int64 a, int64 b) {
	if (b == 0) return a;
	else return gcd(b, a % b);
}

int64 specialdeal(int64 a, int64 b, int64 n) {
//We still assume n>0,n=0 is impossible!
//if (a==0) a=nk,k >= 1
	if (b == 1 || n == 1) return 0;
	if (a == 0 && b == 0) return 1;
	if (a == 0 && b != 0) return -1;
	int64 k = 1, tp = a;
	while (gcd(n, tp) != gcd(n, (tp * a) % n)) {
		if (tp == b) return k;
		k ++, tp = (tp * a) % n;
	}
	int64 g = gcd(n, tp);
	if (g == n && b == 0) return k;
	if (g == n && b != 0) return -1;
	if (b % g) return -1;
	tp /= g, b /= g, n /= g;
	b = (b * inv(tp, n)) % n;
	tp = logmod(a, b, n);
	if (tp == -1) return -1;
	return tp + k;
}

int main() {
//	freopen("logmod.in","r",stdin);
//	freopen("my.out","w",stdout);
	int64 a, b, n;
	while (cin >> a >> b >> n) {
		a = a % n, b = b % n; //if (a<n,b<n) then this step is not necessary!
		int64 tp;
		if (gcd(n, a) > 1 || a == 0) tp = specialdeal(a, b, n);
			else tp = logmod(a, b, n);
		if (tp == -1) printf("no solution\n");
			else cout << tp << endl;
	}
	return 0;
}
