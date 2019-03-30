//BAPC 2012 Preliminaries C. Cubing
#include <cstdio>

char s[6][3][4];

void Rotate1(int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3, int x4, int y4, int z4) {
	char tp = s[x4][y4][z4];
	s[x4][y4][z4] = s[x3][y3][z3];
	s[x3][y3][z3] = s[x2][y2][z2];
	s[x2][y2][z2] = s[x1][y1][z1];
	s[x1][y1][z1] = tp;
}

void Rotate2(int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3, int x4, int y4, int z4) {
	Rotate1(x4, y4, z4, x3, y3, z3, x2, y2, z2, x1, y1, z1);
}

int main() {
	int T, q;
	char query[5];
	for (scanf("%d", &T); T--; ) {
		for (int i = 0; i < 3; i ++) for (int j = 0; j < 3; j ++) {
			s[0][i][j] = 'w';
			s[1][i][j] = 'y';
			s[2][i][j] = 'r';
			s[3][i][j] = 'o';
			s[4][i][j] = 'g';
			s[5][i][j] = 'b';
		}
		for (int i = 0; i < 6; i ++) for (int j = 0; j < 3; j ++) s[i][j][3]=0;
		for (scanf("%d", &q); q --; ) {
			scanf("%s", query);
			if (query[0] == 'U') {
				if (query[1] == '-') {
					for (int i=0; i<3; i++) Rotate1(2, 0, i, 5, 0, i, 3, 0, i, 4, 0, i);
					Rotate1(0, 0, 0, 0, 2, 0, 0, 2, 2, 0, 0, 2);
					Rotate1(0, 1, 0, 0, 2, 1, 0, 1, 2, 0, 0, 1);
				} else {
					for (int i=0; i<3; i++) Rotate2(2, 0, i, 5, 0, i, 3, 0, i, 4, 0, i);
					Rotate2(0, 0, 0, 0, 2, 0, 0, 2, 2, 0, 0, 2);
					Rotate2(0, 1, 0, 0, 2, 1, 0, 1, 2, 0, 0, 1);
				}
			} else if (query[0] == 'D') {
				if (query[1] == '-') {
					for (int i=0; i<3; i++) Rotate1(2, 2, i, 4, 2, i, 3, 2, i, 5, 2, i);
					Rotate1(1, 0, 0, 1, 2, 0, 1, 2, 2, 1, 0, 2);
					Rotate1(1, 1, 0, 1, 2, 1, 1, 1, 2, 1, 0, 1);
				} else {
					for (int i=0; i<3; i++) Rotate2(2, 2, i, 4, 2, i, 3, 2, i, 5, 2, i);
					Rotate2(1, 0, 0, 1, 2, 0, 1, 2, 2, 1, 0, 2);
					Rotate2(1, 1, 0, 1, 2, 1, 1, 1, 2, 1, 0, 1);
				}
			} else if (query[0] == 'F') {
				if (query[1] == '-') {
					Rotate1(0, 2, 0, 4, 2, 2, 1, 0, 2, 5, 0, 0);
					Rotate1(0, 2, 1, 4, 1, 2, 1, 0, 1, 5, 1, 0);
					Rotate1(0, 2, 2, 4, 0, 2, 1, 0, 0, 5, 2, 0);
					Rotate1(2, 0, 0, 2, 2, 0, 2, 2, 2, 2, 0, 2);
					Rotate1(2, 1, 0, 2, 2, 1, 2, 1, 2, 2, 0, 1);
				} else {
					Rotate2(0, 2, 0, 4, 2, 2, 1, 0, 2, 5, 0, 0);
					Rotate2(0, 2, 1, 4, 1, 2, 1, 0, 1, 5, 1, 0);
					Rotate2(0, 2, 2, 4, 0, 2, 1, 0, 0, 5, 2, 0);
					Rotate2(2, 0, 0, 2, 2, 0, 2, 2, 2, 2, 0, 2);
					Rotate2(2, 1, 0, 2, 2, 1, 2, 1, 2, 2, 0, 1);
				}
			} else if (query[0] == 'B') {
				if (query[1] == '-') {
					Rotate1(0, 0, 0, 5, 0, 2, 1, 2, 2, 4, 2, 0);
					Rotate1(0, 0, 1, 5, 1, 2, 1, 2, 1, 4, 1, 0);
					Rotate1(0, 0, 2, 5, 2, 2, 1, 2, 0, 4, 0, 0);
					Rotate1(3, 0, 0, 3, 2, 0, 3, 2, 2, 3, 0, 2);
					Rotate1(3, 1, 0, 3, 2, 1, 3, 1, 2, 3, 0, 1);
				} else {
					Rotate2(0, 0, 0, 5, 0, 2, 1, 2, 2, 4, 2, 0);
					Rotate2(0, 0, 1, 5, 1, 2, 1, 2, 1, 4, 1, 0);
					Rotate2(0, 0, 2, 5, 2, 2, 1, 2, 0, 4, 0, 0);
					Rotate2(3, 0, 0, 3, 2, 0, 3, 2, 2, 3, 0, 2);
					Rotate2(3, 1, 0, 3, 2, 1, 3, 1, 2, 3, 0, 1);
				}
			} else if (query[0] == 'L') {
				if (query[1] == '-') {
					Rotate1(0, 2, 0, 3, 0, 2, 1, 2, 0, 2, 2, 0);
					Rotate1(0, 1, 0, 3, 1, 2, 1, 1, 0, 2, 1, 0);
					Rotate1(0, 0, 0, 3, 2, 2, 1, 0, 0, 2, 0, 0);
					Rotate1(4, 0, 0, 4, 2, 0, 4, 2, 2, 4, 0, 2);
					Rotate1(4, 1, 0, 4, 2, 1, 4, 1, 2, 4, 0, 1);
				} else {
					Rotate2(0, 2, 0, 3, 0, 2, 1, 2, 0, 2, 2, 0);
					Rotate2(0, 1, 0, 3, 1, 2, 1, 1, 0, 2, 1, 0);
					Rotate2(0, 0, 0, 3, 2, 2, 1, 0, 0, 2, 0, 0);
					Rotate2(4, 0, 0, 4, 2, 0, 4, 2, 2, 4, 0, 2);
					Rotate2(4, 1, 0, 4, 2, 1, 4, 1, 2, 4, 0, 1);
				}
			} else {
				if (query[1] == '-') {
					Rotate1(0, 2, 2, 2, 2, 2, 1, 2, 2, 3, 0, 0);
					Rotate1(0, 1, 2, 2, 1, 2, 1, 1, 2, 3, 1, 0);
					Rotate1(0, 0, 2, 2, 0, 2, 1, 0, 2, 3, 2, 0);
					Rotate1(5, 0, 0, 5, 2, 0, 5, 2, 2, 5, 0, 2);
					Rotate1(5, 1, 0, 5, 2, 1, 5, 1, 2, 5, 0, 1);
				} else {
					Rotate2(0, 2, 2, 2, 2, 2, 1, 2, 2, 3, 0, 0);
					Rotate2(0, 1, 2, 2, 1, 2, 1, 1, 2, 3, 1, 0);
					Rotate2(0, 0, 2, 2, 0, 2, 1, 0, 2, 3, 2, 0);
					Rotate2(5, 0, 0, 5, 2, 0, 5, 2, 2, 5, 0, 2);
					Rotate2(5, 1, 0, 5, 2, 1, 5, 1, 2, 5, 0, 1);
				}
			}
		}
		for (int i=0; i<3; i++) puts(s[0][i]);
	}
}
