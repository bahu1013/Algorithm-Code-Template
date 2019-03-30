#include <cstdio>
#include <string>

using namespace std;

struct IO {
	int cur;

	inline char nextChar() { return cur = getchar(); }
	inline char peekChar() { return cur; }
	inline operator bool() { return (peekChar() != 0); }
	inline static bool isSpace(char c) { return (c < '0' && c); }
	inline bool skipBlanks() { while (isSpace(nextChar())); return peekChar() != 0; }
	IO() : cur(0) {}

	inline IO& operator >> (char & c) { c = nextChar(); return *this; }

	inline IO& operator >> (char * buf) {
		if (skipBlanks()) {
			if (peekChar()) {
				*(buf++) = peekChar();
				while (!isSpace(nextChar())) *(buf++) = peekChar();
			}
			*(buf++) = 0;
		}
		return *this;
	}

	inline IO& operator >> (string & s) {
		if (skipBlanks()) {
			s += peekChar();
			while (!isSpace(nextChar())) s += peekChar();
		}
		return *this;
	}

	inline IO& operator >> (int & n) {
		if (skipBlanks()) {
			int sign = +1;
			if (peekChar() == '-') {
				sign = -1;
				n = nextChar() - '0';
			} else n = peekChar() - '0';
			while (!isSpace(nextChar())) {
				n *= 10;
				n += peekChar() - '0';
			}
			n *= sign;
		}
		return *this;
	}

	#define cin io
	#define endl ('\n')
} io;

int main() {
	string s;
	cin >> s;
	puts(s.c_str());
}
