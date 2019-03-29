#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <memory.h>

#define MAXN 2105
#define INF 100000000

using namespace std;

int cost[MAXN][MAXN];
int n, max_match;
int lx[MAXN], ly[MAXN];
int xy[MAXN];
int yx[MAXN];
bool S[MAXN], T[MAXN];
int slack[MAXN];
int slackx[MAXN];
int prev[MAXN];
int q[MAXN];

void init_labels() {
	memset(lx, 0, sizeof lx);
	memset(ly, 0, sizeof ly);
	for (int x = 0; x < n; x++)
		for (int y = 0; y < n; y++) lx[x] = max(lx[x], cost[x][y]);
}

void update_labels() {
	int x, y, delta = INF;

	for (y = 0; y < n; y++)
		if (!T[y]) delta = min(delta, slack[y]);
	for (x = 0; x < n; x++)
		if (S[x]) lx[x] -= delta;
	for (y = 0; y < n; y++)
		if (T[y]) ly[y] += delta;
		else slack[y] -= delta;
}

void add_to_tree(int x, int prevx) {
	S[x] = true;
	prev[x] = prevx;
	for (int y = 0; y < n; y++)
		if (lx[x] + ly[y] - cost[x][y] < slack[y]) {
			slack[y] = lx[x] + ly[y] - cost[x][y];
			slackx[y] = x;
		}
}

void augment() {
	if (max_match == n) return;
	int x, y, root;
	int wr = 0, rd = 0;

	memset(S, 0, sizeof S);
	memset(T, 0, sizeof T);
	memset(prev, -1, sizeof prev);
	for (x = 0; x < n; x++)
		if (xy[x] == -1) break;
	q[wr++] = root = x;
	prev[x] = -2;
	S[x] = true;
	for (y = 0; y < n; y++) {
		slack[y] = lx[root] + ly[y] - cost[root][y];
		slackx[y] = root;
	}

	while (true) {
		while (rd < wr) {
			x = q[rd++];
			for (y = 0; y < n; y++)
				if (cost[x][y] == lx[x] + ly[y] && !T[y]) {
					if (yx[y] == -1) break;
					T[y] = true;
					q[wr++] = yx[y];
					add_to_tree(yx[y], x);
				}
			if (y < n) break;
		}
		if (y < n) break;
		update_labels();
		wr = rd = 0;
		for (y = 0; y < n; y++)
			if (!T[y] && !slack[y]) {
				if (yx[y] == -1) {
					x = slackx[y];
					break;
				} else {
					T[y] = true;
					if (!S[yx[y]]) {
						q[wr++] = yx[y];
						add_to_tree(yx[y], slackx[y]);
					}
				}
			}
		if (y < n) break;
	}

	if (y < n) {
		max_match++;
		for (int cx = x, cy = y, ty; cx != -2; cx = prev[cx], cy = ty) {
			ty = xy[cx];
			yx[cy] = cx;
			xy[cx] = cy;
		}
		augment();
	}
}

int hungarian() {
	int x, rlt;

	max_match = 0;
	memset(xy, -1, sizeof(xy));
	memset(yx, -1, sizeof(yx));
	init_labels();
	augment();
	for (rlt = x = 0; x < n; x++) rlt += cost[x][xy[x]];
    return rlt;
}

int main() {
	int i,j,k;
	scanf("%d",&n);
	for(i=0;i<n;i++) for(j=0;j<n;j++) scanf("%d",&cost[i][j]);
	printf("%d\n",hungarian());
}
