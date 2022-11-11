#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e3+10;
int mat[maxn],vis[maxn];
int n,m,e;
int clk;
vector<int> p[maxn];
bool dfs(int u) {
    for(auto &v:p[u]) {
        if(vis[v] != clk) {
            vis[v] = clk;
            if(!mat[v] || dfs(mat[v])) {
                mat[v] = u;
                return true;
            }
        }
    }
    return false;
}
int main() {
    ios::sync_with_stdio(0);
    cin>>n>>m>>e;
    int u,v;
    for(int i=1; i<=e; i++)  {
        cin>>u>>v;
        p[u].push_back(v);
    }
    int ans = 0;
    for(int i=1; i<=n; i++) {
        ++clk;
        if(dfs(i)) ans++;
    }
    cout<<ans;
    return 0;
}
/*
建边可以建单向但是最后要对的每个点都要dfs匹配

或者就建双向边，然后只对左部点进行dfs匹配
*/