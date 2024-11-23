mint Lagrange(const vector<mint> &x, const vector<mint> &y, mint k) {
  const int n = (int)x.size() - 1;
  vector<mint> pre(n + 2), suf(n + 2);
  mint ans = 0;
  pre[0] = k - x[0], suf[n + 1] = 1;
  for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] * (k - x[i]);
  for (int i = n; i >= 0; i--) suf[i] = suf[i + 1] * (k - x[i]);
  for (int i = 0; i <= n; i++) {
    mint up = (i == 0 ? 1 : pre[i - 1]) * suf[i + 1];
    mint down = invfact[i] * invfact[n - i] * (((n - i) % 2 == 1) ? mint(0) - 1 : 1);
    ans = (ans + y[i] * up * down);
  }
  return ans;
}