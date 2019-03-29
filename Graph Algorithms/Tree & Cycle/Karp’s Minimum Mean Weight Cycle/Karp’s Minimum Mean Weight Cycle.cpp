const int N=700;
const int inf=1000000000;

struct edge {
	int v, dis;
};

vector <edge> edge[N];
int dist[N][N+2];

double minimum_mean_cycle(int n) {
	int i, j, k, jj;
	double t, res;

	for (i=0; i<n; i++) dist[i][0]=0;

	for (k=1; k<=n+1; k++)
		for (i=0; i<n; i++)
			for (j=0, dist[i][k]=inf; j<edge[i].size(); j++)
				if (dist[edge[i][j].v][k-1]!=inf)
					dist[i][k]=min(dist[i][k], dist[edge[i][j].v][k-1]+edge[i][j].dis);

	for (i=0, res=inf; i<n; i++) {
		if (dist[i][n+1]==inf) continue;
		for (k=0, t=-inf; k<=n; k++)
			if (dist[i][k]!=inf)
				t=max(t, (double)(dist[i][n+1]-dist[i][k])/(n+1-k));
		res=min(res, t);
	}

	return res;
}
