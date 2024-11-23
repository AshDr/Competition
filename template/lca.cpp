// index from 0
// anc(n, vector<int>(20, -1)); depth[0] = 0
// use __lg for anc
auto dfs = [&](auto self, int u, int p) -> void {
  for (int i = 1; i <= __lg(depth[u]); i++) {
    anc[u][i] = anc[anc[u][i - 1]][i - 1];
  }
  for (auto v : G[u]) {
    if (v == p) continue;
    depth[v] = depth[u] + 1;
    anc[v][0] = u;
    self(self, v, u);
  }
};
dfs(dfs, s, -1);
auto lca = [&](int x, int y) {
  if (depth[x] < depth[y]) swap(x, y);
  for (int i = __lg(depth[x]); i >= 0; i--) {
    if (anc[x][i] == -1) continue;
    if (depth[anc[x][i]] >= depth[y]) x = anc[x][i];
  }
  if (x == y) return x;
  for (int i = __lg(depth[x]); i >= 0; i--) {
    if (anc[x][i] == -1) continue;
    if (anc[x][i] != anc[y][i]) {
      x = anc[x][i];
      y = anc[y][i];
    }
  }
  return anc[x][0];
};