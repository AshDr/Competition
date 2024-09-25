void GetLoop(const int u, int v) {
  while (v != u) {
    lop[ncnt].push_back(v);
    v = fa[v];
  }
  lop[ncnt].push_back(u);
  std::reverse(lop[ncnt].begin(), lop[ncnt].end());
}
void tarjan(const int u) {
  dfn[u] = low[u] = ++vistime;
  for (auto v : ee[u]) if (dfn[v] == 0) {
    fa[v] = u;
    tarjan(v);
    low[u] = std::min(low[u], low[v]);
  } else if (v != fa[u]) {
    low[u] = std::min(low[u], dfn[v]);
  }
  for (auto v : ee[u]) if ((fa[v] != u) && (dfn[v] > dfn[u]))  {
    GetLoop(u, v);
  }
}