//Fast FFT
struct node
{
	double x, y;
	node(double _x = 0.0, double _y = 0.0)
	{
		x = _x;
		y = _y;
	}
	node operator+(node a)
	{
		return node(x + a.x, y + a.y);
	}
	node operator-(node a)
	{
		return node(x - a.x, y - a.y);
	}
	node operator*(node a)
	{
		return node(x * a.x - y * a.y, x * a.y + y * a.x);
	}
};

node A[N];
int L;

int reverse(int x)
{
	int ans = 0, i;
	FOR0(i, L) if(x & (1 << i)) ans |= 1 << (L - 1 - i);
	return ans;
}

void bitReverseCopy(node a[], int n)
{
	int i;
	FOR0(i, n) A[i] = a[i];
	FOR0(i, n)
	{
		a[reverse(i)]=A[i];
	}
}

void fft(node a[], int n, int on)
{
	bitReverseCopy(a, n);
	int len, i, j, k;
	node x, y, u, t;
	for(len = 2; len <= n; len <<= 1)
	{
		x = node(cos(-on * 2 * pi / len), sin(-on * 2 * pi / len));
		for(j = 0; j < n; j += len)
		{
			y = node(1, 0);
			for(k = j; k < j + len / 2; k ++)
			{
				u = a[k];
				t = y * a[k + len / 2];
				a[k] = u + t;
				a[k + len / 2] = u - t;
				y = y * x;
			}
		}
	}
	if(on == -1)
	{
		FOR0(i, n) a[i].x /= n;
	}
}

node P[N], Q[N];
int M;

void init()
{
	L = 5;
	M = 1 << L;
	printf("M = %d\n", M);
	for(int i = 0; i < M; i ++) P[i] = Q[i] = node(0, 0);
	for(int i = 0; i < 10; i ++) P[i] = node(1, 0);
	for(int i = 0; i < 10; i ++) Q[i] = node(1, 0);
	fft(P, M, 1);
	fft(Q, M, 1);
	for(int i = 0; i < M; i ++) P[i] = P[i] * Q[i];
	fft(P, M, -1);
	for(int i = 0; i < 20; i ++) printf("%.lf\n", P[i].x + 0.4);
}


//Simple FFT
int n2 = (1 << T)
typedef complex <double> cp;
cp a[M], b[M];
void fft(int n, double t, cp *a){
    int m, h, i, j, k;
    cp w, x;
    for(m = n, h; h = m / 2, m >= 2; t *= 2, m = h)
        for(i = 0; i < h; i ++)
            for(w = exp(i * t * I), j = i; j < n; j += m)
                k = j + h , x = a[j] - a[k], a[j] += a[k], a[k] = w * x;
    i = 0;
    for(j = 1; j < n - 1; j ++)
    {
        for(k = n / 2; k > (i ^= k); k /= 2);
        if(j < i) swap(a[i], a[j]);
    }
}
fft(n2, 2 * M_PI / n2, a);
fft(n2, -2 * M_PI/ n2, b);
