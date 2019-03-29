#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
#define inf 1000000000

struct edge {
	int src, dst, w;
	edge(int src, int dst, int w):src(src), dst(dst), w(w){}
	edge(){}
};
typedef vector<vector<edge> > graph;

struct cmp{
	bool operator() (edge a, edge b) {
		return a.w>b.w;
	}
};

bool johnson(const graph& g, vector< vector<int> >& dist, vector< vector<int> >& prev) {
	int n = g.size();
	vector<int> h(n+1);
	for (int k = 0; k < n; ++k) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < g[i].size(); ++j) {
				const edge& e = g[i][j];
				if (h[e.dst] > h[e.src] + e.w) {
					h[e.dst] = h[e.src] + e.w;
					if (k == n-1) return false;
				}
			}
		}
	}
	dist.resize(n, vector<int>(n, inf));
	prev.resize(n, vector<int>(n, -1));
	for (int s = 0; s < n; ++s) {
		priority_queue<edge, vector<edge>, cmp> pque;
		pque.push(edge(n, s, 0));
		while (!pque.empty()) {
			edge e = pque.top();
			pque.pop();
			if (dist[s][e.dst] >= inf) {
				dist[s][e.dst] = e.w;
				prev[s][e.dst] = e.src;
				for (int i = 0; i < g[e.dst].size(); ++i) {
					const edge& f = g[e.dst][i];
					if (dist[s][f.dst] >= inf) {
						pque.push(edge(f.src, f.dst, f.w+e.w+h[e.src]-h[f.dst]));
					}
				}
			}
		}
		for (int i = 0; i < n; ++i) {
			dist[s][i] += h[i] - h[s];
		}
	}
	return true;
}

int main() {
	int n, m, i, j, k;
	scanf ("%d %d", &n, &m);
	graph myg(n);
	while (m--) {
		scanf ("%d %d %d", &i, &j, &k);
		myg[i].push_back(edge(i,j,k));
		myg[j].push_back(edge(j,i,k));
	}
	vector<vector<int> > dist, prev;
	johnson(myg, dist, prev);
	for (i=0; i<n; i++) for (j=0; j<n;j++) printf ("%d %d %d\n", i, j, dist[i][j]);
	return 0;
}
