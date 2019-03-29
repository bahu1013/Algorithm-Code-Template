#include <stdio.h>
#include <string.h>
#define N 200100
#define M 26

char pattern[M];
char text[M];
int h[N], m, n;

void insert() {
	int k = 0;
	m=strlen(pattern);
	h[1] = 0;
	for (int i = 2; i <= m; i ++) {
		while (k && pattern[k] != pattern[i - 1]) k = h[k];
		if (pattern[k] == pattern[i - 1]) k ++;
		h[i] = k;
	}
}

void find() {
	int k = 0;
	n = strlen(text);
	for (int i = 1; i <= n; i ++) {
		while (k && pattern[k] != text[i - 1]) k = h[k];
		if (pattern[k] == text[i - 1]) k ++;
		if (k == m) {
			printf("Pattern occurs with shift %d\n", i – m + 1);
			k = h[k];
		}
	}
}

int main() {
	scanf("%s", pattern);
	scanf("%s", text);
	insert();
	find();
}
