class Fraction {
	BigInteger a, b;
	Fraction() {
		a = BigInteger.ZERO;
		b = BigInteger.ONE;
	}
	Fraction(BigInteger aa, BigInteger bb) {
		BigInteger g = aa.gcd(bb);
		a = aa.divide(g);
		b = bb.divide(g);
	}
	Fraction add(Fraction B) {
		return new Fraction(a.multiply(B.b).add(B.a.multiply(b)), b.multiply(B.b));
	}
	Fraction subtract(Fraction B) {
		return new Fraction(a.multiply(B.b).subtract(B.a.multiply(b)), b.multiply(B.b));
	}
	Fraction multiply(Fraction B) {
		return new Fraction(a.multiply(B.a), b.multiply(B.b));
	}
	Fraction divide(Fraction B) {
		BigInteger bb = b.multiply(B.a);
		BigInteger aa = a.multiply(B.b);

		if (bb.compareTo(BigInteger.ZERO) < 0) {
			bb = bb.negate();
			aa = aa.negate();
		}
		return new Fraction(aa, bb);
	}
	int compareTo(Fraction B) {
		if (b.compareTo(B.b) == 0) return a.compareTo(B.a);
		Fraction ret = subtract(B);
		return ret.a.compareTo(BigInteger.ZERO);
	}
	void print() {
		System.out.print(a + "/" + b + "\n");
	}
};
