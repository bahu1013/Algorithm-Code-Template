#include<stdio.h>
#include<memory.h>
#include<stdlib.h>
#include<algorithm>
using namespace std;
typedef __int64 ll;
#define P 101
#pragma comment(linker, “/STACK:16777216”)

int num[P];
void Prepare() {
	int i,k;
	for(i=0;i<63;i++) {
		k=((1LL<<i))%P;
		num[k]=i;
	}
}

int calc(ll k) {
	if(!k) return 64;
	k=(k&(-k))%P;
	return num[k];
}

int n;
ll g[1000];
int weights[1000];

int BronKerbosch(ll cur,ll allowed,ll forbidden) {
	if(!allowed && !forbidden) {
		int res=0;
		for(int u=calc(cur);u<n;u+=calc(cur>>(u+1))+1) res+=weights[u];
		return res;
	}
	if(!allowed) return -1;
	int res=-1;
	int pivot=calc(allowed | forbidden);
	ll z=allowed & ~g[pivot];
	for(int u=calc(z);u<n;u+=calc(z>>(u+1))+1) {
		res=max(res,BronKerbosch(cur | (1LL<<u),allowed & g[u],forbidden & g[u]));
		allowed ^=1LL<<u;
		forbidden |=1LL<<u;
	}
    return res;
}

int maxCliqueSlow() {
	int res=0;
	for(int set=0;set<1<<n;set++) {
		bool ok=true;
		for(int i=0;i<n;i++) for(int j=0;j<i;j++) ok &=(set &(1<<i))==0 ||(set &(1<<j))==0 ||(g[i] &(1L<<j)) !=0;
		if(ok) {
			int cur=0;
			for(int i=0;i<n;i++) if((set &(1<<i)) !=0) cur+=weights[i];
			res=max(res,cur);
		}
	}
	return res;
}

int main() {
	int i,j;
	Prepare();
    for(int step=0;step<100;step++) {
		n=10;
		for(i=0;i<n;i++) weights[i]=rand()%1000;
		memset(g,0,sizeof(g));
		for(i=0;i<n;i++) for(j=0;j<i;j++) if(rand()%2) g[i]|=1<<j,g[j]|=1<<i;
      	int res1=BronKerbosch(0,(1LL<<n)-1,0);
      	int res2= maxCliqueSlow();
      	if(res1 !=res2) puts("no");
    }
}
