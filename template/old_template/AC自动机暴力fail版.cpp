#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
struct Trie {
	int fail,end;
	int son[26];
}trie[N];
struct  node {
	int num,pos;
	friend bool operator < (const node& x,const node& y) {
		if(x.num != y.num)return x.num > y.num;
		else return x.pos < y.pos;
	}
}ans[N];
int n,tot;
string a[N];
void clean(int x) {
	memset(trie[x].son,0,sizeof(trie[x].son));
	trie[x].fail = trie[x].end = 0;
}
void insert(string s,int id) {
	int nowpos = 0;
	for(int i = 0 ; i <(int) s.size(); i++) {
		int x = s[i] - 'a';
		if(!trie[nowpos].son[x]) trie[nowpos].son[x] = ++tot,clean(tot);//技巧 边建边清除上一组数据的trie
		nowpos = trie[nowpos].son[x];
	}
	trie[nowpos].end = id;//记录是哪个字符串的结尾 为了后面映射统计答案用
}
void get_fail(){
	queue<int> q;
	trie[0].fail = 0;
	for(int i = 0 ; i < 26 ; i++) {
		if(trie[0].son[i]) {
			trie[trie[0].son[i]].fail = 0;
			q.push(trie[0].son[i]);
		} 
	}
	while(!q.empty()) {
		int u = q.front();q.pop();
		for(int i = 0 ; i < 26; i++) {
			if(trie[u].son[i]) {
				trie[trie[u].son[i]].fail = trie[trie[u].fail].son[i];//我为人人转移
				q.push(trie[u].son[i]);
			}
			else trie[u].son[i] = trie[trie[u].fail].son[i];
		}
	}
}//建trie图
int AC_query(string s) {
	int nowpos = 0;
	int t = 0;
	for(int i = 0; i <(int) s.size(); i++) {
		int x = s[i] - 'a';
		nowpos = trie[nowpos].son[x];
		for(int j = nowpos; j; j = trie[j].fail) ans[trie[j].end].num++,t++;//每到一个位置 暴力跳fail
	}
	return t;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	while(cin>>n) {
		if(!n) break;
		tot = 0;//注意
		clean(0);//根先清一下
		for(int i = 1; i <= n; i++) {
			cin>>a[i];
			insert(a[i],i); 
			ans[i].num = 0;
			ans[i].pos = i;
		}
		get_fail();
		string ss;
		cin>>ss;
		AC_query(ss);
		sort(ans + 1,ans + 1 + n);
		cout<<ans[1].num<<endl;
		cout<<a[ans[1].pos]<<endl;
		for(int i = 2; i <= n; i++) {
			if(ans[i].num == ans[i - 1].num) cout<<a[ans[i].pos]<<endl;
			else break;
		}
	}
	return 0;
}