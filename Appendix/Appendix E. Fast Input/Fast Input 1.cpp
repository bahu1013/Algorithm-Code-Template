int nextInt() {
	char in;
	bool neg = false;
	while (((in = getchar()) > '9' || in < '0') && in != '-');
	if (in == '-') {
		neg = true;
		while ((in = getchar()) > '9' || in < '0');
	}
	int rlt = in - '0';
	while (in = getchar(), in >= '0' && in <= '9') rlt *= 10, rlt += in - '0';
	if (neg) rlt = -rlt;
	return rlt;
}
