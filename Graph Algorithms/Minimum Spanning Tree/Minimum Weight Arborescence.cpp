#include <stdio.h>
#include <vector>
using namespace std;
#define inf 1000000000

struct edge {
	int src, dst, w;
	edge(int src, int dst, int w):src(src), dst(dst), w(w){}
	edge(){}
};
typedef vector<vector<edge> > graph;

void Visit(int v, int s, int r, graph &gg, vector<int> &no, vector<vector<int> > &comp, vector<int> &prev, vector< vector<int> > next, vector<int> &mcost, vector<int> &mark, int &cost, bool &found) {
	const int n=gg.size();
	if (mark[v]) {
		vector<int> temp=no;
		found=true;
		do{
			cost+=mcost[v];
			v=prev[v];
			if(v != s) {
				while (comp[v].size()>0) {
					no[comp[v].back()]=s;
					comp[s].push_back(comp[v].back());
					comp[v].pop_back();
				}
			}
		} while (v != s);
		for (int k=0; k<comp[s].size(); k++) {
			int j=comp[s][k];
			if (j!=r) for (int l=0; l<gg[j].size(); l++) if (no[gg[j][l].src]!=s) gg[j][l].w-=mcost[temp[j]];
		}
	}
	mark[v]=true;
	for (int k=0; k<next[v].size(); k++) {
		int i=next[v][k];
		if (no[i] != no[v] && prev[no[i]]==v)
			if(!mark[no[i]] || i==s)
				Visit(i,s,r,gg,no,comp,prev,next,mcost,mark,cost,found);
	}
}

int MWA(int r, graph &g) {
	const int n=g.size();
	graph gg(n);
	for (int i=0; i<g.size(); i++)
		for (int j=0; j<g[i].size(); j++)
			gg[g[i][j].dst].push_back(g[i][j]);
	vector<int> no(n);
	vector<vector<int> > comp(n);
	for (int i=0; i<n; i++) {
		no[i]=i;
		comp[i].push_back(i);
	}
	int cost=0;
	while (1) {
		vector<int> prev(n,-1);
		vector<int> mcost(n,inf);
		for (int j=0; j<n; j++) {
			if (j==r) continue;
			for (int k=0; k<gg[j].size(); k++) {
				int i=gg[j][k].src;
				if (no[i] != no[j]) {
					if (gg[j][k].w < mcost[no[j]]) {
						mcost[no[j]]=gg[j][k].w;
						prev[no[j]]=no[i];
					}
				}
			}
		}
		vector<vector<int> > next(n);
		for (int i=0; i<n; i++)
			if(prev[i]>=0) next[prev[i]].push_back(i);
		bool stop=true;
		vector<int> mark(n);
		for (int i=0; i<n; i++) {
			if(i==r || mark[i] || comp[i].size()==0) continue;
			bool found=false;
			Visit(i,i,r,gg,no,comp,prev,next,mcost,mark,cost,found);
			if (found) stop=false;
		}
		if (stop) {
			for (int i=0; i<n; i++)
				if(prev[i]>=0) cost += mcost[i];
			return cost;
		}
	}
}

int main() {
	int n, i, j, k, m;
	scanf("%d %d", &n, &m);
	graph G(n);
	while (m--) {
		scanf ("%d %d %d", &i, &j, &k);
		i --, j --;
		G[i].push_back(edge(i, j, k));
	}
	int ans=MWA(0,G);
	printf ("%d\n", ans);
	return 0;
}
