//NEERC 2009 A. Asteroid
//Coded by ASC
#include <stdio.h>
#include <memory.h>
#include <math.h>
#define M 101
#define clr(u) memset(u,0,sizeof(u))
#define GO (xx*xx1+yy*yy1+zz*zz1)
#define INF 1e10
#define min(a,b) ((a<b)?(a):(b))
double x[M], y[M], z[M];
bool tp[M][M][M];
bool chk[3*M][M];
int sto[M];
int n;

double mix_multi(int i, int j, int k, int t){
	double xi=x[i]-x[t], yi=y[i]-y[t], zi=z[i]-z[t];
	double xj=x[j]-x[t], yj=y[j]-y[t], zj=z[j]-z[t];
	double xk=x[k]-x[t], yk=y[k]-y[t], zk=z[k]-z[t];
	return xi*yj*zk+yi*zj*xk+zi*xj*yk-xi*zj*yk-yi*xj*zk-zi*yj*xk;
}

void vec_multi(int i, int j, int k, double &xx, double &yy, double &zz){
	double xi=x[i]-x[k], yi=y[i]-y[k], zi=z[i]-z[k];
	double xj=x[j]-x[k], yj=y[j]-y[k], zj=z[j]-z[k];
	xx=yi*zj-yj*zi, yy=zi*xj-xi*zj, zz=xi*yj-xj*yi;
}


double size_multi(int i, int j, int k){
	double xx, yy, zz;
	vec_multi(i, j, k, xx, yy, zz);
	return hypot(xx, hypot(yy, zz));
}

double dis(int i, int j){
	return hypot(x[i]-x[j], hypot(y[i]-y[j], z[i]-z[j]));
}

bool ontop(int i, int j, int k){
	int np=0, nm=0,t;
	for(t=0; t<n; t++){
		if(mix_multi(i, j, k, t)>0) np++;
		if(mix_multi(i, j, k, t)<0) nm++;
		if(np && nm) break;
	}
	if (t==n) return 1;
	return 0;
}

void doit(double &d){
	int i, j, k, t, ns=0, h, l, nxt;
	double cx=0, cy=0, cz=0, xx, yy, zz, xx1, yy1, zz1, v=0, vv;
	scanf("%d", &n);
	for(i=0; i<n; i++) scanf("%lf %lf %lf", x+i, y+i, z+i);
	clr(tp);
	clr(chk);
	for(i=0; i<n; i++) for(j=i+1; j<n; j++){
		for(k=j+1; k<n; k++){
			if(ontop(i, j, k)) tp[i][j][k]=1;
		}
	}
	for(i=0; i<n; i++) for(j=i+1; j<n; j++) for(k=j+1; k<n; k++){
		if(!ontop(i, j, k)) continue;
		for(t=0; t<ns; t++) if(chk[t][i] && chk[t][j] && chk[t][k]) break;
		if(t<ns) continue;
		vec_multi(i, j, k, xx, yy, zz);
		int nsto=0;
		for(t=0; t<n; t++){
			if(mix_multi(i, j, k, t)==0){
				chk[ns][t]=1;
				sto[nsto++]=t;
			}
		}
		for(t=0;;t=nxt){
			nxt=-1;
			for(h=0; h<nsto; h++){
				if(h==t) continue;
				for(l=0; l<nsto; l++){
					vec_multi(sto[h], sto[l], sto[t], xx1, yy1, zz1);
					if(GO<0) break;
				}
				if(l==nsto){
					if(nxt == -1 || dis(sto[t], sto[nxt])>dis(sto[t], sto[h])) nxt=h;
				}
			}
			v+=(vv=fabs(mix_multi(0, sto[0], sto[t], sto[nxt])));
			cx+=(x[0]+x[sto[0]]+x[sto[t]]+x[sto[nxt]])/4*vv;
			cy+=(y[0]+y[sto[0]]+y[sto[t]]+y[sto[nxt]])/4*vv;
			cz+=(z[0]+z[sto[0]]+z[sto[t]]+z[sto[nxt]])/4*vv;
			if(nxt==0) break;
		}
		ns++;
	}
	cx/=v;
	cy/=v;
	cz/=v;
	x[n]=cx;
	y[n]=cy;
	z[n]=cz;
	d=INF;
	for(i=0; i<n; i++) for(j=0; j<n; j++) for(k=0; k<n; k++){
		if(!tp[i][j][k]) continue;
		double ss=size_multi(i, j, k);
		d=min(d, fabs(mix_multi(n, i, j, k))/ss);
	}
}

int main(){
	double d1, d2;
	doit(d1);
	doit(d2);
	printf("%.5lf\n", d1+d2);
	return 0;
}
