inline void add(int k, int v) { for (; k <= n; k += k & -k) tree[k] += v; }

int sum(int k) {
	int rlt = 0;
	for (int i = k; i; i -= i & -i) rlt += tree[i];
	return rlt;
}
