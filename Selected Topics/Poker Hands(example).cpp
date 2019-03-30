//CTU Open Contest 2012. Rhinoceros Beetle
#include <stdio.h>
#include <algorithm>
#define N 10

using namespace std;

struct Poker {
	int score;
	int cnt;
	int high[5];
} P[N];

struct Card {
	int rank;
	int suit;
	Card (int rank = 0, int suit = 0): rank(rank), suit(suit) {}
} Com[5], H[N][7];

int n;

bool operator  < (Poker a, Poker b) {
	if (a.score != b.score) return a.score < b.score;
	for (int i = 0; i < a.cnt; i ++) {
		if (a.high[i] != b.high[i]) return a.high[i] < b.high[i];
	}
	return 0;
}

bool operator  == (Poker a, Poker b) {
	if (a < b || b < a) return 0;
	return 1;
}

bool operator  < (Card a, Card b) {
	if (a.rank != b.rank) return a.rank < b.rank;
	return a.suit < b.suit;
}

Card StringToCard(char *s) {
	int R, S;
	if (s[0] >= '2' && s[0] <= '9') R = s[0] - '0';
	else if (s[0] == 'X' || s[0] == 'T') R = 10;
	else if (s[0] == 'J') R = 11;
	else if (s[0] == 'Q') R = 12;
	else if (s[0] == 'K') R = 13;
	else R = 14;
	if (s[1] == 'S' || s[1] == 's') S = 0;
	else if (s[1] == 'C' || s[1] == 'c') S = 1;
	else if (s[1] == 'D' || s[1] == 'd') S = 2;
	else S = 3;
	return Card(R, S);
}

bool Input() {
	int bf = scanf("%d", &n);
	if (bf <= 0) return 0;
	char s[10];
	for (int i = 0; i < 5; i ++) {
		scanf("%s", s);
		Com[i] = StringToCard(s);
	}
	for (int i = 0; i < n; i ++)
		for (int j = 0; j < 2; j ++) {
			scanf("%s", s);
			H[i][j] = StringToCard(s);
		}
	return 1;
}

Poker CALC(Card h[5]) {
	Poker ret;
	sort(h, h + 5);
	int a[5], b[5];
	for (int i = 0; i < 5; i ++) a[i] = h[i].rank, b[i] = h[i].suit;
	bool Flush = 0;
	if (b[0] == b[1] && b[1] == b[2] && b[2] == b[3] && b[3] == b[4]) {
		if (a[4] == a[3] + 1 && a[3] == a[2] + 1 && a[2] == a[1] + 1 && a[1] == a[0] + 1) {
			//Royal Flush
			ret.score = 9;
			ret.cnt = 1;
			ret.high[0] = a[4];
			return ret;
		} else if (a[4] == 14 && a[3] == 5 && a[2] == 4 && a[1] == 3 && a[0] == 2) {
			//Royal Flush
			ret.score = 9;
			ret.cnt = 1;
			ret.high[0] = 5;
			return ret;
		} else {
			//Flush
			Flush = 1;
			ret.score = 6;
			ret.cnt = 5;
			for (int i = 0; i < 5; i ++) ret.high[i] = a[4 - i];
		}
	}
	if (a[0] == a[3] || a[1] == a[4]) {
		//Poker
		ret.score = 8;
		ret.cnt = 2;
		ret.high[0] = a[1];
		if (a[1] == a[4]) ret.high[1] = a[0];
		else ret.high[1] = a[4];
		return ret;
	}
	if (a[0] == a[1] && a[2] == a[4]) {
		//Full House
		ret.score = 7;
		ret.cnt = 2;
		ret.high[0] = a[2];
		ret.high[1] = a[0];
		return ret;
	}
	if (a[0] == a[2] && a[3] == a[4]) {
		//Full House
		ret.score = 7;
		ret.cnt = 2;
		ret.high[0] = a[0];
		ret.high[1] = a[3];
		return ret;
	}
	if (Flush) return ret;
	if (a[4] == a[3] + 1 && a[3] == a[2] + 1 && a[2] == a[1] + 1 && a[1] == a[0] + 1) {
		//Straight
		ret.score = 5;
		ret.cnt = 1;
		ret.high[0] = a[4];
		return ret;
	} else if (a[4] == 14 && a[3] == 5 && a[2] == 4 && a[1] == 3 && a[0] == 2) {
		//Straight
		ret.score = 5;
		ret.cnt = 1;
		ret.high[0] = 5;
		return ret;
	}
	if (a[2] == a[4]) {
		//Three
		ret.score = 4;
		ret.cnt = 3;
		ret.high[0] = a[2];
		ret.high[1] = a[1];
		ret.high[2] = a[0];
		return ret;
	}
	if (a[1] == a[3]) {
		//Three
		ret.score = 4;
		ret.cnt = 3;
		ret.high[0] = a[1];
		ret.high[1] = a[4];
		ret.high[2] = a[0];
		return ret;
	}
	if (a[0] == a[2]) {
		//Three
		ret.score = 4;
		ret.cnt = 3;
		ret.high[0] = a[0];
		ret.high[1] = a[4];
		ret.high[2] = a[3];
		return ret;
	}
	if (a[3] == a[4] && a[1] == a[2]) {
		//Two pairs
		ret.score = 3;
		ret.cnt = 3;
		ret.high[0] = a[3];
		ret.high[1] = a[1];
		ret.high[2] = a[0];
		return ret;
	}
	if (a[3] == a[4] && a[0] == a[1]) {
		//Two pairs
		ret.score = 3;
		ret.cnt = 3;
		ret.high[0] = a[3];
		ret.high[1] = a[0];
		ret.high[2] = a[2];
		return ret;
	}
	if (a[2] == a[3] && a[0] == a[1]) {
		//Two pairs
		ret.score = 3;
		ret.cnt = 3;
		ret.high[0] = a[2];
		ret.high[1] = a[0];
		ret.high[2] = a[4];
		return ret;
	}
	if (a[0] == a[1] || a[1] == a[2] || a[2] == a[3] || a[3] == a[4]) {
		//Two
		ret.score = 2;
		ret.cnt = 4;
		if (a[0] == a[1]) {
			ret.high[0] = a[0];
			ret.high[1] = a[4];
			ret.high[2] = a[3];
			ret.high[3] = a[2];
		} else if (a[1] == a[2]) {
			ret.high[0] = a[1];
			ret.high[1] = a[4];
			ret.high[2] = a[3];
			ret.high[3] = a[0];
		} else if (a[2] == a[3]) {
			ret.high[0] = a[2];
			ret.high[1] = a[4];
			ret.high[2] = a[1];
			ret.high[3] = a[0];
		} else {
			ret.high[0] = a[3];
			ret.high[1] = a[2];
			ret.high[2] = a[1];
			ret.high[3] = a[0];
		}
		return ret;
	}
	//One
	ret.score = 1;
	ret.cnt = 5;
	for (int i = 0; i < 5; i ++) ret.high[i] = a[4 - i];
	return ret;
}

Poker CalcPoker(Card h[7]) {
	Card tp[5];
	int cnt = 0;
	Poker Ret, Temp;
	Ret.score = -1;
	for (int i = 0; i < 7; i ++) for (int j = i + 1; j < 7; j ++) {
		cnt = 0;
		for (int k = 0; k < 7; k ++) if (k != i && k != j) {
			tp[cnt ++] = h[k];
		}
		Temp = CALC(tp);
		if (Ret < Temp) Ret = Temp;
	}
	return Ret;
}

void Run() {
	for (int i = 0; i < n; i ++) {
		for (int j = 2; j < 7; j ++) H[i][j] = Com[j - 2];
		P[i] = CalcPoker(H[i]);
	}
	Poker Max;
	Max.score = -1;
	for (int i = 0; i < n; i ++) {
		if (Max < P[i]) Max = P[i];
	}
	bool bf = 0;
	for (int i = 0; i < n; i ++) if (Max == P[i]) {
		if (bf) putchar(' ');
		printf("%d", i + 1);
		bf = 1;
	}
	puts("");
}

int main() {
	freopen ("in.txt", "r", stdin);
	while (Input()) Run();
}
