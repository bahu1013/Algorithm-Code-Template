struct pnt {
	double x, y;
	pnt (double x = 0, double y = 0): x(x), y(y) {}
	inline pnt operator - (const pnt &a) const { return pnt(x - a.x, y - a.y); }
	inline pnt operator + (const pnt &a) const { return pnt(x + a.x, y + a.y); }
	inline pnt operator * (const double &a) const { return pnt(x * a, y * a); }
	inline pnt operator / (const double &a) const { return pnt(x / a, y / a); }
	inline double operator & (const pnt &a) const { return x * a.x + y * a.y; }
	inline double operator ^ (const pnt &a) const { return x * a.y - y * a.x; }
	inline void input() { x = y = 0, scanf("%lf %lf", &x, &y); }
	inline pnt operator * (const pnt &a) const { return pnt(x * a.x - y * a.y, x * a.y + y * a.x); }
	inline pnt operator / (const pnt &a) const {
		double len = a & a;
		return pnt((a & *this) / len, (a ^ *this) / len);
	}
	void FastInput() {
		int a, b;
		scanf("%d %d", &a, &b);
		x = 1.0 * a;
		y = 1.0 * b;
	}
	inline void print() { printf("(%lf, %lf)\n", x, y); }
	inline bool operator < (const pnt &a) const {
		if (fabs(x - a.x) > ep) return x < a.x;
		return y < a.y;
	}
	inline bool operator == (const pnt &a) const {
		return fabs(x - a.x) < ep && fabs(y - a.y) < ep;
	}
	inline pnt Rotate(const double &angle) {
		pnt R = pnt(sin(angle), cos(angle)), C = *this;
		return pnt(C ^ R, C & R);
	}
	inline double dist() { return sqrt(x * x + y * y); }
	inline pnt norm() { return (*this) / dist(); }
};

struct Pnt {
	double x, y, z;
	Pnt (double x = 0, double y = 0, double z = 0): x(x), y(y), z(z) {};
	inline Pnt operator + (const Pnt &a) const { return Pnt(x + a.x, y + a.y, z + a.z); }
	inline Pnt operator - (const Pnt &a) const { return Pnt(x - a.x, y - a.y, z - a.z); }
	inline Pnt operator * (const double &a) const { return Pnt(x * a, y * a, z * a); }
	inline Pnt operator / (const double &a) const { return Pnt(x / a, y / a, z / a); }
	inline Pnt operator ^ (const Pnt &a) const { return Pnt(y * a.z - z * a.y, z * a.x - x * a.z, x * a.y - y * a.x); }
	inline double operator & (const Pnt &a) const { return x * a.x + y * a.y + z * a.z; }
	inline friend double MixedProduct (const Pnt &a, const Pnt &b, const Pnt &c) { return (a ^ b) & c; }
	inline friend double dist(const Pnt &a) { return sqrt(a & a); }
	inline bool operator < (const pnt &a) const {
		if (fabs(x - a.x) > ep) return x < a.x;
		if (fabs(y - a.y) > ep) return y < a.y;
		return z < a.z;
	}
	inline bool operator == (const pnt &a) const {
		return fabs(x - a.x) < ep && fabs(y - a.y) < ep && fabs(z - a.z) < ep;
	}
	inline void input() { x = y = z = 0, scanf("%lf %lf %lf", &x, &y, &z); }
	inline void FastInput() {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		x = 1.0 * a;
		y = 1.0 * b;
		z = 1.0 * c;
	}
	inline void print() { printf("%lf %lf %lf\n", x, y, z); }
};
