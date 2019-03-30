//Standard
char *st1 = "23456789TJQKA", *st2 = "CDHS";
int mm[5][2];
int cnt[13], cc[5];
int sto[5];

int calc(){
	int i, j;
	int fla = 0, strai = 0;
	int mx = 0, mn = 13;

	for (i = 0; i < 13; i++) cnt[i] = 0;
	for (i = 0; i < 5; i++) cc[i] = 0;

	for (i = 0; i < 5; i++){
		cnt[mm[i][0]]++;
		if (mm[i][0] > mx) mx = mm[i][0];
		if (mm[i][0] < mn) mn = mm[i][0];
	}
	for (i = 0; i < 13; i++) cc[cnt[i]]++;
	for (i = 0; i < 4; i++) if (mm[i][1] != mm[i + 1][1]) break;
	if (i == 4) fla = 1;

	if (cc[1] == 5){
		if (mx - mn == 4) strai = 1;
		else if (mx == 12 && mn == 0){
			if (cnt[1] && cnt[2] && cnt[3]) strai = 2;
		}
	}
	if (fla && strai){
		if (strai == 1) sto[0] = mx;
		else sto[0] = 3;
		return 8;
	}
	if (cc[4]){
		for (i = 0; i < 13; i++)
			if (cnt[i] == 4) sto[0] = i;
			else if (cnt[i] == 1) sto[1] = i;
		return 7;
	}
	if (cc[3] && cc[2]){
		for (i = 0; i < 13; i++)
			if (cnt[i] == 3) sto[0] = i;
			else if (cnt[i] == 2) sto[1] = i;
		return 6;
	}
	if (fla){
		for (i = 0; i < 5; i++) sto[i] = mm[i][0];
		sort(sto, sto + 5, cmp);
		return 5;
	}
	if (strai){
		if (strai == 1) sto[0] = mx;
		else sto[0] = 3;
		return 4;
	}
	if (cc[3]){
		j = 1;
		for (i = 0; i < 13; i++)
			if (cnt[i] == 3) sto[0] = i;
			else if (cnt[i] == 1) sto[j++] = i;
		sort(sto + 1, sto + 3, cmp);
		return 3;
	}
	if (cc[2] == 2){
		j = 0;
		for (i = 0; i < 13; i++)
			if (cnt[i] == 2) sto[j++] = i;
			else if (cnt[i] == 1) sto[2] = i;
		sort(sto, sto + 2, cmp);
		return 2;
	}
	if (cc[2]){
		j = 1;
		for (i = 0; i < 13; i++)
			if (cnt[i] == 2) sto[0] = i;
			else if (cnt[i] == 1) sto[j++] = i;

		sort(sto + 1, sto + 4, cmp);
		return 1;
	}
	for (i = 0; i < 5; i++) sto[i] = mm[i][0];
	sort(sto, sto + 5, cmp);
	return 0;
}
