// 必须是无向简单图 
struct ECC {
    int n;
    vector<vector<int>> g, ecc; //每个边双集合
    vector<int> dfn, low, stk, belong;
    int ts, cnt;
    ECC(const vector<vector<int>>& G): n(int(G.size())),g(G) {
        cout << n << "!\n";
        dfn.assign(n, 0);
        low.assign(n, 0);
        belong.assign(n, -1);
        cnt = 0;ts = 0;
        for(int i = 0; i < n; i++) {
            if(!dfn[i]) {
                stk.clear();
                tarjan(i, -1);
            }
        }
    }
    void tarjan(int u, int p) {
        dfn[u] = low[u] = ++ts;
        stk.push_back(u);
        for(auto &v: g[u]) {
            if(!dfn[v]) {
                tarjan(v, u);
                low[u] = min(low[u], low[v]);
            }else if(v != p) {//如果包含重边和自环 只要这条边不是下来的边的反向边就行
                low[u] = min(low[u], dfn[v]);
            }
        }
        if(dfn[u] == low[u]) {
            ecc.push_back({});
            int x;
            do {
                x = stk.back();
                stk.pop_back();
                ecc[cnt].push_back(x);
                belong[x] = cnt;
            }while(x != u);
            cnt++;//边双集合缩点的新编号
        }
    }
};