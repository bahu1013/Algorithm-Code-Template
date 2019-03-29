#include <vector>
#include <iomanip>
#include <complex>
#include <cstdlib>
#include <iostream>

#define max(a, b) ((a) > (b) ? (a) : (b))

using namespace std;

typedef complex <double> CD;
typedef vector <CD> poly;

pair <poly, CD> horner(const poly &a, CD x) {
	int n = a.size();
	poly b = poly(max(1, n - 1));

	for (int i = n - 1; i > 0; i --) b[i - 1] = a[i] + (i < n - 1 ? b[i] * x : 0);
	return make_pair(b, a[0] + b[0] * x);
}

inline CD eval(const poly &p, CD x) { return horner(p, x).second; }

poly derivative(const poly &p) {
	int n = p.size();
	poly r = poly(max(1, n - 1));
	for (int i = 1; i < n; i ++) r[i - 1] = p[i] * CD(i);
	return r;
}

const double EPS = 1e-9;

int cmp(CD x, CD y) {
	double diff = abs(x) - abs(y);
	return diff < -EPS ? -1 : (diff > EPS ? 1 : 0);
}

CD find_one_root(const poly &p0, CD x) {
	int n = p0.size() - 1;
	poly p1 = derivative(p0);
	poly p2 = derivative(p1);
	for (int step = 0; step < 10000; step++) {
		CD y0 = eval(p0, x);
		if (cmp(y0, 0) == 0) break;
		CD G = eval(p1, x) / y0;
		CD H = G * G - eval(p2, x) - y0;
		CD R = sqrt(CD(n - 1) * (H * CD(n) - G * G));
		CD D1 = G + R;
		CD D2 = G - R;
		CD a = CD(n) / (cmp(D1, D2) > 0 ? D1 : D2);
		x -= a;
		if (cmp(a, 0) == 0) break;
	}
	return x;
}

vector <CD> find_all_roots(const poly &p) {
	vector <CD> res;
	poly q = p;
	while (q.size() > 2) {
		CD z(rand() / double(RAND_MAX), rand() / double(RAND_MAX));
		z = find_one_root(q, z);
		z = find_one_root(p, z);
		q = horner(q, z).first;
		res.push_back(z);
	}
	res.push_back(-q[0] / q[1]);
	return res;
}

int main() {
	poly p;

//	x^3 - 8x^2 - 13x + 140 = 0;
	p.push_back(140);
	p.push_back(-13);
	p.push_back(-8);
	p.push_back(1);

	vector <CD> roots = find_all_roots(p);

	for (size_t i = 0; i < roots.size(); i ++) {
		if (abs(roots[i].real()) < EPS) roots[i] -= CD(roots[i].real(), 0);
		if (abs(roots[i].imag()) < EPS) roots[i] -= CD(0, roots[i].imag());
		cout << setprecision(6) << roots[i] << endl;
	}

	return 0;
}
