// ECC
struct Edge {
  int to;
  int id;
  operator int() const { return to; }
};

struct LowLink {
  int n;
  vector<vector<Edge> > g;
  vector<int> in, out, low;
  int ts;
  set<int> bridge;
  // map<int, int> bridge;
  // mutiedge might use map
  LowLink(const vector<vector<Edge> > &g) : n(int(g.size()) - 1), g(g) {
    ts = 0;
    in.assign(n + 1, 0);
    out.assign(n + 1, 0);
    low.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      if (in[i] == 0) {
        tarjan(i, -1);
      }
    }

    id.assign(n + 1, 0);
    cnt = 0;
    for (int i = 1; i <= n; i++) {
      if (id[i] == 0) {
        dfs(i, -1);
      }
    }
    group.resize(cnt + 1);
    ;
    for (int i = 1; i <= n; i++) {
      group[id[i]].push_back(i);
    }
  }

  void tarjan(int u, int from) {
    in[u] = low[u] = ++ts;
    for (auto j : g[u]) {
      if (!in[j]) {
        tarjan(j, j.id);
        low[u] = min(low[u], low[j]);
        if (low[j] > in[u]) {
          bridge.insert(j.id);
        }
      } else if (j.id != from)
        low[u] = min(low[u], in[j]);
    }
    out[u] = ts;
  }

  int cnt;
  vector<vector<int> > group;
  vector<int> id;

  void dfs(int u, int fa) {
    if (fa != -1 && low[u] <= in[fa]) {
      id[u] = id[fa];
    } else {
      id[u] = ++cnt;
    }
    for (auto j : g[u]) {
      if (id[j] == 0) {
        dfs(j, u);
      }
    }
  }
};