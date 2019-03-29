/// Real Value Determinant
#include <cstdio>
#include <cmath>

#define N 110

const double ep = 1e-7;
double work[N][N];

double Determinant(int n, double a[N][N]) {
	int i, j;
	double ret = 1, tp;
	for (i = 0; i < n; i ++)
	for (j = 0; j < n; j ++) {
		work[i][j] = a[i][j];
	}

	for (i = 0; i < n; i ++) {
		if (fabs(work[i][i]) < ep) {
			for (j = i + 1; j < n; j ++) if (fabs(work[j][i]) > ep) break;
			if (j == n) return 0;
			for (int k = i; k < n; k ++) {
				tp = work[j][k], work[j][k] = work[i][k], work[i][k] = tp;
			}
			ret = -ret;
		}

		ret *= work[i][i];
		for (j = 0; j < n; j ++) {
			if (fabs(work[j][i]) < ep || j == i) continue;
			tp = work[j][i] / work[i][i];
			for (int k = i; k < n; k ++) {
				work[j][k] -= work[i][k] * tp;
			}
		}
	}
	return ret;
}

double A[N][N];

int main() {
	int n;
	freopen ("Matrix.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i < n; i ++)
	for (int j = 0; j < n; j ++) {
		scanf("%lf", A[i] + j);
	}
	printf("%lf\n", Determinant(n, A));
}


/// Long Long Value Determinant in Zp or Z
#include <cstdio>
#include <cmath>
#include <algorithm>

#define N 110

using namespace std;

typedef __int64 INT;

INT P;
INT work[N][N];

INT DeterminantZp(int n, INT a[N][N]) {
	INT ret = 1, tp;
	for (int i = 0; i < n; i ++)
	for (int j = 0; j < n; j ++) {
		work[i][j] = a[i][j] % P;
	}

	for (int i = 0; i < n; i ++) {
		for (int j = i + 1; j < n; j ++) {
			while (work[j][i]) {
				tp = work[i][i] / work[j][i];
				for (int k = i; k < n; k ++) {
					work[i][k] = (work[i][k] - work[j][k] * tp) % P;
				}
				for (int k = i; k < n; k ++) swap(work[i][k], work[j][k]);
				ret = -ret;
			}
		}
		if (!work[i][i]) return 0;
		ret = ret * work[i][i] % P;
	}
	if (ret < 0) ret += P;
	return ret;
}

INT A[N][N];

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i ++)
	for (int j = 0; j < n; j ++) {
		scanf("%I64d", A[i] + j);
	}
	scanf("%I64d\n", &P);
	printf("%I64d\n", DeterminantZp(n, A));
}
