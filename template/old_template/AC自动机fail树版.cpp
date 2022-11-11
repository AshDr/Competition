//ACAM FAIL VERSION
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
struct Trie {
	int end,fail;
	int son[26];
}trie[N];
int ans[N];
string s[N];
int n,tot;
int head[N],to[N],nxt[N],tot1;
int ed[N];
void addedge(int u, int v) {
	to[tot1] = v;nxt[tot1] = head[u];head[u] = tot1++;
}
void insert(string s,int id) {
	int nowpos = 0;
	for(int i = 0; i <(int)s.size(); i++) {
		int x = s[i] - 'a';
		if(!trie[nowpos].son[x]) trie[nowpos].son[x] = ++tot;
		nowpos = trie[nowpos].son[x];
	}
	trie[nowpos].end = id;
	ed[id] = nowpos;
}
void get_fail() {
	queue<int> q;
	trie[0].fail = 0;
	for(int i = 0; i < 26; i++) {
		if(trie[0].son[i]) {
			trie[trie[0].son[i]].fail = 0;
			q.push(trie[0].son[i]);
		}
	}
	while(!q.empty()) {
		int u = q.front();q.pop();
		for(int i = 0; i < 26 ;i++) {
			if(trie[u].son[i]) {
				trie[trie[u].son[i]].fail = trie[trie[u].fail].son[i];
				q.push(trie[u].son[i]);
			}
			else trie[u].son[i] = trie[trie[u].fail].son[i]; 
		}
	}
}
void AC_query(string text) {
	int nowpos = 0;
	for(int i = 0 ; i < (int)text.size(); i++) {
		int x = text[i] - 'a';
		nowpos = trie[nowpos].son[x];
		ans[nowpos]++;
	}
}
void dfs(int u) {
	for(int i = head[u]; ~i ; i = nxt[i]) {
		int v = to[i];
		dfs(v);
		ans[u] += ans[v];
	}
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	memset(head,-1,sizeof head);
	cin>>n;
	for(int i = 1; i <= n; i++) {
		cin>>s[i];
		insert(s[i],i);
	}
	get_fail();
	for(int i = 1; i <= tot; i++) addedge(trie[i].fail,i);
	string text;
	cin>>text;
	AC_query(text);
	dfs(0);
	for(int i = 1; i <= n; i++) cout<<ans[ed[i]]<<endl;
	return 0;
}