int MinimumCyclicPresentation(char *s, int n){
	int i, j, x, y, u, v;
	for(x=0, y=1; y<n; y++) if(s[y]<=s[x]){
		i=u=x;
		j=v=y;
		while(s[i]==s[j]){
			++u; if(++i==n) i=0;
			++v; if(++j==n) j=0;
			if(i==x) break;
		}
		if(s[i]<=s[j]) y=v;
		else{
			x=y;
			if(u>y) y=u;
		}
	}
	return x;
}
