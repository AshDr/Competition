// 注意bit范围
struct Persistent_Trie {
  static constexpr int ALPHABET = 2;
  struct Node {
    std::array<int, ALPHABET> childs;
    Node() : childs{} {}
  };
  std::vector<Node> trie;
  std::vector<int> root, cnt;
  int rt_num;
  Persistent_Trie(int n) : rt_num(n) { init(); }

  void init() {
    trie.assign(1, Node());
    cnt.push_back(0);
    root.assign(rt_num, 0);
  }

  int newNode() {
    trie.emplace_back();
    cnt.push_back(0);
    return trie.size() - 1;
  }

  void insert(int pre, int rt, int x) {
    int q = newNode();
    root[rt] = q;
    pre = root[pre];
    int cur = q;
    for (int i = 30; i >= 0; i--) {
      int bit = (x >> i) & 1;
      trie[cur].childs[bit] = newNode();
      trie[cur].childs[!bit] = trie[pre].childs[!bit];
      cnt[trie[cur].childs[bit]] = cnt[trie[pre].childs[bit]] + 1;
      cur = trie[cur].childs[bit];
      pre = trie[pre].childs[bit];
    }
  }

  int query_max(int l, int r, int x) {
    int res = 0;
    --l;  // 处理树上的时候要改为l = fa[lca]
    l = root[l];
    r = root[r];
    for (int i = 30; i >= 0; i--) {
      int bit = (x >> i) & 1;
      if (cnt[trie[r].childs[!bit]] - cnt[trie[l].childs[!bit]] > 0) {
        res += (1 << i);
        l = trie[l].childs[!bit];
        r = trie[r].childs[!bit];
      } else {
        l = trie[l].childs[bit];
        r = trie[r].childs[bit];
      }
    }
    return res;
  }
};
// 在处理序列的时候可以将序列整体平移一位，在最前面插入0