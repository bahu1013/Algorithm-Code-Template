int Partition(int st, int en) {			//a[st, st+1, … , en-1]
	int x = a[en - 1], i = st - 1;
	for (int j = st; j < en - 1; j ++) {
		if (a[j] > x) continue;
		i ++;
		swap(a[j], a[i]);
	}
	swap(a[i + 1], a[en - 1]);
	return i + 1;
}

void Quicksort(int st, int en) {
	int mid;
	if (en - st > 1) {
		mid = Partition(st, en);
		Quicksort(st, mid);
		Quicksort(mid + 1, en);
	}
}
