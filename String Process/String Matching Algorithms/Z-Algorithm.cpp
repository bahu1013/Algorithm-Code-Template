#include <cstdio>
#include <cstring>

#define M 100100
#define max(a, b) ((a) > (b) ? (a) : (b))

int z[M];

void doZ(int L, char *s, int *z) {
/* every i: 	z[i] = max(s[0...z[i]-1] = s[i...i+z[i]-1]);
				r = max(j+z[j]-1) | 1<=j<=i	:: r++
				l = min(r) | s[0...r-l] = s[l...r](l>=1);*/

	int r=1, l=1;
	for(; r<L and s[r]==s[r-1]; r++);
	z[1]=r-1;
	for(int i=2; i<L; i++){
		if(r>i and z[i-l]<r-i){
			z[i]=z[i-l];
		}else{
			l=i;
			///if(r<i)r++;
			r=max(r,i);
			for(; r<L and s[r]==s[r-i]; r++);
			z[i]=r-i;
		}
	}
}


char s[M], t[M];

int main() {
	scanf("%s %s", s, t);
	strcat(s, "&");
	strcat(s, t);
	int L = strlen(s);
	doZ(L, s, z);
}
