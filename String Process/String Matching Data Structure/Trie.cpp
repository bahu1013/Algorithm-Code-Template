#include <cstdio>
#include <memory.h>

#define N 1001000
#define SIGMA 26
#define leaf -1

int *hp, h[N], hh[N], P;

void insert(int v, char* s) {
	if (!*s) {
		hh[v] = P;
		return;
	}
	if (h[v] == leaf) {
		h[v] = hp - h;
		for (int i = 0; i < SIGMA; i ++) *hp++ = leaf;
	}
	insert(h[v] + *s - 'a', s + 1);
}

int find(char *s) {
	int v = 0;
	for ( ; *s; s ++) {
		if (h[v] == leaf) return -1;
		v = h[v] + *s - 'a';
	}
	return hh[v];
}

char s[N];

int main() {
	int n, q;
	scanf("%d", &n);
	hp = h;
	*(hp ++) = leaf;
	memset(hh, 0, sizeof(hh));
	for (int i = 0; i < n; i ++) {
		scanf("%s", s);
		P ++;
		insert(0, s);
	}
	for (scanf("%d", &q); q --; ) {
		scanf("%s", s);
		int rlt = find(s);
		if (rlt < 0) puts("Not Found");
		else if (!rlt) puts("It's only a prefix of a word and not found");
		else printf("It's %d-th word in Dictionary.\n", rlt);
	}
}
