//SEERC 2006 Problem A. Sudoku
#include <cstdio>
#include <memory.h>
#include <vector>

using namespace std;

const int R = 4;
const char SC = 'A';
const int N = R * R;

char s[N][N + 1];
bool chk[N][N][N];
int conx[N][N][N * 3], cony[N][N][N * 3], sz[N][N];

int Runs;

bool Input() {
	int bf = scanf("%s", s[0]);
	if (bf <= 0) return 0;

	for (int i = 1; i < N; i ++) scanf("%s", s[i]);

	return 1;
}

void Set(int x, int y, int p) {
	s[x][y] = p + SC;
	for (int k = 0; k < N; k ++) chk[x][y][k] = 0;
	chk[x][y][p] = 1;
	for (int k = 0; k < sz[x][y]; k ++) chk[conx[x][y][k]][cony[x][y][k]][p] = 0;
}

bool Single() {
	bool bf = 1, ret = 0;
	while (bf) {
		bf = 0;
		for (int i = 0; i < N; i ++)
		for (int j = 0; j < N; j ++) if (s[i][j] == '-') {
			int tot = 0, p;
			for (int k = 0; k < N; k ++) {
				if (chk[i][j][k]) tot ++, p = k;
			}
			if (tot == 1) bf = ret = 1, Set(i, j, p);
		}
	}
	return ret;
}

bool HiddenSingle() {
//Rectangle
	bool ret = 0;
	bool bf = 1;

	while (bf) {
		bf = 0;
		for (int i = 0; i < R; i ++)
		for (int j = 0; j < R; j ++)
		for (int k = 0; k < N; k ++) {
			int tot = 0, px, py;
			for (int x = i * R; x < (i + 1) * R; x ++)
			for (int y = j * R; y < (j + 1) * R; y ++) {
				if (!chk[x][y][k]) tot ++;
				else px = x, py = y;
			}
			if (tot + 1 == N && s[px][py] == '-') bf = 1, Set(px, py, k), ret = 1;
		}
	}
//Row
	bf = 1;
	while (bf) {
		bf = 0;
		for (int i = 0; i < N; i ++)
		for (int k = 0; k < N; k ++) {
			int tot = 0, px, py;
			for (int y = 0; y < N; y ++) {
				if (!chk[i][y][k]) tot ++;
				else px = i, py = y;
			}
			if (tot + 1 == N && s[px][py] == '-') bf = 1, Set(px, py, k), ret = 1;
		}
	}
//Col
	bf = 1;
	while (bf) {
		bf = 0;
		for (int j = 0; j < N; j ++)
		for (int k = 0; k < N; k ++) {
			int tot = 0, px, py;
			for (int x = 0; x < N; x ++) {
				if (!chk[x][j][k]) tot ++;
				else px = x, py = j;
			}
			if (tot + 1 == N && s[px][py] == '-') bf = 1, Set(px, py, k), ret = 1;
		}
	}
	return ret;
}

bool LockedCandidatesI() {
	bool ret = 0, bf = 1;
	while (bf) {
		bf = 0;
		for (int i = 0; i < R; i ++)
		for (int j = 0; j < R; j ++) {
			for (int k = 0; k < N; k ++) {
				bool Exist = 0;
				for (int x = i * R; x < (i + 1) * R; x ++) {
					for (int y = j * R; y < (j + 1) * R; y ++) if (s[x][y] == k + SC) {
						Exist = 1;
						break;
					}
					if (Exist) break;
				}
				if (Exist) continue;
				int tot = 0, row;
				for (int x = i * R; x < (i + 1) * R; x ++) {
					bool fl = 0;
					for (int y = j * R; y < (j + 1) * R; y ++) if (chk[x][y][k]) {
						fl = 1;
						row = x;
						break;
					}
					tot += fl;
				}
				if (tot == 1) {
					for (int y = 0; y < j * R; y ++) {
						if (chk[row][y][k]) bf = ret = 1;
						chk[row][y][k] = 0;
					}
					for (int y = (j + 1) * R; y < N; y ++) {
						if (chk[row][y][k]) bf = ret = 1;
						chk[row][y][k] = 0;
					}
				}
			}
		}
	}

	bf = 1;
	while (bf) {
		bf = 0;
		for (int i = 0; i < R; i ++)
		for (int j = 0; j < R; j ++) {
			for (int k = 0; k < N; k ++) {
				bool Exist = 0;
				for (int x = i * R; x < (i + 1) * R; x ++) {
					for (int y = j * R; y < (j + 1) * R; y ++) if (s[x][y] == k + SC) {
						Exist = 1;
						break;
					}
					if (Exist) break;
				}
				if (Exist) continue;
				int tot = 0, col;
				for (int y = j * R; y < (j + 1) * R; y ++) {
					bool fl = 0;
					for (int x = i * R; x < (i + 1) * R; x ++) if (chk[x][y][k]) {
						fl = 1;
						col = y;
						break;
					}
					tot += fl;
				}
				if (tot == 1) {
					for (int x = 0; x < i * R; x ++) {
						if (chk[x][col][k]) bf = ret = 1;
						chk[x][col][k] = 0;
					}
					for (int x = (i + 1) * R; x < N; x ++) {
						if (chk[x][col][k]) bf = ret = 1;
						chk[x][col][k] = 0;
					}
				}
			}
		}
	}
	return ret;
}

bool LockedCandidatesII() {
	bool ret = 0, bf = 1;
	while (bf) {
		bf = 0;
		for (int i = 0; i < R; i ++)
		for (int j = 0; j < R; j ++)
		for (int k = 0; k < N; k ++) {
			for (int col = j * R; col < (j + 1) * R; col ++) {
				bool fl = 0;
				for (int x = 0; x < i * R; x ++) if (chk[x][col][k]) {
					fl = 1;
					break;
				}
				if (fl) continue;
				for (int x = (i + 1) * R; x < N; x ++) if (chk[x][col][k]) {
					fl = 1;
					break;
				}
				if (fl) continue;
				for (int y = j * R; y < (j + 1) * R; y ++) if (y != col) {
					for (int x = i * R; x < (i + 1) * R; x ++) {
						if (chk[x][y][k]) bf = ret = 1;
						chk[x][y][k] = 0;
					}
				}
			}
		}
	}
	bf = 1;
	while (bf) {
		bf = 0;
		for (int i = 0; i < R; i ++)
		for (int j = 0; j < R; j ++)
		for (int k = 0; k < N; k ++) {
			for (int row = i * R; row < (i + 1) * R; row ++) {
				bool fl = 0;
				for (int y = 0; y < j * R; y ++) if (chk[row][y][k]) {
					fl = 1;
					break;
				}
				if (fl) continue;
				for (int y = (j + 1) * R; y < N; y ++) if (chk[row][y][k]) {
					fl = 1;
					break;
				}
				if (fl) continue;
				for (int x = i * R; x < (i + 1) * R; x ++) if (x != row) {
					for (int y = j * R; y < (j + 1) * R; y ++) {
						if (chk[x][y][k]) bf = ret = 1;
						chk[x][y][k] = 0;
					}
				}
			}
		}
	}
	return ret;
}

bool HiddenPairs() {
	bool bf = 1, ret = 0;
	while (bf) {
		bf = 0;
		for (int i = 0; i < R; i ++)
		for (int j = 0; j < R; j ++) {
			for (int k = 0; k < N; k ++)
			for (int kk = k + 1; kk < N; kk ++) {
				int tot = 0;
				int px[N], py[N], cp = 0;
				for (int x = i * R; x < (i + 1) * R; x ++)
				for (int y = j * R; y < (j + 1) * R; y ++) {
					if (chk[x][y][k] && chk[x][y][kk]) px[cp] = x, py[cp ++] = y;
					if (!chk[x][y][k] && !chk[x][y][kk]) tot ++;
				}
				if (cp != 2 || tot + cp != N) continue;
				for (int u = 0; u < cp; u ++) {
					for (int p = 0; p < N; p ++) if (p != k && p != kk) {
						if (chk[px[u]][py[u]][p]) ret = bf = 1;
						chk[px[u]][py[u]][p] = 0;
					}
				}
			}
		}
	}
	return ret;
}

void Eliminate() {
	bool bf = 1;
	while (bf) {
		bf = 0;
		bf |= Single();
		bf |= HiddenSingle();
		bf |= LockedCandidatesI();
		bf |= LockedCandidatesII();
		bf |= HiddenPairs();
	}
}

void Init() {
	for (int i = 0; i < N; i ++) {
		for (int j = 0; j < N; j ++) {
			for (int k = 0; k < N; k ++) {
				chk[i][j][k] = 1;
			}
		}
	}

	for (int i = 0; i < N; i ++) {
		for (int j = 0; j < N; j ++) {
			sz[i][j] = 0;
			int ii = i / R, jj = j / R;
			for (int I = ii * R; I < (ii + 1) * R; I ++) {
				for (int J = jj * R; J < (jj + 1) * R; J ++) {
					if (I == i && J == j) continue;
					conx[i][j][sz[i][j]] = I;
					cony[i][j][sz[i][j] ++] = J;
				}
			}
			for (int I = 0; I < ii * R; I ++) {
				conx[i][j][sz[i][j]] = I;
				cony[i][j][sz[i][j] ++] = j;
			}
			for (int I = (ii + 1) * R; I < N; I ++) {
				conx[i][j][sz[i][j]] = I;
				cony[i][j][sz[i][j] ++] = j;
			}
			for (int J = 0; J < jj * R; J ++) {
				conx[i][j][sz[i][j]] = i;
				cony[i][j][sz[i][j] ++] = J;
			}
			for (int J = (jj + 1) * R; J < N; J ++) {
				conx[i][j][sz[i][j]] = i;
				cony[i][j][sz[i][j] ++] = J;
			}
		}
	}

	for (int i = 0; i < N; i ++) {
		for (int j = 0; j < N; j ++) {
			if (s[i][j] != '-') {
				int c = s[i][j] - SC;
				Set(i, j, c);
			}
		}
	}
}

bool Find(int dp) {
	bool bf = 0;
	for (int i = 0; i < N; i ++) {
		for (int j = 0; j < N; j ++) if (s[i][j] == '-') {
			bf = 1;
			break;
		}
	}
	if (!bf) return 1;
	int cnt = N + 1, x, y;
	bool mem[N][N][N];
	char t[N][N + 1];
	memcpy(mem, chk, sizeof(chk));
	memcpy(t, s, sizeof(s));
	Eliminate();
	for (int i = 0; i < N; i ++) {
		for (int j = 0; j < N; j ++) if (s[i][j] == '-') {
			int cur = 0;
			for (int k = 0; k < N; k ++) if (chk[i][j][k]) cur ++;
			if (cnt > cur) cnt = cur, x = i, y = j;
		}
	}
	if (!cnt) {
		memcpy(chk, mem, sizeof(chk));
		memcpy(s, t, sizeof(s));
		return 0;
	}
	bool A[N], B[N * 3];
	for (int i = 0; i < N; i ++) A[i] = chk[x][y][i];
	for (int k = 0; k < N; k ++) if (chk[x][y][k]) {
		for (int i = 0; i < sz[x][y]; i ++) B[i] = chk[conx[x][y][i]][cony[x][y][i]][k];
		Set(x, y, k);
		if (Find(dp + 1)) return 1;
		s[x][y] = '-';
		for (int i = 0; i < N; i ++) chk[x][y][i] = A[i];
		for (int i = 0; i < sz[x][y]; i ++) chk[conx[x][y][i]][cony[x][y][i]][k] = B[i];
	}
	memcpy(chk, mem, sizeof(chk));
	memcpy(s, t, sizeof(s));
	return 0;
}

bool Solve() {
	Init();
	return Find(0);
}

int main() {
	Runs = 0;
	while (Input()) {
		if (Runs) puts("");
		Runs ++;
		bool res = Solve();
		if (!res) puts("NO SOLUTION");
		else for (int i = 0; i < N; i ++) puts(s[i]);
	}
}
