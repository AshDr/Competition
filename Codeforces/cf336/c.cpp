#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
pair<int,int> a[N];//pos,val
int f[N],b[N];
int n;
int main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin>>n;
	for(int i = 1; i <= n; i++) cin>>a[i].first>>a[i].second,b[i] = a[i].first;
	sort(a + 1,a + 1 + n);
	sort(b + 1,b + 1 + n);
	f[1] = 0;
	int res = n - 1;
	for(int i = 2; i <= n; i++) {
		int pos = a[i].first,val = a[i].second;
		if(val >= pos) f[i] = i - 1;
		else {
			int t = lower_bound(b + 1,b + 1 + n,pos - val) - b;
			f[i] = f[t - 1] + i - t;
		}
		//cout<<f[i]<<endl;
		res = min(res,f[i] + n - i);
	}
	cout<<res<<endl;
	return 0;	
}