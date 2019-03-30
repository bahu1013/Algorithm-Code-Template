INT calc(int *c, int st, int en) {
//	a[st, st+1, ... , en-1];
	if (en <= st+1) return 0;
	int mid = (st + en) >> 1;
	INT rlt = calc(c, st, mid) + calc(c, mid, en);
	for (int i = st; i < mid; i ++) left[i - st] = c[i];
	for (int i = mid; i < en; i ++) right[i - mid] = c[i];
	int i = 0, j = 0;
	for (int k = st; k < en; k ++) {
		if (i == mid - st) c[k] = right[j], j ++;
		else if (j == en - mid) c[k] = left[i], i ++, rlt += j;
		else if (left[i] <= right[j]) c[k] = left[i], i ++, rlt += j;
		else c[k] = right[j], j ++;
	}
	return rlt;
}
