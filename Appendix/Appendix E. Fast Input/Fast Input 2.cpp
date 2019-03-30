inline int readint() {
	char c = getchar();
	while (!isdigit(c)) c = getchar();
	int x = 0;
	while (isdigit(c)) {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x;
}
