namespace CD {
	vector<pii> G[N];
	int S=n,rt=0,cnt,mxpart=1e9,siz[N]; //init S and mxpart
	void find_rt(int u, int fa) {
	    siz[u]=1;
	    int mx=0;
	    for(auto [v,w]: G[u]) {
	        if(vis[v]||v==fa) continue;
	        find_rt(v, u);
	        siz[u]+=siz[v];
	        mx=max(mx,siz[v]);
	    }
	    mx=max(mx,S-siz[u]);
	    // if(mx<mxpart) mxpart=mx,rt=u;
	    if(mx <= S / 2) rt = u;
	    //哪个t了就换另一个
	}
	int get_siz(int u, int fa) {
	    int val=1;
	    for(auto [v,w]:G[u]) {
	        if(vis[v]||v==fa) continue;
	        val+=get_siz(v, u);
	    }
	}
	void get_dis(int u, int fa, int dis) {
	    if(dis<M) d[++cnt]=dis;
	    for(auto [v,w]: G[u]) {
	        if(vis[v]||v==fa) continue;
	        get_dis(v, u, dis+w);
	    }
	}
	void calc(int u) {
	    mxpart=1e9;
	    rt=u;
	    find_rt(u,0);
	    // cout<<u<<" "<<rt<<endl;
	    vis[rt]=1;
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
	    int tmp=S;
	    for(auto [v,w]:G[rt]) {
	        if(!vis[v]) {
	            // S=(siz[v]<siz[rt]?siz[v]:tmp-siz[rt]);
	            calc(v);
	        }
	    }
	}

}