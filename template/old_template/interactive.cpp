extern "C" int  Seniorious(int);
extern "C" int Chtholly(int n,int c) {
	int l = 1,r = n;
	while(l < r) {
		int mid = (l + r + 1) >> 1;
		if(Seniorious(mid) > 0) r = mid - 1;
		else l = mid;
	}
	return l;
}
