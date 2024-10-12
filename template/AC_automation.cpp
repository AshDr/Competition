namespace AC_automation {
    int trie[N][30],val[N],fail[N],tot = 0;
    void build_trie(string s) {
        int len = s.size();
        int now = 0;
        for(int i = 0 ; i < len ; i++) {
            int t = s[i] - 'a';
            if(!trie[now][t]) trie[now][t] = ++tot;
            now = trie[now][t]; 
        }
        val[now]++;
    }
    void get_fail() {
        queue<int> q;
        for(int i = 0 ; i < 26; i++) if(trie[0][i]) fail[trie[0][i]] = 0,q.push(trie[0][i]);
        while(!q.empty()) {
            int now = q.front();q.pop();
            for(int i = 0 ; i < 26; i++) {
                if(trie[now][i]) fail[trie[now][i]] = trie[fail[now]][i],q.push(trie[now][i]);
                else trie[now][i] = trie[fail[now]][i]; 
            }
        }
    }  
    int AC_query(string ss) {
        int len = ss.size();
        int res = 0,now = 0;
        for(int i = 0 ; i < len; i++) {
            now = trie[now][ss[i] - 'a'];
            for(int  j = now; j && ~val[j]; j = fail[j]) {
                res += val[j];
                val[j] = -1;
            } 
        }
        return res;
    }
}