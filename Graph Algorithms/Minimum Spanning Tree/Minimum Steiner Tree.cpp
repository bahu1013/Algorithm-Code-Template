weight minimum_steiner_tree(const vector<int>& T, const matrix &g) {
	const int n = g.size();
	const int numT = T.size();
	if (numT <= 1) return 0;
	matrix d(g);
	for (int k = 0; k < n; ++k)
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
			d[i][j] = min(d[i][j],d[i][k]+d[k][j]);
	weight OPT[(1 << numT)][n];
	for (int S = 0; S < (1 << numT); ++S)
		for (int x = 0; x < n; ++x)
			OPT[S][x] = inf;
	for (int p = 0; p < numT; ++p)
		for (int q = 0; q < n; ++q)
			OPT[1 << p][q] = d[T[p]][q];
	for (int S = 1; S < (1 << numT); ++S){
		if (!(S & (S-1))) continue;
		for (int p = 0; p < n; ++p)
			for (int E = 0; E < S; ++E) if ((E|S) == S)
				OPT[S][p] = min(OPT[S][p], OPT[E][p]+OPT[S-E][p]);
		for (int p = 0; p < n; ++p)
			for (int q = 0; q < n; ++q)
				OPT[S][p] = min(OPT[S][p], OPT[S][q] + d[p][q]);
	}
	weight ans = inf;
	for (int S = 0; S < (1 << numT); ++S)
		for (int q = 0; q < n; ++q)
			ans=min(ans,OPT[S][q]+OPT[((1<<numT)-1)-S][q]);
}
