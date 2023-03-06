namespace SAM {
    int np=1,tot=1;
    int len[N<<1],ch[N<<1][26],fa[N<<1],cnt[N<<1];
    vector<int> G[N<<1];
    void extend(int cc) {
        int p=np;
        np=++tot;
        len[np]=len[p]+1;cnt[np]=1;
        for(;p&&!ch[p][cc];p=fa[p]) ch[p][cc]=np;
        if(p==0) {
            fa[np]=1;
        }else{
            int q=ch[p][cc];
            if(len[q]==len[p]+1) {
                fa[np]=q;
            }else {
                int nq=++tot;//split node
                len[nq]=len[p]+1;fa[nq]=fa[q];
                fa[q]=nq;fa[np]=nq;
                for(;p&&ch[p][cc]==q;p=fa[p]) ch[p][cc]=nq; 
                memcpy(ch[nq],ch[q],sizeof(ch[q]));
                // four types edges
            }
        }
    }
    void build_suf_tree() {
        for(int i = 2; i <= tot; i++) {
            G[fa[i]].push_back(i);
        }    
    }
    ll dfs(int u) {
        ll res = 0;
        if(u!=1) res+=len[u]-len[fa[u]];
        for(auto v: G[u]) {
            res += dfs(v);
        }
        return res;
    }
    ll getstrnum(){
        return dfs(1);
    }
}