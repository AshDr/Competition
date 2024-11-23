template <typename T, bool isMin>
struct SparseTable {
  int n, m;
  vector<vector<T>> st;
  vector<T> a;
  SparseTable() {}
  SparseTable(int n) : n(n), m(__lg(n)), st(m + 1, vector<T>(n + 1)) {}
  SparseTable(const vector<T> &init) : SparseTable((int)init.size()) {
    a.assign(all(init));
    iota(all(st[0]), 0);
    for (int j = 1; j <= m; j++) {
      for (int i = 1; i + (1 << j) - 1 <= n; i++) {
        if (isMin) {
          st[j][i] = a[st[j - 1][i]] < a[st[j - 1][i + (1 << (j - 1))]] ? st[j - 1][i] : st[j - 1][i + (1 << (j - 1))];
        } else {
          st[j][i] = a[st[j - 1][i]] > a[st[j - 1][i + (1 << (j - 1))]] ? st[j - 1][i] : st[j - 1][i + (1 << (j - 1))];
        }
      }
    }
  }

  T rmq(int l, int r) {  // query value
    if (l > r) {
      if (isMin) return numeric_limits<T>::max() / 2;
      return numeric_limits<T>::min() / 2;
    }
    int len = __lg(r - l + 1);
    if (isMin) return min(a[st[len][l]], a[st[len][r - (1 << len) + 1]]);
    return max(a[st[len][l]], a[st[len][r - (1 << len) + 1]]);
  }

  T rmp(int l, int r) {  // query position
    if (l > r) {
      if (isMin) return numeric_limits<T>::max() / 2;
      return numeric_limits<T>::min() / 2;
    }
    int len = __lg(r - l + 1);
    if (isMin) return a[st[len][l]] < a[st[len][r - (1 << len) + 1]] ? st[len][l] : st[len][r - (1 << len) + 1];
    return a[st[len][l]] > a[st[len][r - (1 << len) + 1]] ? st[len][l] : st[len][r - (1 << len) + 1];
  }
};