#include <cstdio>
#include <cmath>

#define N 110

const double ep = 1e-7;
double work[N][N];

bool InvMatrix(int n, double a[N][N], double inv[N][N]) {
	int i, j, k;
	double tp;

	for (i = 0; i < n; i ++)
	for (j = 0; j < n; j ++) {
		work[i][j] = a[i][j];
		inv[i][j] = (i == j);
	}
	for (i = 0; i < n; i ++) {
		if (fabs(work[i][i]) < ep) {
			for (j = i + 1; j < n; j ++) if (fabs(work[j][i]) > ep) break;
			if (j == n) return 0;
			for (k = 0; k < n; k ++) {
				tp = work[j][k], work[j][k] = work[i][k], work[i][k] = tp;
				tp = inv[j][k], inv[j][k] = inv[i][k], inv[i][k] = inv[j][k];
			}
		}

		for (j = 0; j < n; j ++) {
			if (fabs(work[j][i]) < ep || j == i) continue;
			tp = work[j][i] / work[i][i];
			for (int k = 0; k < n; k ++) {
				work[j][k] -= work[i][k] * tp;
				inv[j][k] -= inv[i][k] * tp;
			}
		}

		tp = work[i][i];
		for (j = 0; j < n; j ++) {
			work[i][j] /= tp;
			inv[i][j] /= tp;
		}
	}
	return 1;
}

double A[N][N];
double B[N][N];

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i ++)
	for (int j = 0; j < n; j ++) {
		scanf("%lf", A[i] + j);
	}
	bool ans = InvMatrix(n, A, B);
	if (!ans) puts("No Inverse Matrix.");
	else {
		for (int i = 0; i < n; i ++)
		for (int j = 0; j < n; j ++) {
			printf("%lf%s", B[i][j], j < (n - 1) ? " " : "\n");
		}
	}
}
