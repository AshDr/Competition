namespace CD {
    vector<pii> G[N];
    int S=n,rt=0,cnt,mxpart=1e9,siz[N],vis[N],parent[N]; //init S and mxpart
    int d[N];
    void find_rt(int u, int fa) {
        int mx=0;
        for(auto [v,w]: G[u]) {
            if(vis[v]||v==fa) continue;
            find_rt(v, u);
            mx=max(mx,siz[v]);
        }
        mx=max(mx,S - siz[u]);
        if(mx < mxpart) mxpart=mx,rt=u;
    }
    void get_siz(int u, int fa) {
        siz[u]=1;
        for(auto [v,w]:G[u]) {
            if(vis[v] || v==fa) continue;
            get_siz(v, u);
            siz[u]+=siz[v];
        }
    }
    void get_dis(int u, int fa, int dis) {
        if(dis<M) d[++cnt]=dis;
        for(auto [v,w]: G[u]) {
            if(vis[v]||v==fa) continue;
            get_dis(v, u, dis+w);
        }
    }
    void calc(int u, int prefa) {
        mxpart=1e9;
        rt=u;
        get_siz(u, 0);
        S = siz[u];
        find_rt(u, 0);
        // cout<<u<<" "<<rt<<endl;
        vis[rt]=1;
        // parent[rt] = prefa; //点分树的父亲
        for(auto [v,w]: G[rt]) { //注意从这一下都要写成rt
            if(vis[v]) continue;
            cnt=0;get_dis(v,rt,w);
            /*
            Calc 
            */
        }
        /*
        Delete info
        */
        int curfa = rt;
        for(auto [v,w]:G[rt]) {
            if(!vis[v]) {
                calc(v, curfa);
            }
        }
    }
}