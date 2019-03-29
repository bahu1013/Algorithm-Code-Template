void DFT(int rt) {
	for (int i = 1; i <= n; i ++) cur[i] = head[i];
	arr[cnt = 1] = rt;
	for (int x = rt, v, i; x; ) {
		i = cur[x], cur[x] = next[i];
		if (!i) arr[++ cnt] = x + n, x = p[x];			//finish time
		else p[v = to[i]] = x, arr[++ cnt] = x = v;		//discover time
	}
}
