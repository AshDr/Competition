// https://oi.men.ci/linear-basis-notes/
// 不显式构造出集合 支持动态插入。
const int MAXL = 63;
struct LinearBasis {
  long long a[MAXL + 1];

  LinearBasis() { std::fill(a, a + MAXL + 1, 0); }

  LinearBasis(long long *x, int n) { build(x, n); }

  bool insert(long long t) {
    for (int j = MAXL; j >= 0; j--) {
      if (!t) return false;
      if (!(t & (1ll << j))) continue;

      if (a[j])
        t ^= a[j];
      else {
        for (int k = 0; k < j; k++)
          if (t & (1ll << k)) t ^= a[k];
        for (int k = j + 1; k <= MAXL; k++)
          if (a[k] & (1ll << j)) a[k] ^= t;
        a[j] = t;
        return true;
        break;
      }
    }
    return false;
  }
  bool query(long long t) {
    for (int j = MAXL; j >= 0; j--) {
      if (t & (1ll << j)) {
        if (!a[i])
          return false;
        else
          t ^= a[i];
      }
    }
    return true;
  }

  // 数组 x 表示集合 S，下标范围 [1...n]
  void build(long long *x, int n) {
    std::fill(a, a + MAXL + 1, 0);

    for (int i = 1; i <= n; i++) {
      insert(x[i]);
    }
  }

  long long queryMax() {
    long long res = 0;
    for (int i = 0; i <= MAXL; i++) res ^= a[i];
    return res;
  }
  void mergeFrom(const LinearBasis &other) {
    for (int i = 0; i <= MAXL; i++) insert(other.a[i]);
  }

  static LinearBasis merge(const LinearBasis &a, const LinearBasis &b) {
    LinearBasis res = a;
    for (int i = 0; i <= MAXL; i++) res.insert(b.a[i]);
    return res;
  }
} linbis;

// 显式构造出集合，不支持动态插入。
struct LinearBasis {
  std::vector<long long> v;
  int n;  // 原有集合 S 的大小

  // 数组 x 表示集合 S，下标范围 [1...n]
  void build(long long *x, int n) {
    this->n = n;
    std::vector<long long> a(MAXL + 1);

    for (int i = 1; i <= n; i++) {
      long long t = x[i];

      for (int j = MAXL; j >= 0; j--) {
        if ((t & (1ll << j)) == 0) continue;

        if (a[j])
          t ^= a[j];
        else {
          for (int k = 0; k < j; k++)
            if (t & (1ll << k)) t ^= a[k];
          for (int k = j + 1; k <= MAXL; k++)
            if (a[k] & (1ll << j)) a[k] ^= t;

          a[j] = t;
          break;
        }
      }
    }

    v.clear();
    for (int i = 0; i <= MAXL; i++)
      if (a[i]) v.push_back(a[i]);
  }

  bool query(long long t) {
    for (int j = MAXL; j >= 0; j--) {
      if (t & (1ll << j)) {
        if (!a[i])
          return false;
        else
          t ^= a[i];
      }
    }
    return true;
  }

  long long queryMax() {
    long long x = 0;
    for (size_t i = 0; i < v.size(); i++) x ^= v[i];
    return x;
  }
} linbis;
// 上面的都是主元为1，其他位为0的线性基
ll tmp[N];
struct Basis {
  ll a[MAXL + 1];

  Basis() {}

  bool add(ll x) {
    for (int i = MAXL; i >= 0; i--) {
      if (x & (1ll << i)) {
        if (!a[i]) {
          a[i] = x;
          return true;
          break;
        } else {
          x ^= a[i];
        }
      }
    }
    return false;
  }
  bool check(ll x) {
    for (int i = MAXL; i >= 0; i--) {
      if (x & (1ll << i)) {
        if (!a[i])
          return false;
        else {
          x ^= a[i];
        }
      }
    }
    return true;
    // return x == 0;
  }
  ll queryMax() {
    ll ans = 0;
    for (int i = MAXL; i >= 0; i--) {
      if (!(ans >> i & 1)) {
        ans ^= a[i];
      }
    }
    return ans;
  }
  ll query_kmn(ll k) {  // 第k小
    ll res = 0;
    int cnt = 0;
    k -= flag;
    if (!k) return 0;
    for (int i = 0; i <= MAXL; i++) {
      for (int j = i - 1; j >= 0; j--) {
        if (a[i] >> j & 1) a[i] ^= a[j];
      }
      if (a[i]) tmp[cnt++] = a[i];
    }
    if (k >= (1ll << cnt)) return -1;
    for (int i = 0; i < cnt; i++) {
      if (k >> i & 1) res ^= tmp[i];
    }
    return res;
  }
};
