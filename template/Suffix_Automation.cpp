namespace SAM {
    int np=1,tot=1;
    int len[N<<1],ch[N<<1][26],fa[N<<1],endpos[N<<1];
    //fa[]是parent树上每个节点的父亲
    //ch[u][c]是每个节点的转移边，表示u节点后加上c字符能转移到的节点
    //len[]表示每个等价类节点的最大串长
    //endpos[] 当前等价类节点在原串上的信息，一般表示子串出现的位置个数
    vector<int> G[N<<1];
    void extend(int cc) {
        int p=np;
        np=++tot;
        len[np]=len[p]+1;endpos[np]=1;
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
            G[fa[i]].push_back(i); //建立parent树
        }    
    }
    //对sam做dag上的操作时要先手动做一遍topo，从tot~1不一定满足拓扑序 
    ll dfs(int u) {
        ll res = 0;
        if(u!=1) res+=len[u]-len[fa[u]];
        for(auto v: G[u]) {
            res += dfs(v);
            endpos[u] += endpos[v];
        }
        return res;
    }
    ll getstrnum(){
        return dfs(1);
    }
}
/*
ac自动机是多个模式串构建的接受前缀的dfa
sam是一个接受s所有后缀的dfa 是dag，从t0出发，到达一个终止状态就是s的一个后缀
任意从初始状态 t_0 开始的路径，如果我们将转移路径上的标号写下来，都会形成 s 的一个 子串。反之每个 s 的子串对应从 t_0 开始的某条路径。
所有字符串 s 的非空子串都可以根据它们的 endpos 集合被分为若干 等价类，因为可能endpos(s1) = endpos(s2)，一类串在sam中对应一个节点
SAM 中的状态数等于所有子串的等价类的个数，再加上初始状态。
一个 后缀链接 link(v) 连接到对应于 w 的最长后缀的另一个 endpos 等价类的状态,w为等价类中最长的那个串
任意一个 SAM 的 endpos 集合形成了一棵树
*/