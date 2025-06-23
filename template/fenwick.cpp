template <typename T>
struct Fenwick {
  int n;
  std::vector<T> tr;

  Fenwick(int n) : n(n), tr(n + 1, 0) {}

  int lowbit(int x) { return x & -x; }

  void modify(int x, T c) {
    for (int i = x; i <= n; i += lowbit(i)) tr[i] += c;
  }

  void modify(int l, int r, T c) {
    modify(l, c);
    if (r + 1 <= n) modify(r + 1, -c);
  }

  T query(int x) {
    T res = T();
    for (int i = x; i; i -= lowbit(i)) res += tr[i];
    return res;
  }

  T query(int l, int r) {
    assert(l <= r);
    return query(r) - query(l - 1);
  }

  int find_first(T sum) {
    int ans = 0;
    T val = 0;
    for (int i = __lg(n); i >= 0; i--) {
      if ((ans | (1 << i)) <= n && val + tr[ans | (1 << i)] < sum) {
        ans |= 1 << i;
        val += tr[ans];
      }
    }
    return ans + 1;
  }

  int find_last(T sum) {
    int ans = 0;
    T val = 0;
    for (int i = __lg(n); i >= 0; i--) {
      if ((ans | (1 << i)) <= n && val + tr[ans | (1 << i)] <= sum) {
        ans |= 1 << i;
        val += tr[ans];
      }
    }
    return ans;
  }
  int find_kth(int k) {
    int ans = 0, cnt = 0;
    for (int i = 1 << __lg(n); i >= 0; i--)  // 这里的20适当的取值，与MAX_VAL有关，一般取lg(MAX_VAL)
    {
      ans += (1 << i);
      if (ans >= n || cnt + tr[ans] >= k)
        ans -= (1 << i);
      else
        cnt += tr[ans];
    }
    return ans + 1;
  }                       // 注意k不能太大
  int lower_bound(T k) {  // k<=query(idx)
    if (k <= 0) return 0;
    int ans = 0;
    for (int i = 20; i >= 0; i--) {
      if (ans + (1 << i) <= n && tr[ans + (1 << i)] < k) {
        ans += (1 << i);
        k -= tr[ans];
      }
    }
    return ans + 1;
  }
};
/*
开区间版 fw.sum(r) 表示 [0~r)
下标[0,n-1]
template <typename T>
struct Fenwick {
    int n;
    std::vector<T> a;

    Fenwick(int n = 0) {
        init(n);
    }

    void init(int n) {
        this->n = n;
        a.assign(n, T());
    }

    void add(int x, T v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] += v;
        }
    }

    T sum(int x) {
        auto ans = T();
        for (int i = x; i > 0; i -= i & -i) {
            ans += a[i - 1];
        }
        return ans;
    }//[1, x)

    T rangeSum(int l, int r) {
        return sum(r) - sum(l);
    }//[0~r)-[0~l)


    int kth(T k) {
        int x = 0;
        T cur{}
        for (int i = 1 << std::__lg(n); i; i /= 2) {
            if (x + i <= n && cur + a[x + i - 1] <= k) {
                x += i;
                cur = cur + a[x - 1];
            }
        }
        return x;
    }
};
*/