struct SqrtDecomposition {
  const int block_size, bn;      // bn是block的数量
  std::vector<int> ls, rs;       // 每个块i的段位记为[ls[i], rs[i]]
  std::vector<bool> to_be_eval;  // 该block的懒标记是否全部被清空
  std::vector<int> belong;
  explicit SqrtDecomposition(const int n_)  // 1~n_
      : block_size(std::round(std::sqrt(n_))), bn((n_ + block_size - 1) / block_size) {
    ls.resize(n_ + 1);
    rs.resize(n_ + 1);
    belong.resize(n_ + 1);
    to_be_eval.assign(n_ + 1, false);
    for (int i = 1; i <= bn; ++i) {
      ls[i] = block_size * (i - 1) + 1;
      rs[i] = (i == bn ? n_ : ls[i] + block_size - 1);
    }
    for (int i = 1; i <= n_; i++) {
      belong[i] = (i - 1) / block_size + 1;
    }
  }
  template <typename T>
  void partial_update(const int idx, const T val);  // to implemented  单点修改

  template <typename T>
  void total_update(const int idx, const T val);  // to implemented 整块修改

  template <typename T>
  void update(const int l, const int r, const T val) {
    assert(l <= r);
    const int b_l = belong[l], b_r = belong[r];  // [l, r]->[b_l, b_r]
    if (b_l < b_r) {
      if (l == ls[b_l]) {  // 如果左端点恰好是区间的开始,只要更新这个区间就好了
        total_update(b_l, val);
      } else {
        for (int i = l; i <= rs[b_l]; ++i) {
          partial_update(i, val);
        }
      }

      for (int i = b_l + 1; i < b_r; ++i) {
        total_update(i, val);
      }

      if (r == rs[b_r]) {  // 如果右端点恰好是区间的结尾
        total_update(b_r, val);
      } else {
        for (int i = ls[b_r]; i <= r; ++i) {
          partial_update(i, val);
        }
      }
    } else {
      for (int i = l; i <= r; ++i) {
        partial_update(i, val);
      }
    }
  }

  template <typename T>
  void partial_query(const int idx, T *val);  // 单点查询

  template <typename T>
  void total_query(const int idx, T *val); // 整块查询

  template <typename T>
  T query(const int l, const int r, const T indentity) {
    const int b_l = belong[l], b_r = belong[r];  // [l, r]->[b_l, b_r]
    T res = indentity;                                  // 幺元 indentity, 0 for sum, 1 for product
    if (b_l < b_r) {
      if (l == ls[b_l]) {
        total_query(b_l, &res);
      } else {
        for (int i = l; i <= rs[b_l]; ++i) {
          partial_query(i, &res);
        }
      }
      for (int i = b_l + 1; i < b_r; ++i) {
        total_query(i, &res);
      }
      if (r == rs[b_r]) {
        total_query(b_r, &res);
      } else {
        for (int i = ls[b_r]; i <= r; ++i) {
          partial_query(i, &res);
        }
      }
    } else {
      for (int i = l; i <= r; ++i) {
        partial_query(i, &res);
      }
    }
    return res;
  }
};
// instance
std::vector<long long> a, b, lazy;
// 分别是原数组，block维护的信息和懒标记
// 其中a的长度是数组原长，b和lazy都是block的数量，记录了block的和和懒标记。
template <typename T>
void SqrtDecomposition::partial_update(const int idx, const T val) {
  //todo: upd both a and b 
}

template <typename T>
void SqrtDecomposition::total_update(const int b_idx, const T val) {
  //todo: upd lazy

  to_be_eval[b_idx] = true;  // 标记block存在懒标记，计算时需要重新赋值
}

template <typename T>
void SqrtDecomposition::partial_query(const int idx, T *val) {
  const int block = belong[idx];
  if (to_be_eval[block]) {
    for (int i = ls[block]; i < rs[block]; ++i) {
      partial_update(i, lazy[block]);
    }
    //todo: clear lazy

    to_be_eval[block] = false;
  }
  //todo: add the value of a[idx]

}

template <typename T>
void SqrtDecomposition::total_query(const int b_idx, T *val) { // 考虑懒标记的影响,因为标记不一定被收割
  
}