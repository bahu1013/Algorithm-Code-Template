#include <cstdio>
#include <vector>
#include <memory.h>

#define N 150100
#define max(a, b) ((a) > (b) ? (a) : (b))

using namespace std;

int n, m, p;
int head[N], to[N], next[N], from[N];

bool vis[N];
bool OnCycle[N];
int pE[N];

typedef int Edge;
typedef vector <Edge> Rings;

Rings Ring[N];
int RingCnt;
int RingID[N];
int ans;

int dist[N];

void Init() {
	ans = 0;
	m = RingCnt = 0;
	for (int i = 1; i <= n; i ++) head[i] = 0;
	for (int i = 1; i <= n; i ++) pE[i] = 0;
	for (int i = 1; i <= n; i ++) vis[i] = 0;
	for (int i = 1; i <= n; i ++) dist[i] = -1;
}

void AddEdge(int s, int e, int u) {
	OnCycle[u] = 0;
	from[u] = s;
	to[u] = e;
	next[u] = head[s];
	head[s] = u;
}

inline int Abs(Edge E) { return (((E + 1) >> 1) << 1) - 1; }
inline Edge RevE(Edge E) { return ((E - 1) ^ 1) + 1; }

void Insert(Edge E) {
	int e = Abs(E);
	OnCycle[e] = 1;
	RingID[e] = RingCnt;
	Ring[RingCnt].push_back(E);
}

void CactusFind(int cur) {
	vis[cur] = 1;
	for (int i = head[cur]; i; i = next[i]) {
		int pos = to[i];
		if (!vis[pos]) {
			pE[pos] = i;
			CactusFind(pos);
		} else if (i != RevE(pE[cur]) && !OnCycle[Abs(i)]) {
			RingCnt ++;
			Ring[RingCnt].clear();
			Insert(i);
			int o = cur;
			while (1) {
				int p = pE[o];
				Insert(p);
				o = to[RevE(p)];
				if (o == pos) break;
			}
		}
	}
}

int Stack[N], top;
int loc[N];

void CactusFindNoRecursive(int cur) {
	for (int i = 1; i <= n; i ++) loc[i] = head[i];
	top = 0;
	Stack[++ top] = cur;
	while (top) {
		cur = Stack[top];
		vis[cur] = 1;
		for (int i = loc[cur]; i; i = next[i]) {
			int pos = to[i];
			if (!vis[pos]) {
				pE[pos] = i;
				Stack[++ top] = pos;
				loc[cur] = next[i];
				goto Label;
			} else if (i != RevE(pE[cur]) && !OnCycle[Abs(i)]) {
				RingCnt ++;
				Ring[RingCnt].clear();
				Insert(i);
				int o = cur;
				while (1) {
					int p = pE[o];
					Insert(p);
					o = to[RevE(p)];
					if (o == pos) break;
				}
			}
		}
		top --;
	Label:;
	}
}

int CalcOnRing(int RN, int cur);

int CalcLongDist(int cur) {
	int M1 = 0, M2 = 0, tp;
	if (dist[cur] >= 0) return dist[cur];
	for (int i = head[cur]; i; i = next[i]) {
		int pos = to[i];
		if (vis[Abs(i)]) continue;
		vis[Abs(i)] = 1;
		if (!OnCycle[Abs(i)]) tp = CalcLongDist(pos) + 1;
		else tp = CalcOnRing(RingID[Abs(i)], cur);
		if (M1 < tp) M2 = M1, M1 = tp;
		else if (M2 < tp) M2 = tp;
	}
	ans = max(ans, M1 + M2);
	return dist[cur] = M1;
}

int CalcOnRing(int RN, int cur) {
	int pos, ret = 0;
	int cnt = Ring[RN].size();
	int sz = cnt / 2, b;
	vector <int> arr, tp;
	for (int i = 0; i < cnt; i ++) {
		int e = Ring[RN][i];
		if (from[e] == cur) pos = i;
		vis[Abs(e)] = 1;
	}
	arr.clear();
	arr.resize(cnt);
	for (int i = 1; i < cnt; i ++) {
		arr[i] = CalcLongDist(from[Ring[RN][(i + pos) % cnt]]);
		ret = max(ret, arr[i] + ((i <= sz) ? i : (cnt - i)));
	}
	tp.clear();
	tp.resize(cnt << 1);
	for (int i = 1; i <= cnt + sz; i ++) tp[i] = arr[i % cnt] + i;
	for (b = 0; (1 << b) < sz / 2; b ++);
	for (int i = 1; i <= b; i ++) {
		int k = (1 << i);
		for (int j = 0; j <= cnt + sz - k; j ++) tp[j] = max(tp[j], tp[j + k / 2]);
	}
	for (int i = 0; i < cnt; i ++) ans = max(ans, arr[i] - i + max(tp[i + 1], tp[i + 1 + sz - (1 << b)]));
	return ret;
}

int main() {
	while (scanf("%d %d", &n, &p) > 0) {
		Init();
		while (p --) {
			int c, a, b;
			scanf("%d %d", &c, &a);
			for (c --; c --; ) {
				scanf("%d", &b);
				AddEdge(a, b, ++ m);
				AddEdge(b, a, ++ m);
				a = b;
			}
		}
		CactusFindNoRecursive(1);
		memset(vis, 0, sizeof(bool) * (m + 1));
		CalcLongDist(1);
		printf("%d\n", ans);
	}
}
