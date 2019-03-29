#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

vector<int> stable_matching(const vector< vector<int> >& orderM, const vector< vector<int> >& orderW) {
	const int N = orderM.size();
	vector< vector<int> > preferW(N, vector<int>(N+1, N));
	vector<int> matchW(N, N), proposedM(N);
	for (int w = 0; w < N; ++w)
		for (int i = 0; i < N; ++i)
			preferW[w][ orderW[w][i] ] = i;
	for (int m_ = 0; m_ < N; ++m_) {
		for (int m = m_; m < N; ) {
			int w = orderM[m][ proposedM[m]++ ];
			if (preferW[w][ m ] < preferW[w][ matchW[w] ])
			swap(m, matchW[w]);
		}
	}
	return matchW;
}

int main() {
	int n, i, j, k;
	scanf ("%d", &n);
	vector<vector<int> > orderM(n), orderW(n);
	for (i=0; i<n; i++) {
		for (j=0; j<n; j++) {
			scanf ("%d", &k);
			orderM[i].push_back(k);
		}
	}
	for (i=0; i<n; i++) {
		for (j=0; j<n; j++) {
			scanf ("%d", &k);
			orderW[i].push_back(k);
		}
	}
	vector<int> ans=stable_matching(orderM, orderW);
	for (i=0; i<ans.size(); i++) printf ("%d ", ans[i]); puts("");
	return 0;
}
