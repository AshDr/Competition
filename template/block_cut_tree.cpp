/*
圆点方点相间
原图中u->v必经点=u->v上圆点的数量=树上距离/2 + 1 
度数为1的圆点都对应唯一一个方点
每条边对应唯一一个方点
圆方树是无根树
*/
template<class T>
struct BlockCutTree{ //只适用于连通无向简单图
    int n;
    vector<vector<T> > g, ng;//原图 与 新图(树)
    vector<int> dfn, low, stk;
    vector<bool> cut;
    int root, ts, cnt;
    int conn; //子图个数

    BlockCutTree(const vector<vector<T> > &g) : n(int(g.size())), g(g) {
        cut.assign(n, false);
        dfn.assign(n, 0);
        low.assign(n, 0);
        ng.assign(n, {});
        ts = 0; cnt = n; //0~n-1 n~...
        conn = 0;
        // 不用特判根是不是割点
        for(root = 0; root < n; root++){
            if (dfn[root] == 0){
                conn += 1;
                stk.clear(); //注意清空 每次对于一个子图 栈里会剩一个点
                tarjan(root, -1);
            }
        }
    }
    void tarjan(int u, int p){
        dfn[u] = low[u] = ++ts;
        stk.push_back(u);
        for(auto &v : g[u]){
            if (!dfn[v]){
                tarjan(v, u);                
                low[u] = min(low[u], low[v]);
                if (low[v] >= dfn[u]){
                    ng.push_back({});
                    int x;
                    do{
                        x = stk.back();
                        stk.pop_back();
                        ng[x].push_back(cnt);
                        ng[cnt].push_back(x);
                    }while(x != v); // 不弹u
                    ng[u].push_back(cnt);
                    ng[cnt].push_back(u);
                    cnt++;//新建方点
                }
            }
            else if(v != p){
                low[u] = min(low[u], dfn[v]);
            }
        }
    }
};