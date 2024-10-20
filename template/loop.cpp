void dfs(ll id, ll step, ll fa) {
  vis[id] = 1, dfn[id] = step;
  for (ll i = head[id]; i != -1; i = e[i].next) {
    ll v = e[i].to;
    if (v == fa || vis[v] == 2) continue;
    if (vis[v] == 1) {
      sum += step - dfn[v] + 1;  // loop length
    } else
      dfs(v, step + 1, id);
  }
  vis[id] = 2;
}