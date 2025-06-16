// https://codeforces.com/contest/1334/standings
template <int P>
struct NTT {
  static constexpr int ROOT = 3;
  std::vector<int> rev, roots{0, 1};
  int power(int base, int e) {
    int res = 1;
    while (e > 0) {
      if (e % 2 == 1) res = 1LL * res * base % P;
      base = 1LL * base * base % P;
      e /= 2;
    }
    return res;
  }
  void dft(std::vector<int> &a) {
    int n = a.size();
    if (int(rev.size()) != n) {
      int k = __builtin_ctz(n) - 1;
      rev.resize(n);
      for (int i = 0; i < n; ++i) rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
    }
    for (int i = 0; i < n; ++i)
      if (rev[i] < i) std::swap(a[i], a[rev[i]]);
    if (int(roots.size()) < n) {
      int k = __builtin_ctz(roots.size());
      roots.resize(n);
      while ((1 << k) < n) {
        int e = power(ROOT, (P - 1) >> (k + 1));
        for (int i = 1 << (k - 1); i < (1 << k); ++i) {
          roots[2 * i] = roots[i];
          roots[2 * i + 1] = 1LL * roots[i] * e % P;
        }
        ++k;
      }
    }
    for (int k = 1; k < n; k *= 2) {
      for (int i = 0; i < n; i += 2 * k) {
        for (int j = 0; j < k; ++j) {
          int u = a[i + j];
          int v = 1LL * a[i + j + k] * roots[k + j] % P;
          int x = u + v - P;
          x += x >> 31 & P;
          a[i + j] = x;
          x = u - v;
          x += x >> 31 & P;
          a[i + j + k] = x;
        }
      }
    }
  }
  void idft(std::vector<int> &a) {
    int n = a.size();
    std::reverse(a.begin() + 1, a.end());
    dft(a);
    int inv = power(n, P - 2);
    for (int i = 0; i < n; ++i) a[i] = 1LL * a[i] * inv % P;
  }
  std::vector<int> conv(std::vector<int> a, std::vector<int> b) {
    int sz = 1, tot = a.size() + b.size() - 1;
    while (sz < tot) sz *= 2;
    a.resize(sz);
    b.resize(sz);
    dft(a);
    dft(b);
    for (int i = 0; i < sz; ++i) a[i] = 1LL * a[i] * b[i] % P;
    idft(a);
    a.resize(tot);
    return a;
  }
};
// 998244353 1004535809