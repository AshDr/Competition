#include <bits/stdc++.h>
// P3275
// 一般的情况
// x_a - x_b >= c(x_b <= x_a - c) -> G[a].push_back({b, -c})
// x_a - x_b <= c(x_a <= x_b + c) -> G[b].push_back({a, c})
// x_a == x_b -> G[b].push_back({a, 0}) G[a].push_back({b, 0})
// 确保图联通，不联通要加超级源点 判是否存在负环
// 记超级源点为s, dis[s] = w, 跑最短路spfa 求出来的就是 x_1,x_2...x_n <= w的最大解

// 如果要求x_1,x_2...x_n>=w的最小解，则需要在 x_a >= x_b + c的情况下 G[b].push_back({a, c})
// 这个时候又是正权环无解,跑最长路
//(跑最短路，判负环) (跑最长路，判正环) 使用哪个就取决于你要求的是>=w的最小解还是 <=w的最大解

// 稳过的算法:
// 边权都非负的时候，跑最长路, 不用spfa
// 先用tarjan 把环缩掉，可以证明如果有解，环内边权均为0，故这个强连通分量内所有的 dist 值都相同
// 然后拓扑排序，在新图上求dist,d[0] = 0, 其余为-inf, 常规跑即可
using namespace std;
struct qq {
  int v, w;
};
vector<qq> g[10001];
int n, m, di[10001], vi[10001];
bool spfa(int u) {
  vi[u] = 1;
  for (int i = 0; i < g[u].size(); i++) {
    int v = g[u][i].v, w = g[u][i].w;
    if (di[v] > di[u] + w) {
      di[v] = di[u] + w;
      if (vi[v]) return 0;
      if (!spfa(v)) return 0;
    }
  }
  vi[u] = 0;
  return 1;
}
int main() {
  cin >> n >> m;
  while (m--) {
    int q, u, v, w;
    cin >> q >> u >> v;
    if (q == 1) {
      cin >> w;
      g[u].push_back((qq){v, -w});
    }
    if (q == 2) {
      cin >> w;
      g[v].push_back((qq){u, w});
    }
    if (q == 3) {
      g[u].push_back((qq){v, 0});
      g[v].push_back((qq){u, 0});
    }
  }
  for (int i = 1; i <= n; i++) di[i] = 2e8;
  for (int i = 1; i <= n; i++) g[0].push_back((qq){i, 0});
  if (spfa(0))
    cout << "Yes";
  else
    cout << "No";
  // for(int i = 1; i <=n ;i++) cout << di[i] << " ";
  return 0;
}
/*
最长路 推荐 因为解是>0的最小值
bool spfa(int u)
{
    vi[u]=1;
    for(int i=0;i<g[u].size();i++)
    {
        int v=g[u][i].v,w=g[u][i].w;
        if(di[v]<di[u]+w)
        {
            di[v]=di[u]+w;
            if(vi[v])return 0;
            if(!spfa(v))return 0;
        }
    }
    vi[u]=0;
    return 1;
}
int main()
{
    cin>>n>>m;
    while(m--)
    {
        int x, y, w;
        cin >> x >> y >> w;
        g[x - 1].push_back({y, w});
    }
    for(int i = 0; i <= n; i++) {
        if(i > 1) {
            g[i - 1].push_back({i, 0});
            g[i].push_back({i - 1, -1});
        }
    }
    for(int i=1;i<=n;i++)di[i]=-2e8;
    for(int i=1;i<=n;i++)g[0].push_back((qq){i,0});
    if(!spfa(0)) {
        cout << -1 << "\n";
    }else {
        // for(int i = 1; i <=n ;i++) cout << di[i] << " ";
        cout << di[n] << "\n";
    }
    return 0;
}
*/