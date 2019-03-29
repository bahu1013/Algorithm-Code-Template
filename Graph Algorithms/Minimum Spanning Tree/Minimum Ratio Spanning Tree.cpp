/*

	Definition of MRST:

		In G(V , E) , each e of E has two value C(e) , K(e)
		Let T is Spanning Tree of G(V , E)
		if sum(C(e)) / sum(K(e)) over edges in T is minimal , T is MRST
	
	Algorithm:
		
		rational r = 0;
		do {
			set weight of each edge to c_ij - r * k_ij;
			find MST;
			r = sum(c_ij) / sum(k_ij) over edges in the mst found;
		} while (cost of MST found != 0);
		print r;
		
	Problem:
		Bitwise2009-6
*/

#include <iostream>

#define MX 1005
#define FOUND 1
#define INF 1e10
#define EPS 1e-6
using namespace std;

int n , pn;
int con[MX][MX];
double w[MX][MX];
double C[MX][MX] , K[MX][MX];
pair<int , int> Path[MX];

void Build(double r){
	
	int i , k;
	for(i = 0 ; i < n ; i ++)
		for(k = 0 ; k < n ; k ++){
			if(con[i][k]) w[i][k] = max(0.0 , C[i][k] - r * K[i][k]); 
			else w[i][k] = 0.0;
		}
}

double Update(){
	
	int i , u , v;
	double c = 0.0 , k = 0.0;
	
	for(i = 0 ; i < n ; i ++){
		u = Path[i].first , v = Path[i].second;
		c += C[u][v] , k += K[u][v];	
	}
	return c / k;
}

int MST(){
	
	int i , k , id;
	double mx;
	
	int chk[MX] , prev[MX];
	double val[MX];
	
	for(pn = i = 0 ; i < n ; i ++)
		chk[i] = prev[i] = 0 , val[i] = INF;
	val[0] = 0.0;
	
	
	while(1){
		
		id = -1 , mx = INF;
		for(i = 0 ; i < n ; i ++) if(!chk[i]){
			if(mx > val[i] + EPS) mx = val[i] , id = i;	
		}
		if(id == -1) break;
		chk[id] = 1;
		if(id) Path[pn ++] = make_pair(prev[id] , id);
		
		for(i = 0 ; i < n ; i ++) if(!chk[i]){
			if(!con[id][i]) continue;
			if(w[id][i] < EPS) break;
			if(w[id][i] < val[i] + EPS){
				val[i] = w[id][i] , prev[i] = id;	
			}	
		}
	}
	if(pn == n - 1) return FOUND;
	else return !FOUND;
}

void Get_MRST(){
	
	double r = 0.0;

	while(1){
		Build(r);
		if(!MST()) break;
		r = Update();	
	}
	cout << r << endl;
}

int main(){
	
	int i , k;
	while(cin >> n && n){
		
		for(i = 0 ; i < n ; i ++)
			for(k = 0 ; k < n ; k ++) scanf("%d" , con[i] + k);
		for(i = 0 ; i < n ; i ++)
			for(k = 0 ; k < n ; k ++) scanf("%lf" , C[i] + k);
		for(i = 0 ; i < n ; i ++)
			for(k = 0 ; k < n ; k ++) scanf("%lf" , K[i] + k);
		
		Get_MRST();
	}
	return 0;
}
