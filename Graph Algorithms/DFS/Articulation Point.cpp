int artic(int u) {
	int mn, m;
	bool art = false;
	mn = sign[u] = ++ Time;
	for (int i = 0; i < con[u].size(); i ++) {
		int v = con[u][i];
		if (!sign[v]) {
			m = artic(v);
			if (m < mn) mn = m;
			if ((sign[u] == 1 && i) ||  (sign[u] > 1 && m == sign[u])) art=true;
		} else mn = min(mn, sign[v]);
	}
	if (art) {
		//u is artic point
		Artic[u] = 1;
		cnt ++;
	}
	return mn;
}
