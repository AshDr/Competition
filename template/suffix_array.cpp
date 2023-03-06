// SA
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
int n,m;
char s[N];
int c[N],x[N],y[N],sa[N],rk[N];//基数排序用的桶 第一关键字 第二关键字 排名为i的后缀是哪个 第i个后缀的排名
int height[N];//表示排名为i与排名为i - 1的lcp长度
void get_sa() {
	for(int i = 1; i <= n; i++) c[x[i] = s[i]]++;
	for(int i = 2; i <= m; i++) c[i] += c[i - 1];
	for(int i = n;i;i--) sa[c[x[i]]--] = i;
	for(int k = 1; k <= n; k <<= 1) {
		int num = 0;
		for(int i = n - k + 1; i <= n; i++) y[++num] = i;//按第二关键字排序
		for(int i = 1; i <= n; i++) if(sa[i] > k) y[++num] = sa[i] - k;//你的第二关键字就是上一次的第一关键字
		for(int i = 1; i <= m; i++) c[i] = 0;
		for(int i = 1; i <= n; i++) c[x[i]]++;
		for(int i = 2; i <= m; i++) c[i] += c[i - 1];
		for(int i = n; i;i--) sa[c[x[y[i]]]--] = y[i],y[i] = 0;//按第一关键字排序
		swap(x,y);
		x[sa[1]] = 1,num = 1;
		for(int i = 2; i <= n; i++) {
			x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? num:++num;
		}//离散化
		if(num == n) break;
		m = num;
	} 
}
void get_height() {
	for(int i = 1; i <= n; i++) rk[sa[i]] = i;
	for(int i = 1, k = 0; i <= n; i++) {
		if(rk[i] == 1) continue;
		if(k) k--;
		int j = sa[rk[i] - 1];
		while(i + k <= n && j + k <= n && s[i + k] == s[j + k]) k++;
		height[rk[i]] = k; // h函数满足 height[rk[i]] = h(i) >= h(i - 1) - 1;
	}
}
int main() {
	scanf("%s",s + 1);
	n = strlen(s + 1),m = 122;
	get_sa();
	// get_height();
	for(int i = 1; i <= n; i++) printf("%d ",sa[i]);
	// puts("");
	// for(int i = 1; i <= n; i++) printf("%d ",height[i]);
	return 0;
}