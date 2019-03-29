const int U = 20;
const int MOD = 100003; // definited mod value
const int NN = (1 << U)+1; // range
int N1 = (1 << U);//limit
const int P1 = 998244353; //P1 = 2^{23}*7*17 + 1
const int P2 = 897581057; //P2 = 2^{23}*107 + 1
const lll M1 = 522669703646500173LL;
const lll M2 = 373335517863520949LL;
const lll MM = 896005221510021121LL; //MM = P1*P2
int I1 = 998244234; // I1*N1 = 1(mod P1)
int I2 = 897580950; // I2*N1 = 1(mod P2)
int E1 = 15311432;
int E2 = 872686320;
int F1 = 469870224; // E1*F1 = 1(mod P1)
int F2 = 354917575; // E2*F2 = 1(mod P2)

lll POW(lll x, int k, lll mod){
	lll s = 1, pw = x;
	while(k) {
		if(k & 1) s = s * pw % mod;
		pw = pw * pw % mod;
		k /= 2;
	}
	return s;
}

void format(int r){
	///MM=(lll)P1*P2;
	///M1=POW(P2, P1-2, P1)*P2;
	///M2=POW(P1, P2-2, P2)*P1;
	///printf("%I64d %I64d %I64d\n", MM, M1, M2);
	N1 = (1 << r);
	{
		I1 = P1 - (P1 / N1);
		E1 = POW(3, P1 / N1, P1);
		F1 = POW(E1, P1 - 2, P1);
	}
	{
		I2 = P2 - (P2 / N1);
		E2 = POW(3, P2 / N1, P2);
		F2 = POW(E2, P2 - 2, P2);
	}
	///printf("%d %d %d\n", I1, E1, F1);
	///printf("%d %d %d\n", I2, E2, F2);
}
/// x*y%z
lll mul(lll x, lll y, lll z){
	return (x * y - (lll)(x / (long double)z * y + 1e-3) * z + z) % z;
}

int trf(int x1, int x2){
	return (mul(M1, x1, MM) + mul(M2, x2, MM)) % MM % MOD;
}

int A[NN], B[NN], C[NN];
int A1[NN], B1[NN], C1[NN];

void fft(int *A, int PM, int PW) {
	for(int m = N1, h; h = m / 2, m >= 2; PW = (lll)PW * PW % PM, m = h)
		for(int i = 0, w = 1; i < h; i ++, w = (lll)w * PW % PM)
			for(int j = i; j < N1; j += m){
				int k = j + h, x = (A[j] - A[k] + PM) % PM;
				(A[j] += A[k]) %= PM;
				A[k] = (lll)w * x % PM;
			}
	for(int i = 0, j = 1; j < N1 - 1; j ++){
		for(int k = N1 / 2; k > (i ^= k); k /= 2);
		if(j < i)swap(A[i], A[j]);
	}
}

void multi() {
	memset(C, 0, sizeof(C));
	memcpy(A1, A, sizeof(A));
	memcpy(B1, B, sizeof(B));
	fft(A1, P1, E1);
	fft(B1, P1, E1);
	for(int i = 0; i < N1; i ++) C1[i] = (lll)A1[i] * B1[i] % P1;
	fft(C1, P1, F1);
	for(int i = 0; i < N1; i ++) C1[i] = (lll)C1[i] *I1 % P1;
	fft(A, P2, E2);
	fft(B, P2, E2);
	for(int i = 0; i < N1; i ++) C[i] = (lll)A[i] * B[i] % P2;
	fft(C, P2, F2);
	for(int i = 0; i < N1; i++) C[i] = (lll)C[i] * I2 % P2;
	for(int i = 0; i < N1; i++) C[i] = trf(C1[i], C[i]); 
}

int main() {
	memset(A, 0, sizeof(A));
	memset(B, 0, sizeof(B));
	for(int i = 0; i < 10; i ++) A[i]=1;
	for(int j = 0; j < 10; j ++)B[j] = 1;
	format(18);
	multi();
	for(int i = 0; i < 20; i ++) printf("%d\n", C[i]);
    return 0;
}
