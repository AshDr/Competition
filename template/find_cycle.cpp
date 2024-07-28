vector<int> dfn(n + 1),fa(n + 1), vis(n + 1);
    int dfn_cnt = 0;
    vector<int> cycle;
    function<void(int)> get_loop = [&](int u) {
        dfn[u] = ++dfn_cnt;
        for(int i = head[u]; ~i; i = edges[i].nxt) {
            int v = edges[i].to;
            if(dfn[v]) {
                if(dfn[v] < dfn[u]) continue; // 第一次遇到
                int x = v;
                while(x != u) {
                    cycle.push_back(x);
                    x = fa[x];
                }
                cycle.push_back(u);
            }else {
                fa[v] = u;
                get_loop(v);
            }
        }
    };