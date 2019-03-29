int longest_palindrome(char *text, int n) {
	int rad[2*n], i, j, k;
	for (i=j=0; i<2*n; i+=k, j= max(j-k, 0)) {
		while (i-j>=0 && i+j+1<2*n && text[(i-j)/2]==text[(i+j+1)/2]) ++j;
		rad[i]=j;
		for (k=1; i-k>=0 && rad[i]-k>=0&& rad[i-k]!=rad[i]-k; ++k)
			rad[i+k]=min(rad[i-k], rad[i]-k);
	}
	return *max_element(rad, rad+2*n);
	// ret. centre of the longest palindrome
}
