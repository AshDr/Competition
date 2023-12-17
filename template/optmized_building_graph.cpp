/*如果是路径到路径，就用虚点连接两个路径
如果是森林的话，就不能用st表了，除非对每个森林用hld,一般做法是注意到我们只会有一个 
dfn区间不是一条重链上一段前缀的形式（跨过 LCA的那个区间），于是对这个区间线段树优化建图，
其他预处理重链后前缀优化建图
*/
int tot_ecnt = n;
vector<vector<int>> edgedown(n,vector<int>(22)),edgeup(n,vector<int>(22)); 
for(int i = 0; i < n; i++) edgedown[hld.in[i]][0] = edgeup[hld.in[i]][0] = i;

for(int o = 1; o <= lg2[n]; o++) {
    for(int i = 0; i + (1 << o) <= n; i++) {
        edgedown[i][o] = tot_ecnt++;
        edgeup[i][o] = tot_ecnt++;
        add_edge(edgedown[i][o], edgedown[i][o - 1]);
        add_edge(edgedown[i][o], edgedown[i + (1 << (o - 1))][o - 1]);

        add_edge(edgeup[i][o - 1], edgeup[i][o]);
        add_edge(edgeup[i + (1 << (o - 1))][o - 1], edgeup[i][o]);
    }
}
auto gao1 = [&](auto self, int l, int r, int p)->void {
    if(l <= hld.in[p] && hld.in[p] <= r) {
        if(l < hld.in[p]) self(self, l, hld.in[p] - 1, p);
        if(r > hld.in[p]) self(self, hld.in[p] + 1, r, p);
    }else {
        int bit = lg2[r - l + 1];
        add_edge(p, edgedown[l][bit]);
        add_edge(p, edgedown[r - (1 << bit) + 1][bit]);
    }
};
auto gao2 = [&](auto self, int l, int r, int p)->void {
    if(l <= hld.in[p] && hld.in[p] <= r) {
        if(l < hld.in[p]) self(self, l, hld.in[p] - 1, p);
        if(r > hld.in[p]) self(self, hld.in[p] + 1, r, p);
    }else {
        int bit = lg2[r - l + 1];
        add_edge(edgeup[l][bit], p);
        add_edge(edgeup[r - (1 << bit) + 1][bit], p);
    }
};

for(int i = 0; i < m; i++) {
    int op, a, b, c;
    cin >> op >> a >> b >> c;
    --a;--b;--c;
    if(op == 1) { //c向a~b连边
        while(hld.top[a] != hld.top[b]) {
            if(hld.dep[hld.top[a]] < hld.dep[hld.top[b]]) swap(a, b);
            gao1(gao1, hld.in[hld.top[a]], hld.in[a], c);
            a = hld.parent[hld.top[a]];
        }
        if(hld.in[a] > hld.in[b]) swap(a ,b);
        gao1(gao1, hld.in[a], hld.in[b], c);
    }else {//a~b向c连边
        while(hld.top[a] != hld.top[b]) {
            if(hld.dep[hld.top[a]] < hld.dep[hld.top[b]]) swap(a, b);
            gao2(gao2, hld.in[hld.top[a]], hld.in[a], c);
            a = hld.parent[hld.top[a]];
        }
        if(hld.in[a] > hld.in[b]) swap(a ,b);
        gao2(gao2, hld.in[a], hld.in[b], c);
    }
}