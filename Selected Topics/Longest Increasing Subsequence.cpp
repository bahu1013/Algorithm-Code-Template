cin >> n;
for (i = 0; i < n; i ++) cin >> a[i];
for (m = i = 0; i < n; i ++) {
	j = lower_bound(g, g + m, a[i]) - g;
	m += (j == m);	//LIS in a[0]~a[i]
	g[j] = a[i];
}
cout << m <<endl;
