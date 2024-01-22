#include <bits/stdc++.h>
using namespace std;
int wei[10],tot;
map<int,int> mp; 
inline int check(int x)
{
	int now=sqrt(x);
	if(now*now==x)return 1;
	return 0;
}
inline int hsh(int x)
{
	tot=0;
	while(x)wei[++tot]=x%10,x/=10;
	sort(wei+1,wei+tot+1);
	int res=0;
	for(int i=1;i<=tot;i++)res=res*10+wei[i];
	return res;
}
int main()
{
	for(int i=100000000;i<=999999999;i++)
	{
		if(check(i))
		{
			mp[hsh(i)]++;
			if(hsh(i)==169)printf("i:%d,sqrt:%d\n",i,(int)sqrt(i));
		}
	}
	for(map<int,int>::iterator it=mp.begin();it!=mp.end();it++)
	{
		if(it->second >=  9)
		{
			printf("ok %d\n",it->first);
			exit(0);
		}
	}
	return 0;
}