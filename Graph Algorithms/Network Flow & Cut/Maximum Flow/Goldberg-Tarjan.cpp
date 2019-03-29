const int MaxV = 311;
const int MaxE = 4111;
const int inf = 1e9;

struct Goldberg_Tarjan {
	int head[MaxV];
	int cap[MaxE], to[MaxE], next[MaxE];
	int ecnt;
	int maxFlow;

	int height[MaxV], C[MaxV];
	int S, T, V;

	void init() {
		memset(head, -1, sizeof(head));
		memset(height, 0, sizeof(height));
		memset(C, 0, sizeof(C));
		ecnt=0;
	}

	void add(int s, int e, int c) {
		cap[ecnt]=c, to[ecnt]=e, next[ecnt]=head[s], head[s]=ecnt++;
		cap[ecnt]=0, to[ecnt]=s, next[ecnt]=head[e], head[e]=ecnt++;
	}

	int ISAP(int x, int y) {
		int mn=V-1, F=0, R=y, t;
		if (x==T) return y;
		for (int i=head[x]; i!=-1; i=next[i]) {
			if (cap[i]>0) {
				if (height[x]==height[to[i]]+1) {
					t=ISAP(to[i], min(cap[i], R));
					cap[i]-=t;
					cap[i^1]+=t;
					R-=t;
					F+=t;
					if (height[S]>=V) return F;
					if (!R) break;
				}
				mn=min(mn, height[to[i]]);
			}
		}
		if (!F) {
			C[height[x]]--;
			if (!C[height[x]]) height[S]=V;
			height[x]=mn+1;
			C[height[x]]++;
		}
		return F;
	}

	void GT(int src, int dst, int cnt) {
		S=src, T=dst, V=cnt;
		C[0]=V;
		maxFlow=0;
		while (height[S]<V) maxFlow+=ISAP(S, inf);
	}
} G;
