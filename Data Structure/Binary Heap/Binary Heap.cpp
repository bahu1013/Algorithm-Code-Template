#include <cstdio>
#include <algorithm>
using namespace std;
#define N 100100

struct MinHeap {
	int Heap[N], HeapSize;	//Heap
	int H[N];	//H[HeapIndex]=ArrayIndex;
	int P[N];	//P[ArrayIndex]=HeapIndex;

	inline void Clear() { HeapSize = 0; }
	inline bool Empty() { return HeapSize == 0; }

	inline void BuildHeap(int *a, int n) {
		HeapSize = n;
		for (int i = 1; i <= n; i ++) Heap[i] = a[i], H[i] = P[i] = i;
		for (int i = HeapSize; i; i --) HeapDown(i);
	}

	void Swap(int i, int j) {
		swap(Heap[i], Heap[j]);
		swap(H[i], H[j]);
		P[H[i]] = i;
		P[H[j]] = j;
	}

	inline void HeapUp(int p) {
		while (p > 1 && Heap[p >> 1] > Heap[p]) Swap(p, p >> 1), p >>= 1;
	}

	void HeapDown(int p) {
		int q;
		while ((p << 1) <= HeapSize) {
			q = p << 1;
			if (q < HeapSize && Heap[q] > Heap[q + 1]) q ++;
			if (Heap[p] > Heap[q]) Swap(p, q), p = q;
			else return;
		}
	}

	void HeapInsert(int x, int v) {	//Insert v = Array[x] to Heap...
		Heap[++ HeapSize] = v;
		H[HeapSize] = x;
		P[x] = HeapSize;
		HeapUp(HeapSize);
	}

	int ExtractMin() {
		int ret = H[1];
		Swap(1, HeapSize), HeapSize --;
		HeapDown(1);
		return ret;	//Array[ret] is minimum...
	}

	void HeapDelete(int x) {	//Delete Array[x] from Heap...
		int y = P[x];
		Swap(y, HeapSize), HeapSize --;
		HeapDown(y);
	}

	void HeapSetVal(int x, int key) {	//Array[x]<-key...
		int pos = P[x];
		if (Heap[pos] == key) return;
		bool bf = Heap[pos] < key;
		Heap[pos] = key;
		if (bf) HeapDown(pos);
		else HeapUp(pos);
	}

	void Print() {
		for (int i = 1; i <= HeapSize; i ++) {
			printf("Heap[%d] = %d, H[%d] = %d, P[%d] = %d\n", i, Heap[i], i, H[i], i, P[i]);
		}
		puts("");
	}
} HP;

int a[N];

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++) scanf("%d", a + i);
	HP.Clear();
	HP.BuildHeap(a, n);
}
