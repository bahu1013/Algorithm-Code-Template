#include <stdio.h>
#include <string.h>
#define N 200100
#define M 26

char pattern[M];
char text[M];
int aut[N][M], final;

void Automaton() {
	final = strlen(pattern);
	for (int i = 0; i < M; i ++) aut[0][i] = 0;
	aut[0][pattern[0] - 'a'] = 1;
	int back = 0;
	for (int i = 1; i < final; i ++) {
		int k = pattern[i] - 'a';
		aut[i][k] = i + 1;
		for (int j = 0; j < M; j ++) if (j != k) {
			aut[i][j] = aut[back][j];
		}
		back = aut[back][k];
	}
	for (int i = 0; i < M; i ++) aut[final][i] = aut[back][i];
}

void Search() {
	int len = strlen(text);
	int q = 0;
	for (int i = 0; i < len; i ++) {
		q = aut[q][text[i] - 'a'];
		if (q == final) printf("Pattern occurs at position %d\n", i – final + 2);
	}
}

int main() {
	scanf("%s", pattern);
	scanf("%s", text);
	Automaton();
	Search();
}
